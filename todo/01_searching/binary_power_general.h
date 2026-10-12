#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Binary power general
// Section: 1. Numeric
// Status: written and tested, not studied yet
//
// a^e for any associative operation, by squaring: O(log e) operations.
// The operation does not have to be multiplication: composing permutations,
// multiplying matrices, or (min, +) "multiplying" distance matrices all work.

template <class T, class Op>
T power_general(T a, long long e, T identity, Op op) {
    T res = identity;
    while (e > 0) {
        if (e & 1) res = op(res, a);
        a = op(a, a);
        e >>= 1;
    }
    return res;
}
