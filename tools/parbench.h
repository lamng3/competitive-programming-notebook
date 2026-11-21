// parbench: check parallel versions of an algorithm against a sequential
// reference, and time them on several thread counts. cppar builds and runs it.
//
// A benchmark is notebook/parallel/<name>/bench.cpp, a main() that registers
// one problem:
//
//   parbench::Bench<Input, Output> b("prefix sums");
//   b.input([](size_t n, uint64_t seed) { return ...; });   // an input of size n
//   b.sequential("loop", [](const Input& in) { ... });      // the reference
//   b.parallel("blocked", [](const Input& in) { ... });     // as many as you like
//   return b.run(argc, argv);
//
// Each version returns an Output, checked against the reference's with ==,
// or with b.check(...) when a problem has many right answers. A version with
// work that shouldn't be timed, like allocating its output or building a
// tree before a batch of updates, registers two functions: setup, which
// turns the input into a state, untimed, and the timed part, which runs on
// that state. A stub that throws logic_error("not written yet") is reported
// as not written yet.
//
//   cppar <name>            time every version, as a table
//   cppar <name> --check    check every version on many sizes, with sanitizers
#pragma once
#include <bits/stdc++.h>
#include <parlay/parallel.h>
#include <parlay/sequence.h>
#ifdef __APPLE__
#include <pthread/qos.h>
#endif

namespace parbench {

// n default-constructed Ts, every page already written. Use it in setup for
// output buffers, so that the first touches don't land in the timed part.
template <class T>
parlay::sequence<T> fresh(size_t n) {
    parlay::sequence<T> s(n);
    parlay::parallel_for(0, n, [&](size_t i) { s[i] = T(); });
    return s;
}

namespace detail {

template <class, class = void> struct indexable : std::false_type {};
template <class C>
struct indexable<C, std::void_t<decltype(std::declval<const C&>().size()), decltype(std::declval<const C&>()[0])>>
    : std::true_type {};

template <class T> std::string show(const T& x) {
    if constexpr (std::is_arithmetic_v<T>) {
        std::ostringstream o;
        o << x;
        return o.str();
    } else {
        return "?";
    }
}

// "" if got equals want, or else where they first differ.
template <class Output> std::string compare(const Output& want, const Output& got) {
    if constexpr (indexable<Output>::value) {
        if (want.size() != got.size())
            return "size is " + std::to_string(got.size()) + ", expected " + std::to_string(want.size());
        for (size_t i = 0; i < want.size(); i++)
            if (!(want[i] == got[i])) {
                using E = std::decay_t<decltype(want[i])>;
                return "[" + std::to_string(i) + "] is " + show<E>(got[i]) + ", expected " + show<E>(want[i]);
            }
        return "";
    } else {
        return want == got ? "" : "wrong answer";
    }
}

inline std::string with_commas(size_t n) {
    std::string s = std::to_string(n);
    for (int i = int(s.size()) - 3; i > 0; i -= 3) s.insert(size_t(i), ",");
    return s;
}

inline std::string ms_text(double ms) {
    char b[32];
    snprintf(b, sizeof b, ms < 1 ? "%.3f ms" : ms < 10 ? "%.2f ms" : ms < 100 ? "%.1f ms" : "%.0f ms", ms);
    return b;
}

}  // namespace detail

template <class Input, class Output>
class Bench {
  public:
    using Run = std::function<Output()>;
    using Prepare = std::function<Run(const Input&)>;  // untimed setup, returning the timed part
    using Checker = std::function<std::string(const Input&, const Output& want, const Output& got)>;

    explicit Bench(std::string name) : name_(std::move(name)) {}

    // How to make an input of size n. The same n and seed must give the same input.
    Bench& input(std::function<Input(size_t n, uint64_t seed)> make) {
        make_ = std::move(make);
        return *this;
    }

