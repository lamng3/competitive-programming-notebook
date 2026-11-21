#include <chrono>
#include <cmath>
#include <iostream>

#include <parlay/parallel.h>
#include <parlay/primitives.h>
#include <parlay/sequence.h>

parlay::sequence<long> prime_sieve(long n) {
    if (n < 2) return parlay::sequence<long>();
    else {
        long sqrt = std::sqrt(n);
        auto primes_sqrt = prime_sieve(sqrt);
        parlay::sequence<bool> flags(n+1, true); // flags to mark primes
        flags[0] = flags[1] = false; // 0 and 1 are not prime
        parlay::parallel_for(0, primes_sqrt.size(), [&](size_t i) {
            long prime = primes_sqrt[i];
            parlay::parallel_for(2, n/prime + 1, [&](size_t j) {
                flags[prime * j] = false;
            });
        }, 1);
        return parlay::filter(parlay::iota<long>(n+1), [&](size_t i) { return flags[i]; });
    }
}

int main() {
    auto small = prime_sieve(100);
    for (long p : small) std::cout << p << ' ';
    std::cout << '\n';

    auto start = std::chrono::steady_clock::now();
    auto big = prime_sieve(100'000'000);
    auto ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count();
    std::cout << big.size() << " primes up to 10^8, in " << ms << " ms on " << parlay::num_workers() << " threads\n";
}
