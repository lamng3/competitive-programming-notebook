#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Discrete golden section search
// Section: 1. Numeric
// Status: written and tested, not studied yet
//
// Maximize a unimodal f on the integers [lo, hi] (strictly up, then strictly down,
// plateaus only at the top). Like ternary search, but the two probe points are
// placed at Fibonacci ratios so one of them is reused each round: about
// log_phi(n) ~ 1.44 log2(n) evaluations instead of 2 log_{3/2}(n) ~ 3.4 log2(n).
// Worth it when f is expensive. Returns the argmax.

template <class F>
long long golden_max_int(long long lo, long long hi, F f) {
    // extend the range to a Fibonacci length; points past hi read as -inf
    vector<long long> fib = {1, 1};
    while (fib.back() < hi - lo + 1) fib.push_back(fib[fib.size() - 1] + fib[fib.size() - 2]);
    using T = decltype(f(lo));
    auto g = [&](long long x) -> pair<int, T> { // (in range?, value), compared as a pair
        if (x > hi) return {0, T()};
        return {1, f(x)};
    };
    long long a = lo;
    int k = fib.size() - 1; // search [a, a + fib[k] - 1]
    if (k < 2) return lo;
    long long x1 = a + fib[k - 2], x2 = a + fib[k - 1];
    auto f1 = g(x1 - 1), f2 = g(x2 - 1); // probes at offsets fib[k-2]-1, fib[k-1]-1
    while (k > 2) {
        if (f1 < f2) { // the max is right of x1 - 1
            a = x1;
            k--;
            x1 = x2, f1 = f2;
            x2 = a + fib[k - 1];
            f2 = g(x2 - 1);
        } else {
            k--;
            x2 = x1, f2 = f1;
            x1 = a + fib[k - 2];
            f1 = g(x1 - 1);
        }
    }
    // a few candidates are left; check them directly
    long long best = a;
    for (long long x = a; x <= min(hi, a + 2); x++) if (g(x) > g(best)) best = x;
    return best;
}
