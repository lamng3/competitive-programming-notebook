#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Segment tree 2D
// Section: 2. Data Structure / Segment Tree
// Status: written and tested, not studied yet
//
// A segment tree over rows whose every node is a segment tree over columns, both
// iterative and bottom-up. Point assignment and rectangle query in O(log n log m)
// for a commutative monoid (op, identity). 0-indexed, half-open rectangles.

template <class T, class Op>
struct SegTree2D {
    int n, m;
    vector<vector<T>> t;
    Op op;
    T id;
    SegTree2D(int n, int m, Op op, T id) : n(n), m(m), t(2 * n, vector<T>(2 * m, id)), op(op), id(id) {}

    void set(int x, int y, T v) {
        x += n, y += m;
        t[x][y] = v;
        for (int j = y >> 1; j > 0; j >>= 1) t[x][j] = op(t[x][2 * j], t[x][2 * j + 1]);
        for (x >>= 1; x > 0; x >>= 1) // the row node at x combines its two children, column by column
            for (int j = y; j > 0; j >>= 1) t[x][j] = op(t[2 * x][j], t[2 * x + 1][j]);
    }

    T row_query(int x, int y1, int y2) {
        T res = id;
        for (y1 += m, y2 += m; y1 < y2; y1 >>= 1, y2 >>= 1) {
            if (y1 & 1) res = op(res, t[x][y1++]);
            if (y2 & 1) res = op(res, t[x][--y2]);
        }
        return res;
    }

    // op over rows [x1, x2), columns [y1, y2)
    T query(int x1, int y1, int x2, int y2) {
        T res = id;
        for (x1 += n, x2 += n; x1 < x2; x1 >>= 1, x2 >>= 1) {
            if (x1 & 1) res = op(res, row_query(x1++, y1, y2));
            if (x2 & 1) res = op(res, row_query(--x2, y1, y2));
        }
        return res;
    }
};
