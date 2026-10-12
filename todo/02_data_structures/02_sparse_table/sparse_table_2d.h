#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Sparse table 2D
// Section: 2. Data Structure / Sparse Table
// Status: written and tested, not studied yet
//
// O(1) rectangle queries for an idempotent operation on an n x m grid.
// t[a][b][i][j] = op over the 2^a x 2^b block at (i, j); a rectangle is covered by
// four (possibly overlapping) such blocks. O(n m log n log m) memory and build.

template <class T, class Op>
struct SparseTable2D {
    int n, m, A, B;
    vector<vector<vector<vector<T>>>> t;
    Op op;
    SparseTable2D(const vector<vector<T>>& g, Op op) : n(g.size()), m(g[0].size()), op(op) {
        A = 32 - __builtin_clz(n), B = 32 - __builtin_clz(m);
        t.assign(A, vector<vector<vector<T>>>(B, g));
        for (int a = 0; a < A; a++)
            for (int b = 0; b < B; b++) {
                if (a == 0 && b == 0) continue;
                for (int i = 0; i + (1 << a) <= n; i++)
                    for (int j = 0; j + (1 << b) <= m; j++)
                        t[a][b][i][j] = a ? op(t[a - 1][b][i][j], t[a - 1][b][i + (1 << (a - 1))][j])
                                          : op(t[a][b - 1][i][j], t[a][b - 1][i][j + (1 << (b - 1))]);
            }
    }

    // op over rows [r1, r2) and columns [c1, c2), both nonempty
    T query(int r1, int c1, int r2, int c2) {
        int a = 31 - __builtin_clz(r2 - r1), b = 31 - __builtin_clz(c2 - c1);
        int r = r2 - (1 << a), c = c2 - (1 << b);
        return op(op(t[a][b][r1][c1], t[a][b][r1][c]), op(t[a][b][r][c1], t[a][b][r][c]));
    }
};
