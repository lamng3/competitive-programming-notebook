// parbench: time plain functions, each checked against the first one.
//
// In any .cpp file:
//
//   size_t n = parbench::n(1 << 26);                         // the size, unless cppar asks for another
//   auto a = ...;                                            // an input of size n
//   parbench::run("loop", [&] { return scan_loop(a); });     // the first run is the baseline
//   parbench::run("blelloch", [&] { return scan_blelloch(a); });
//
// Each run's answer is checked against the baseline's with ==. An empty
// answer, where the baseline's isn't, reads as not written yet. A function
// that returns nothing is timed but not checked.
//
//   cppar <file>            runs it on 1, 2, 4, ... threads: a table of times and speedups
//   cppar <file> --check    runs it on sizes from 0 to 2^20, with sanitizers
//
// Run directly, it prints one line per run, on all threads (or PARLAY_NUM_THREADS).
#pragma once
#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

#include <parlay/parallel.h>
#ifdef __APPLE__
#include <pthread/qos.h>
#endif

namespace parbench {
namespace detail {

#ifdef __APPLE__
// macOS can't pin threads to cores. Before main starts, and so before
// ParlayLib starts its workers, ask it to prefer the performance cores.
inline const bool prefer_performance_cores = [] {
    pthread_set_qos_class_self_np(QOS_CLASS_USER_INTERACTIVE, 0);
    return true;
}();
#endif

inline bool for_cppar() { return std::getenv("PARBENCH_OUT") != nullptr; }
inline bool checking() { return std::getenv("PARBENCH_CHECK") != nullptr; }

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

// "" if got is right, or else what is wrong with it.
template <class R> std::string judge(const R& want, const R& got) {
    if constexpr (indexable<R>::value) {
        if (got.size() == 0 && want.size() != 0) return "not written yet";
        if (want.size() != got.size())
            return "wrong answer: size is " + std::to_string(got.size()) + ", expected " + std::to_string(want.size());
        for (size_t i = 0; i < want.size(); i++)
            if (!(want[i] == got[i])) {
                using E = std::decay_t<decltype(want[i])>;
                return "wrong answer: [" + std::to_string(i) + "] is " + show<E>(got[i]) + ", expected " + show<E>(want[i]);
            }
        return "";
    } else {
        return want == got ? "" : "wrong answer";
    }
}

struct Baseline {
    std::string name;
    std::shared_ptr<void> answer;
    const std::type_info* type = nullptr;
    double ms = 0;
};
inline Baseline& baseline() {
    static Baseline b;
    return b;
}

inline std::string ms_text(double ms) {
    char b[32];
    snprintf(b, sizeof b, ms < 1 ? "%.3f ms" : ms < 10 ? "%.2f ms" : ms < 100 ? "%.1f ms" : "%.0f ms", ms);
    return b;
}

inline void report(const std::string& name, double ms, const std::string& status) {
    if (for_cppar()) {
        printf("@parbench\t%s\t%.4f\t%s\n", name.c_str(), ms, status.c_str());
    } else if (!status.empty()) {
        printf("%-16s %s\n", name.c_str(), status.c_str());
    } else if (name == baseline().name) {
        printf("%-16s %s\n", name.c_str(), ms_text(ms).c_str());
    } else {
        printf("%-16s %-10s %.2fx\n", name.c_str(), ms_text(ms).c_str(), baseline().ms / ms);
    }
    fflush(stdout);
}

}  // namespace detail

// The problem size: default_n, or the size cppar asks for (--lg, --n, --check).
inline size_t n(size_t default_n) {
    size_t n = default_n;
    if (const char* v = std::getenv("PARBENCH_N")) n = std::stoull(v);
    if (detail::for_cppar()) printf("@parbench-n\t%zu\n", n);
    return n;
}

// Times f: the median of 7 runs, after 2 warm-ups. The first function run is
// the baseline; each later one's answer is checked against the baseline's.
template <class F> void run(const std::string& name, F f) {
    using R = std::decay_t<decltype(f())>;
    auto& base = detail::baseline();
    bool first = base.name.empty();
    if (first) base.name = name;
    int warm = detail::checking() ? 0 : 2, reps = detail::checking() ? 1 : 7;
    std::vector<double> t;
    std::string status;
    try {
        for (int r = 0; r < warm + reps && status.empty(); r++) {
            auto start = std::chrono::steady_clock::now();
            if constexpr (std::is_void_v<R>) {
                f();
                auto stop = std::chrono::steady_clock::now();
                if (r >= warm) t.push_back(std::chrono::duration<double, std::milli>(stop - start).count());
            } else {
                R got = f();
                auto stop = std::chrono::steady_clock::now();
                if (r >= warm) t.push_back(std::chrono::duration<double, std::milli>(stop - start).count());
                if (r > 0) continue;
                if (first) {
                    base.answer = std::make_shared<R>(std::move(got));
                    base.type = &typeid(R);
                } else if (base.type == nullptr || *base.type != typeid(R)) {
                    status = "returns a different type from " + base.name;
                } else {
                    status = detail::judge(*static_cast<const R*>(base.answer.get()), got);
                }
            }
        }
    } catch (const std::logic_error& e) {
        status = std::string(e.what()) == "not written yet" ? "not written yet" : std::string("threw: ") + e.what();
    } catch (const std::exception& e) {
        status = std::string("threw: ") + e.what();
    }
    double ms = 0;
    if (status.empty() && !t.empty()) {
        std::sort(t.begin(), t.end());
        ms = t[t.size() / 2];
    }
    if (first) base.ms = ms;
    detail::report(name, ms, status);
}

}  // namespace parbench
