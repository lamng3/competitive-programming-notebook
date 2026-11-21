// Prefix sums: a sequential loop against Hillis and Steele's scan and Blelloch's.
//   cppar prefix_sums            time them, on 1 thread up to every core
//   cppar prefix_sums --check    check them on sizes from 0 to 2^20
#include <parbench.h>
#include <parlay/primitives.h>
#include "HillisSteeleScan.h"
#include "BlellochScan.h"

using ll = long long;
using Seq = parlay::sequence<ll>;

// Each scan writes into buffers allocated in setup, so the timer sees only the scan.
struct Buffers {
    const Seq& in;
    Seq out, tmp;
};

int main(int argc, char** argv) {
    parbench::Bench<Seq, Seq> b("prefix sums");
    b.default_size(26);
    b.input([](size_t n, uint64_t seed) {
        return parlay::tabulate(n, [&](size_t i) { return ll(parlay::hash64(i + seed * n) % 101) - 50; });
    });
    auto out = [](const Seq& in) { return Buffers{in, parbench::fresh<ll>(in.size()), {}}; };
    auto out_and_tmp = [](const Seq& in) {
        return Buffers{in, parbench::fresh<ll>(in.size()), parbench::fresh<ll>(in.size())};
    };

    b.sequential("loop", out, [](Buffers& s) {
        ll sum = 0;
        for (size_t i = 0; i < s.in.size(); i++) s.out[i] = sum += s.in[i];
        return std::move(s.out);
    });
    b.parallel("hillis-steele", out_and_tmp, [](Buffers& s) {
        scan_hillis_steele(s.in.data(), s.out.data(), s.tmp.data(), s.in.size());
        return std::move(s.out);
    });
    b.parallel("blelloch", out, [](Buffers& s) {
        scan_blelloch(s.in.data(), s.out.data(), s.in.size());
        return std::move(s.out);
    });
    return b.run(argc, argv);
}
