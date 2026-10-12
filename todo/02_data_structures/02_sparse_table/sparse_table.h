#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Sparse table
// Section: 2. Data Structure / Sparse Table
// Status: written and tested, not studied yet
//
// O(1) range queries for an idempotent operation (min, max, gcd, AND, OR):
// one where combining overlapping ranges is harmless, op(x, x) = x.
// t[k][i] = op over a[i .. i + 2^k). Any range [l, r) is covered by two blocks
// of length 2^k with k = floor(log2(r - l)), which may overlap. O(n log n) build.

template <class T, class Op>
struct SparseTable {
    vector<vector<T>> t;
    Op op;
    SparseTable(const vector<T>& a, Op op) : op(op) {
        int n = a.size(), K = 1;
        while ((1 << K) <= n) K++;
        t.assign(K, a);
        for (int k = 1; k < K; k++)
            for (int i = 0; i + (1 << k) <= n; i++)
                t[k][i] = op(t[k - 1][i], t[k - 1][i + (1 << (k - 1))]);
    }

    // op over a[l, r), needs l < r
    T query(int l, int r) {
        int k = 31 - __builtin_clz(r - l);
        return op(t[k][l], t[k][r - (1 << k)]);
    }
};