    // The reference: a plain sequential version. Its answers are the right
    // ones, and its time is what the parallel versions are compared with.
    template <class F> Bench& sequential(std::string name, F f) {
        reference_ = {std::move(name), simple(std::move(f))};
        return *this;
    }
    template <class Setup, class Timed> Bench& sequential(std::string name, Setup setup, Timed timed) {
        reference_ = {std::move(name), staged(std::move(setup), std::move(timed))};
        return *this;
    }

    // A parallel version, timed whole or after an untimed setup.
    template <class F> Bench& parallel(std::string name, F f) {
        versions_.push_back({std::move(name), simple(std::move(f))});
        return *this;
    }
    template <class Setup, class Timed> Bench& parallel(std::string name, Setup setup, Timed timed) {
        versions_.push_back({std::move(name), staged(std::move(setup), std::move(timed))});
        return *this;
    }

    // For problems with many right answers (a maximal independent set, a
    // spanning forest): return "" if got is right for this input, or what is
    // wrong with it.
    Bench& check(Checker checker) {
        checker_ = std::move(checker);
        return *this;
    }

    // n = 2^lg when timing, unless cppar is given --lg or --n.
    Bench& default_size(int lg) {
        lg_ = lg;
        return *this;
    }

    // The sizes --check tries, three inputs each.
    Bench& check_sizes(std::vector<size_t> sizes) {
        check_sizes_ = std::move(sizes);
        return *this;
    }

    int run(int argc, char** argv) {
#ifdef __APPLE__
        // macOS can't pin threads to cores; this asks it to prefer the
        // performance cores over the efficiency cores.
        pthread_set_qos_class_self_np(QOS_CLASS_USER_INTERACTIVE, 0);
#endif
        Options o;
        if (!parse(argc, argv, o)) return 2;
        if (!make_ || !reference_.prepare) {
            fprintf(stderr, "%s: register an input and a sequential version before run()\n", name_.c_str());
            return 2;
        }
        return o.check ? checks() : bench(o);
    }

  private:
    struct Version {
        std::string name;
        Prepare prepare;
    };
    struct Options {
        bool check = false, csv = false;
        size_t n = 0;
        int reps = 7;
        std::vector<size_t> threads;
    };

    std::string name_;
    std::function<Input(size_t, uint64_t)> make_;
    Version reference_;
    std::vector<Version> versions_;
    Checker checker_;
    int lg_ = 24;
    std::vector<size_t> check_sizes_ = {0, 1, 2, 3, 4, 5, 7, 8, 9, 16, 17, 100, 1000, 1023, 1024, 4097, 65536, 100003, 1 << 20};
    size_t max_threads_ = std::max(1u, std::thread::hardware_concurrency());

    template <class F> static Prepare simple(F f) {
        return [f](const Input& in) -> Run { return [f, &in] { return Output(f(in)); }; };
    }
    template <class Setup, class Timed> static Prepare staged(Setup setup, Timed timed) {
        return [setup, timed](const Input& in) -> Run {
            using State = std::decay_t<decltype(setup(in))>;
            auto state = std::make_shared<State>(setup(in));
            return [state, timed] { return Output(timed(*state)); };
        };
    }

    bool parse(int argc, char** argv, Options& o) {
        for (int i = 1; i < argc; i++) {
            std::string a = argv[i];
            auto value = [&](const char* what) -> long long {
                if (i + 1 >= argc) throw std::invalid_argument(a + " needs " + what);
                return std::stoll(argv[++i]);
            };
            try {
                if (a == "--check") o.check = true;
                else if (a == "--csv") o.csv = true;
                else if (a == "--lg") o.n = size_t(1) << value("a power of 2");
                else if (a == "--n") o.n = size_t(value("a size"));
                else if (a == "--reps") o.reps = int(std::max(1LL, value("a count")));
                else if (a == "--threads") {
                    while (i + 1 < argc && isdigit(static_cast<unsigned char>(argv[i + 1][0]))) o.threads.push_back(std::stoul(argv[++i]));
                    if (o.threads.empty()) throw std::invalid_argument("--threads needs thread counts");
                } else throw std::invalid_argument("unknown option " + a);
            } catch (const std::exception& e) {
                fprintf(stderr, "%s\nusage: [--check] [--lg L | --n N] [--threads P ...] [--reps R] [--csv]\n", e.what());
                return false;
            }
        }
        if (o.n == 0) o.n = size_t(1) << lg_;
        if (o.threads.empty()) {
            for (size_t p = 1; p < max_threads_; p *= 2) o.threads.push_back(p);
            o.threads.push_back(max_threads_);
        }
        return true;
    }

