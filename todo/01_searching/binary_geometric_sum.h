#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Binary geometric sum
// Section: 1. Numeric
// Status: written and tested, not studied yet
//
// 1 + a + a^2 + ... + a^(n-1) mod m in O(log n), with no division, so it works
// even when a - 1 has no inverse mod m (m not prime, or a = 1 mod m).
//   S(2k)   = S(k) * (1 + a^k)
//   S(2k+1) = S(2k) + a^(2k)
// Recurse on n / 2 while carrying a^(n/2) along.

using ll = long long;

// returns {S(n), a^n} mod m
pair<ll, ll> geo_sum_pow(ll a, ll n, ll m) {
    if (n == 0) return {0, 1 % m};
    auto [s, p] = geo_sum_pow(a, n / 2, m);
    ll s2 = s * ((1 + p) % m) % m, p2 = p * p % m; // first 2 * (n/2) terms
    if (n % 2) return {(s2 + p2) % m, p2 * (a % m) % m};
    return {s2, p2};
}

ll geo_sum(ll a, ll n, ll m) {
    return geo_sum_pow(((a % m) + m) % m, n, m).first;
}
