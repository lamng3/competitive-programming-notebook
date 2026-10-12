#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Range add query sum solver 2D
// Section: 2. Data Structure / Fenwick Tree
// Status: written and tested, not studied yet
//
// Rectangle add and rectangle sum. The 1D trick (range_add_query_sum_solver.h)
// extended to two dimensions: a point update at (i, j) of value d contributes to
// the prefix sum S(x, y) the amount d (x - i + 1)(y - j + 1), which expands into four
// terms: d, d*i, d*j, d*i*j. Keep one 2D Fenwick tree per term.
// A rectangle add is four point updates at its corners (2D difference array).

template <class T>
struct RectAddRectSum {
    int n, m;
    vector<vector<T>> t[4]; // d, d*i, d*j, d*i*j
    RectAddRectSum(int n, int m) : n(n), m(m) {
        for (auto& v : t) v.assign(n + 2, vector<T>(m + 2, 0));
    }

    void point(int x, int y, T d) {
        for (int i = x; i <= n + 1; i += i & -i)
            for (int j = y; j <= m + 1; j += j & -j) {
                t[0][i][j] += d;
                t[1][i][j] += d * x;
                t[2][i][j] += d * y;
                t[3][i][j] += d * x * y;
            }
    }

    // a[x1..x2][y1..y2] += d
    void add(int x1, int y1, int x2, int y2, T d) {
        point(x1, y1, d), point(x1, y2 + 1, -d), point(x2 + 1, y1, -d), point(x2 + 1, y2 + 1, d);
    }

    T prefix(int x, int y) {
        T s[4] = {0, 0, 0, 0};
        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j)
                for (int k = 0; k < 4; k++) s[k] += t[k][i][j];
        return s[0] * (x + 1) * (y + 1) - s[1] * (y + 1) - s[2] * (x + 1) + s[3];
    }

    T sum(int x1, int y1, int x2, int y2) {
        return prefix(x2, y2) - prefix(x1 - 1, y2) - prefix(x2, y1 - 1) + prefix(x1 - 1, y1 - 1);
    }
};
