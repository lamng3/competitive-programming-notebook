#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Range minmax query solver
// Section: 2. Data Structure / Sparse Table
// Status: written and tested, not studied yet
//
// Range min and max, with the positions where they occur, in O(1) per query after
// an O(n log n) build. A sparse table over indices: comparing a[i] and a[j] picks
// the better index, ties broken toward the leftmost.

template <class T>
struct RangeMinMax {
    vector<T> a;
    vector<vector<int>> mn, mx;
    RangeMinMax(const vector<T>& a) : a(a) {
        int n = a.size(), K = 1;
        while ((1 << K) <= n) K++;
        mn.assign(K, vector<int>(n)), mx.assign(K, vector<int>(n));
        iota(mn[0].begin(), mn[0].end(), 0), iota(mx[0].begin(), mx[0].end(), 0);
        for (int k = 1; k < K; k++)
            for (int i = 0; i + (1 << k) <= n; i++) {
                mn[k][i] = lo(mn[k - 1][i], mn[k - 1][i + (1 << (k - 1))]);
                mx[k][i] = hi(mx[k - 1][i], mx[k - 1][i + (1 << (k - 1))]);
            }
    }
    int lo(int i, int j) { return a[j] < a[i] ? j : i; }
    int hi(int i, int j) { return a[i] < a[j] ? j : i; }

    // positions of the min and max of a[l, r), leftmost on ties; needs l < r
    int argmin(int l, int r) { int k = 31 - __builtin_clz(r - l); return lo(mn[k][l], mn[k][r - (1 << k)]); }
    int argmax(int l, int r) { int k = 31 - __builtin_clz(r - l); return hi(mx[k][l], mx[k][r - (1 << k)]); }
    T min(int l, int r) { return a[argmin(l, r)]; }
    T max(int l, int r) { return a[argmax(l, r)]; }
};
