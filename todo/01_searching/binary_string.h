#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Binary string
// Section: 1. Numeric
// Status: written and tested, not studied yet
//
// Integers <-> fixed-width binary strings, and walking all bitmasks of a set.
//   to_binary(5, 4) = "0101", most significant bit first
//   from_binary("0101") = 5
//   for_each_submask(m, f) calls f on every submask of m, m first, 0 last;
//   over all m this is O(3^n), the standard "sum over submasks" loop.

using ll = long long;

string to_binary(ll x, int width) {
    string s(width, '0');
    for (int i = 0; i < width; i++) if (x >> i & 1) s[width - 1 - i] = '1';
    return s;
}

ll from_binary(const string& s) {
    ll x = 0;
    for (char c : s) x = x << 1 | (c == '1');
    return x;
}

template <class F>
void for_each_submask(int m, F f) {
    for (int s = m; ; s = (s - 1) & m) {
        f(s);
        if (s == 0) break;
    }
}