    // "" if v is right on this input, "not written yet", or what went wrong.
    std::string attempt(const Version& v, const Input& in, const Output& want) const {
        try {
            Run f = v.prepare(in);
            Output got = f();
            return judge(in, want, got);
        } catch (const std::logic_error& e) {
            if (std::string(e.what()) == "not written yet") return "not written yet";
            return std::string("threw: ") + e.what();
        } catch (const std::exception& e) {
            return std::string("threw: ") + e.what();
        }
    }

    std::string judge(const Input& in, const Output& want, const Output& got) const {
        return checker_ ? checker_(in, want, got) : detail::compare(want, got);
    }

    // Median of reps timed runs, after 2 warm-ups. The first warm-up's
    // answer is checked too, since a race may show only on some thread counts.
    std::pair<double, std::string> time(const Version& v, const Input& in, const Output& want, int reps) const {
        std::vector<double> t;
        try {
            for (int r = 0; r < 2 + reps; r++) {
                Run f = v.prepare(in);
                auto start = std::chrono::steady_clock::now();
                Output got = f();
                auto stop = std::chrono::steady_clock::now();
                if (r == 0) {
                    std::string problem = judge(in, want, got);
                    if (!problem.empty()) return {0, problem};
                }
                if (r >= 2) t.push_back(std::chrono::duration<double, std::milli>(stop - start).count());
            }
        } catch (const std::exception& e) {
            return {0, std::string("threw: ") + e.what()};
        }
        std::sort(t.begin(), t.end());
        return {t[t.size() / 2], ""};
    }

    int checks() {
        printf("%s: checking %zu parallel version%s against %s, on %zu sizes with 3 inputs each, on %zu threads\n\n",
               name_.c_str(), versions_.size(), versions_.size() == 1 ? "" : "s", reference_.name.c_str(),
               check_sizes_.size(), max_threads_);
        size_t width = 0;
        for (auto& v : versions_) width = std::max(width, v.name.size());
        int bad = 0;
        for (auto& v : versions_) {
            std::string result;
            parlay::execute_with_scheduler(unsigned(max_threads_), [&] {
                for (size_t n : check_sizes_) {
                    for (uint64_t seed = 0; seed < 3 && result.empty(); seed++) {
                        Input in = make_(n, seed);
                        Output want = reference_.prepare(in)();
                        std::string r = attempt(v, in, want);
                        if (r == "not written yet") result = r;
                        else if (!r.empty()) result = "FAIL  n = " + std::to_string(n) + ", input " + std::to_string(seed) + ": " + r;
                    }
                    if (!result.empty()) break;
                }
            });
            printf("  %-*s  %s\n", int(width), v.name.c_str(), result.empty() ? "pass" : result.c_str());
            if (!result.empty()) bad++;
        }
        return bad ? 1 : 0;
    }

