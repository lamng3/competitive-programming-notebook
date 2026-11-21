// Hillis and Steele's scan. Check: cppar hillis_steele_scan --check. Time: cppar hillis_steele_scan.
#include <cstddef>
#include <cstdint>

#include <parlay/parallel.h>
#include <parlay/primitives.h>
#include <parlay/sequence.h>

#include <parbench.h>

parlay::sequence<std::int64_t> scan_loop(const parlay::sequence<std::int64_t>& a) {
    auto out = parlay::sequence<std::int64_t>::uninitialized(a.size());
    std::int64_t sum = 0;
    for (std::size_t i = 0; i < a.size(); i++) out[i] = sum += a[i];
    return out;
}

parlay::sequence<std::int64_t> hillis_steele_scan(const parlay::sequence<std::int64_t>& a) {
    // TODO
    return {};
}

int main() {
    std::size_t n = parbench::n(1 << 26);
    auto a = parlay::tabulate(n, [](std::size_t i) {
        return static_cast<std::int64_t>(parlay::hash64(i) % 101) - 50;
    });

    parbench::run("loop", [&] { return scan_loop(a); });  // the baseline
    parbench::run("hillis-steele", [&] { return hillis_steele_scan(a); });
}
