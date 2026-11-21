// Hillis and Steele's scan. Check: cppar hillis_steele_scan --check. Time: cppar hillis_steele_scan.
#include <cstddef>

#include <parlay/parallel.h>
#include <parlay/primitives.h>
#include <parlay/sequence.h>

#include <parbench.h>

parlay::sequence<long long> scan_loop(const parlay::sequence<long long>& a) {
    auto out = parlay::sequence<long long>::uninitialized(a.size());
    long long sum = 0;
    for (std::size_t i = 0; i < a.size(); i++) out[i] = sum += a[i];
    return out;
}

parlay::sequence<long long> hillis_steele_scan(const parlay::sequence<long long>& a) {
    // TODO
    return {};
}

int main() {
    std::size_t n = parbench::n(1 << 26);
    auto a = parlay::tabulate(n, [](std::size_t i) {
        return static_cast<long long>(parlay::hash64(i) % 101) - 50;
    });

    parbench::run("loop", [&] { return scan_loop(a); });  // the baseline
    parbench::run("hillis-steele", [&] { return hillis_steele_scan(a); });
}
