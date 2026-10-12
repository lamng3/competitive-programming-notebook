#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Disjoint sparse table
// Section: 2. Data Structure / Disjoint Sparse Table
// Status: written and tested, not studied yet
//
// O(1) range queries for any associative operation (sum, product, matrix product),
// no idempotence needed. Split the array at the midpoints of a segment-tree layout;
// for each level and block, store suffix results leftward from the midpoint and
// prefix results rightward. A query [l, r] crosses exactly one midpoint: the level
// is the highest set bit of l ^ r (l and r first differ there, so the midpoint
// between them is r with its lower bits cleared), and the answer is
// suffix(l) op prefix(r).
// Size is padded to a power of two. O(n log n) build.

template <class T, class Op>
struct DisjointSparseTable {
    int n, K;
    vector<vector<T>> t;
    Op op;
    DisjointSparseTable(vector<T> a, Op op) : op(op) {
        n = a.size();
        K = 1;
        while ((1 << K) < max(n, 2)) K++;
        a.resize(1 << K, a.empty() ? T() : a.back()); // padding is never read
        t.assign(K, a);
        for (int k = 0; k < K; k++) { // level k: blocks of 2^k on each side of mid
            int half = 1 << k;
            for (int mid = half; mid < (1 << K); mid += 2 * half) {
                t[k][mid - 1] = a[mid - 1];
                for (int i = mid - 2; i >= mid - half; i--) t[k][i] = op(a[i], t[k][i + 1]);
                t[k][mid] = a[mid];
                for (int i = mid + 1; i < mid + half; i++) t[k][i] = op(t[k][i - 1], a[i]);
            }
        }
    }

    // op over a[l..r], inclusive
    T query(int l, int r) {
        if (l == r) return t[0][l];
        int k = 31 - __builtin_clz(l ^ r);
        return op(t[k][l], t[k][r]);
    }
};
