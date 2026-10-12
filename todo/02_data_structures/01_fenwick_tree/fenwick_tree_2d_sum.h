#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Fenwick tree 2D sum
// Section: 2. Data Structure / Fenwick Tree
// Status: written and tested, not studied yet
//
// A Fenwick tree of Fenwick trees: point add, prefix-rectangle sum, both
// O(log n log m). 1-indexed like FenwickTree.h; rect(x1, y1, x2, y2) is
// inclusion-exclusion over four prefix sums.

template <class T>
struct Fenwick2D {
    int n, m;
    vector<vector<T>> ft;
    Fenwick2D(int n, int m) : n(n), m(m), ft(n + 1, vector<T>(m + 1, 0)) {}

    void add(int x, int y, T v) {
        for (int i = x; i <= n; i += i & -i)
            for (int j = y; j <= m; j += j & -j) ft[i][j] += v;
    }

    // sum over [1..x] x [1..y]
    T sum(int x, int y) {
        T s = 0;
        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j) s += ft[i][j];
        return s;
    }

    T rect(int x1, int y1, int x2, int y2) {
        return sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1);
    }
};
