#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Static range query processor
// Section: 2. Data Structure / Static Range Query Processor
// Status: written and tested, not studied yet
//
// O(1) range queries on a fixed array when the operation has an inverse
// (a group: sums, XOR, products of nonzero values mod p). Store prefixes
// P[i] = a[0] op ... op a[i-1]; then a[l, r) = inv(P[l]) op P[r].
// Written for non-commutative groups too, which is why the inverse goes on the left.
// For operations with no inverse (min, gcd) use a sparse table instead.

template <class T, class Op, class Inv>
struct StaticRangeQuery {
    vector<T> P;
    Op op;
    Inv inv;
    StaticRangeQuery(const vector<T>& a, Op op, Inv inv, T id) : P(a.size() + 1, id), op(op), inv(inv) {
        for (size_t i = 0; i < a.size(); i++) P[i + 1] = op(P[i], a[i]);
    }

    T query(int l, int r) { return op(inv(P[l]), P[r]); } // a[l, r)
};