    int bench(const Options& o) {
        size_t n = o.n;
        Input in;
        Output want;
        double base = 0;
        parlay::execute_with_scheduler(unsigned(max_threads_), [&] { in = make_(n, 1); });
        parlay::execute_with_scheduler(1, [&] {
            want = reference_.prepare(in)();
            base = time(reference_, in, want, o.reps).first;
        });

        // Check every version once, on every core, before timing any.
        std::vector<std::string> status(versions_.size());
        parlay::execute_with_scheduler(unsigned(max_threads_), [&] {
            for (size_t i = 0; i < versions_.size(); i++) status[i] = attempt(versions_[i], in, want);
        });

        std::vector<std::vector<std::string>> cells(versions_.size(), std::vector<std::string>(o.threads.size()));
        for (size_t j = 0; j < o.threads.size(); j++) {
            size_t p = o.threads[j];
            parlay::execute_with_scheduler(unsigned(p), [&] {
                for (size_t i = 0; i < versions_.size(); i++) {
                    if (!status[i].empty()) continue;
                    auto [ms, problem] = time(versions_[i], in, want, o.reps);
                    if (o.csv) {
                        if (problem.empty()) printf("%s,%zu,%zu,%.4f,%.3f\n", versions_[i].name.c_str(), p, n, ms, base / ms);
                        else printf("%s,%zu,%zu,%s\n", versions_[i].name.c_str(), p, n, problem.c_str());
                        continue;
                    }
                    char speed[32];
                    snprintf(speed, sizeof speed, base / ms < 10 ? "%.2fx" : "%.1fx", base / ms);
                    cells[i][j] = problem.empty() ? detail::ms_text(ms) + "  " + speed : "wrong: " + problem;
                }
            });
        }
        if (o.csv) {
            printf("%s,1,%zu,%.4f,1.000\n", reference_.name.c_str(), n, base);
            for (size_t i = 0; i < versions_.size(); i++)
                if (!status[i].empty()) printf("%s,,%zu,%s\n", versions_[i].name.c_str(), n, status[i].c_str());
            return 0;
        }
        print_table(o, n, base, status, cells);
        return 0;
    }

    void print_table(const Options& o, size_t n, double base, const std::vector<std::string>& status,
                     const std::vector<std::vector<std::string>>& cells) const {
        std::string size = detail::with_commas(n);
        if (n && (n & (n - 1)) == 0) size = "2^" + std::to_string(__builtin_ctzll(n)) + " = " + size;
        printf("%s · n = %s · median of %d runs, after 2 warm-ups\n\n", name_.c_str(), size.c_str(), o.reps);

        std::string label = reference_.name == "sequential" ? reference_.name : reference_.name + " (sequential)";
        size_t first = label.size();
        for (auto& v : versions_) first = std::max(first, v.name.size());
        std::vector<std::string> head;
        for (size_t p : o.threads) head.push_back(std::to_string(p) + (p == 1 ? " thread" : " threads"));
        std::vector<size_t> width(o.threads.size());
        for (size_t j = 0; j < o.threads.size(); j++) {
            width[j] = head[j].size();
            for (size_t i = 0; i < versions_.size(); i++)
                if (status[i].empty()) width[j] = std::max(width[j], cells[i][j].size());
        }

        printf("  %-*s", int(first), "");
        for (size_t j = 0; j < head.size(); j++) printf("   %-*s", int(width[j]), head[j].c_str());
        printf("\n  %-*s   %s\n", int(first), label.c_str(), detail::ms_text(base).c_str());
        for (size_t i = 0; i < versions_.size(); i++) {
            printf("  %-*s", int(first), versions_[i].name.c_str());
            if (!status[i].empty()) {
                const std::string& s = status[i];
                bool plain = s == "not written yet" || s.rfind("threw: ", 0) == 0;
                printf("   %s\n", (plain ? s : "wrong answer: " + s).c_str());
                continue;
            }
            for (size_t j = 0; j < cells[i].size(); j++) printf("   %-*s", int(width[j]), cells[i][j].c_str());
            printf("\n");
        }
        printf("\nEach cell: time per run, then speedup over %s (%s).\n", reference_.name.c_str(), detail::ms_text(base).c_str());
    }
};

}  // namespace parbench
