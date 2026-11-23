// https://www.cs.umd.edu/~laxman/notes/parallel.pdf (pg.7)
// Sum. Check: cppar sum --check. Time: cppar sum.
#include <cstddef>

#include <parlay/parallel.h>
#include <parlay/primitives.h>
#include <parlay/sequence.h>
#include <parlay/slice.h>

#include <parbench.h>

template<typename It>
long long sum_sequential(parlay::slice<It, It> s) {
    long long total = 0;
    for (long long x : s) total += x;
    return total;
}

long long sum_sequential(const parlay::sequence<long long>& a) {
    return sum_sequential(parlay::make_slice(a));
}

template<typename It>
long long sum_recursive(parlay::slice<It, It> s) {
    const std::size_t n = s.size();
    if (n == 0) return 0;
    if (n == 1) return s[0];
    auto mid = n / 2;
    long long left = sum_recursive(s.cut(0, mid));
    long long right = sum_recursive(s.cut(mid, n));
    return left + right;
}

long long sum_recursive(const parlay::sequence<long long>& a) {
    return sum_recursive(parlay::make_slice(a));
}

template<typename It>
long long sum_parallel(parlay::slice<It, It> s) {
    const std::size_t n = s.size();
    if (n == 0) return 0;
    if (n == 1) return s[0];
    auto mid = n / 2;
    long long left, right;
    parlay::par_do(
        [&]() { left = sum_parallel(s.cut(0, mid)); },
        [&]() { right = sum_parallel(s.cut(mid, n)); }
    );
    return left + right;
}

long long sum_parallel(const parlay::sequence<long long>& a) {
    return sum_parallel(parlay::make_slice(a));
}

// Below this size, a loop is faster than splitting further: a par_do costs about 8 ns, an addition far less.
constexpr std::size_t cutoff = 4096;

template<typename It>
long long sum_parallel_cutoff(parlay::slice<It, It> s) {
    const std::size_t n = s.size();
    if (n <= cutoff) return sum_sequential(s);
    auto mid = n / 2;
    long long left, right;
    parlay::par_do(
        [&]() { left = sum_parallel_cutoff(s.cut(0, mid)); },
        [&]() { right = sum_parallel_cutoff(s.cut(mid, n)); }
    );
    return left + right;
}

long long sum_parallel_cutoff(const parlay::sequence<long long>& a) {
    return sum_parallel_cutoff(parlay::make_slice(a));
}

int main() {
    std::size_t n = parbench::n(1 << 24);
    auto a = parlay::tabulate(n, [](std::size_t i) {
        return static_cast<long long>(parlay::hash64(i) % 100);
    });

    parbench::run("sequential", [&] { return sum_sequential(a); });  // the baseline
    parbench::run("recursive", [&] { return sum_recursive(a); });
    parbench::run("parallel", [&] { return sum_parallel(a); });
    parbench::run("parallel + cutoff", [&] { return sum_parallel_cutoff(a); });
    parbench::run("parlay::reduce", [&] { return parlay::reduce(a); });  // the speed to beat
}
