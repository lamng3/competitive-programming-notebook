#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Static range query processor 2D
// Section: 2. Data Structure / Static Range Query Processor
// Status: written and tested, not studied yet
//
// O(1) rectangle queries on a fixed grid for a commutative group (sums, XOR):
// 2D prefixes and inclusion-exclusion.
//   P[i][j] = op over g[0..i) x [0..j)
//   rect = P[r2][c2] - P[r1][c2] - P[r2][c1] + P[r1][c1], with "-" as op by the inverse

template <class T, class Op, class Inv>
struct StaticRangeQuery2D {
    vector<vector<T>> P;
    Op op;
    Inv inv;
    StaticRangeQuery2D(const vector<vector<T>>& g, Op op, Inv inv, T id) : op(op), inv(inv) {
        int n = g.size(), m = n ? g[0].size() : 0;
        P.assign(n + 1, vector<T>(m + 1, id));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                P[i + 1][j + 1] = op(op(g[i][j], P[i][j + 1]), op(P[i + 1][j], inv(P[i][j])));
    }

    // op over rows [r1, r2), columns [c1, c2)
    T query(int r1, int c1, int r2, int c2) {
        return op(op(P[r2][c2], inv(P[r1][c2])), op(inv(P[r2][c1]), P[r1][c1]));
    }
};
