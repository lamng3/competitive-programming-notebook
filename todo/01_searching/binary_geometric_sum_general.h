#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Binary geometric sum general
// Section: 1. Numeric
// Status: written and tested, not studied yet
//
// The same doubling as binary_geometric_sum.h, for any T with + and * (a ring):
// matrices, polynomials, modular ints. Returns 1 + a + ... + a^(n-1).
// Needs the identities: zero (for +) and one (for *).
//
// With matrices this sums a linear recurrence's states: sum of the first n
// Fibonacci numbers is one entry of the sum of powers of [[1,1],[1,0]].

template <class T>
pair<T, T> geo_sum_pow_general(const T& a, long long n, const T& zero, const T& one) {
    if (n == 0) return {zero, one};
    auto [s, p] = geo_sum_pow_general(a, n / 2, zero, one);
    T s2 = s * (one + p), p2 = p * p;
    if (n % 2) return {s2 + p2, p2 * a};
    return {s2, p2};
}

template <class T>
T geo_sum_general(const T& a, long long n, const T& zero, const T& one) {
    return geo_sum_pow_general(a, n, zero, one).first;
}
