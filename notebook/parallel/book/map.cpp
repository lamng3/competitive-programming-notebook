// https://www.cs.umd.edu/~laxman/notes/parallel.pdf (pg.7)
// Map. Check: cppar map --check. Time: cppar map.
#include <cstddef>

#include <parlay/parallel.h>
#include <parlay/primitives.h>
#include <parlay/sequence.h>

#include <parbench.h>

long long f(const long long x) {
    return x * 10;
}

parlay::sequence<long long> map_sequential(const parlay::sequence<long long>& a) {
    const std::size_t n = a.size();
    auto b = parlay::sequence<long long>::uninitialized(n);
    for (int i = 0; i < n; i++) {
        b[i] = f(a[i]);
    }
    return b;
}

parlay::sequence<long long> map_parallel(const parlay::sequence<long long>& a) {
    const std::size_t n = a.size();
    auto b = parlay::sequence<long long>::uninitialized(n);
    parlay::parallel_for(0, n, [&](std::size_t i) {
        b[i] = f(a[i]);
    });
    return b;
}

int main() {
    std::size_t n = parbench::n(1 << 24);
    auto a = parlay::tabulate(n, [](std::size_t i) {
        return static_cast<long long>(parlay::hash64(i) % 100);
    });

    parbench::run("sequential", [&] { return map_sequential(a); });  // the baseline
    parbench::run("map", [&] { return map_parallel(a); });
}
