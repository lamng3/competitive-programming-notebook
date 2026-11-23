// Prefix sums: out[i] = a[0] + ... + a[i]. Check: cppar prefix_sums --check. Time: cppar prefix_sums.
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

parlay::sequence<long long> scan_hillis_steele(const parlay::sequence<long long>& a) {
    const std::size_t n = a.size();
    parlay::sequence<long long> cur = a; // copy
    auto nxt = parlay::sequence<long long>::uninitialized(n);
    for (std::size_t d = 1; d < n; d <<= 1) {
        parlay::parallel_for(0, n, [&](std::size_t i) {
            if (i >= d) nxt[i] = cur[i] + cur[i - d];
            else nxt[i] = cur[i];
        });
        std::swap(cur, nxt);
    }
    return cur;
}

parlay::sequence<long long> scan_blelloch(const parlay::sequence<long long>& a) {
    // TODO
    return {};
}

int main() {
    std::size_t n = parbench::n(1 << 26);
    auto a = parlay::tabulate(n, [](std::size_t i) {
        return static_cast<long long>(parlay::hash64(i) % 101) - 50;
    });

    parbench::run("loop", [&] { return scan_loop(a); });  // the baseline
    parbench::run("hillis-steele", [&] { return scan_hillis_steele(a); });
    parbench::run("blelloch", [&] { return scan_blelloch(a); });
}
