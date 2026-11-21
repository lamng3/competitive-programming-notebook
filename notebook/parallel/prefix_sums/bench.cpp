// Times the scans in this folder against a sequential loop and ParlayLib's
// scan. Run it through bench.py, which builds it with -O3 and runs it on
// several thread counts. One run: PARLAY_NUM_THREADS=8 ./bench 26
//
// Prints CSV: method, threads, n, median ms, billions of elements per
// second, and speedup over the sequential loop. A scan that isn't written
// yet, or gives a wrong answer at this size, is reported and not timed.
#include "HillisSteeleScan.h"
#include "BlellochScan.h"
#include "BlockedScan.h"
#include <parlay/primitives.h>
#include <parlay/sequence.h>
#ifdef __APPLE__
#include <pthread/qos.h>
#endif

using ll = long long;
const ll UNTOUCHED = LLONG_MIN + 7;

void scan_sequential(const ll* in, ll* out, size_t n) {
    ll s = 0;
    for (size_t i = 0; i < n; i++) out[i] = s += in[i];
}

// Median of 7 timed runs, after 2 untimed warm-up runs that fault in the
// memory and let the clock speed settle. setup runs before each run, untimed.
double median_ms(const function<void()>& run, const function<void()>& setup = [] {}) {
    vector<double> t;
    for (int r = 0; r < 9; r++) {
        setup();
        auto start = chrono::steady_clock::now();
        run();
        auto stop = chrono::steady_clock::now();
        if (r >= 2) t.push_back(chrono::duration<double, milli>(stop - start).count());
    }
    sort(t.begin(), t.end());
    return t[t.size() / 2];
}

int main(int argc, char** argv) {
#ifdef __APPLE__
    // macOS can't pin threads to cores. This asks it to prefer the
    // performance cores, before ParlayLib starts its workers.
    pthread_set_qos_class_self_np(QOS_CLASS_USER_INTERACTIVE, 0);
#endif
    int lg = argc > 1 ? atoi(argv[1]) : 26;
    size_t n = size_t(1) << lg, p = parlay::num_workers();
    auto in = parlay::tabulate(n, [](size_t i) { return ll(parlay::hash64(i) % 101) - 50; });
    parlay::sequence<ll> want(n), out(n), tmp(n);
    scan_sequential(in.data(), want.data(), n);

    double base = median_ms([&] { scan_sequential(in.data(), out.data(), n); });
    auto line = [&](const char* name, double ms) {
        printf("%s,%zu,%zu,%.2f,%.3f,%.2f\n", name, p, n, ms, n / ms / 1e6, base / ms);
        fflush(stdout);
    };
    line("sequential", base);
    line("parlay", median_ms([&] { parlay::scan_inclusive_inplace(out); }, [&] { parlay::copy(in, out); }));

    struct Scan { const char* name; function<void()> run; };
    vector<Scan> scans = {
        {"hillis-steele", [&] { scan_hillis_steele(in.data(), out.data(), tmp.data(), n); }},
        {"blelloch", [&] { scan_blelloch(in.data(), out.data(), n); }},
        {"blocked", [&] { scan_blocked(in.data(), out.data(), n); }},
    };
    for (auto& s : scans) {
        parlay::parallel_for(0, n, [&](size_t i) { out[i] = UNTOUCHED; });
        s.run();
        if (out[0] == UNTOUCHED && out[n - 1] == UNTOUCHED) printf("%s,%zu,%zu,not written yet\n", s.name, p, n);
        else if (out != want) printf("%s,%zu,%zu,wrong answer\n", s.name, p, n);
        else line(s.name, median_ms(s.run));
    }
}
