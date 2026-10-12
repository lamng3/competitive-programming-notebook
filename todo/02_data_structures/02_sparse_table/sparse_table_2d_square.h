#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Sparse table 2D square
// Section: 2. Data Structure / Sparse Table
// Status: written and tested, not studied yet
//
// When every query is a k x k square, one size index is enough: t[s][i][j] = op
// over the 2^s x 2^s square at (i, j). A k x k square is covered by four 2^s
// squares (s = floor(log2 k)), overlapping. O(n m log) memory instead of log^2.

template <class T, class Op>
struct SparseTable2DSquare {
    int n, m;
    vector<vector<vector<T>>> t;
    Op op;
    SparseTable2DSquare(const vector<vector<T>>& g, Op op) : n(g.size()), m(g[0].size()), op(op) {
        int K = 32 - __builtin_clz(min(n, m));
        t.assign(K, g);
        for (int s = 1; s < K; s++) {
            int h = 1 << (s - 1);
            for (int i = 0; i + 2 * h <= n; i++)
                for (int j = 0; j + 2 * h <= m; j++)
                    t[s][i][j] = op(op(t[s - 1][i][j], t[s - 1][i + h][j]), op(t[s - 1][i][j + h], t[s - 1][i + h][j + h]));
        }
    }

    // op over the k x k square with top-left corner (r, c)
    T query(int r, int c, int k) {
        int s = 31 - __builtin_clz(k), d = k - (1 << s);
        return op(op(t[s][r][c], t[s][r + d][c]), op(t[s][r][c + d], t[s][r + d][c + d]));
    }
};
