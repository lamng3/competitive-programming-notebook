#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Static range query processor 3D
// Section: 2. Data Structure / Static Range Query Processor
// Status: written and tested, not studied yet
//
// O(1) box queries on a fixed 3D array for a commutative group: 3D prefixes, and
// inclusion-exclusion over the 8 corners of the box (a corner taking an odd number
// of lower bounds enters inverted).

template <class T, class Op, class Inv>
struct StaticRangeQuery3D {
    int n, m, k;
    vector<T> P;
    Op op;
    Inv inv;
    T id;
    T& at(int x, int y, int z) { return P[((size_t)x * (m + 1) + y) * (k + 1) + z]; }

    StaticRangeQuery3D(const vector<vector<vector<T>>>& a, Op op, Inv inv, T id)
        : n(a.size()), m(a[0].size()), k(a[0][0].size()), P((size_t)(n + 1) * (m + 1) * (k + 1), id), op(op), inv(inv), id(id) {
        for (int x = 1; x <= n; x++)
            for (int y = 1; y <= m; y++)
                for (int z = 1; z <= k; z++) {
                    T s = a[x - 1][y - 1][z - 1];
                    for (int mask = 1; mask < 8; mask++) { // the 7 smaller prefixes, signed
                        T v = at(x - (mask & 1), y - (mask >> 1 & 1), z - (mask >> 2 & 1));
                        s = op(s, __builtin_popcount(mask) % 2 ? v : inv(v));
                    }
                    at(x, y, z) = s;
                }
    }

    // op over [x1, x2) x [y1, y2) x [z1, z2)
    T query(int x1, int y1, int z1, int x2, int y2, int z2) {
        T s = id;
        for (int mask = 0; mask < 8; mask++) {
            T v = at(mask & 1 ? x1 : x2, mask & 2 ? y1 : y2, mask & 4 ? z1 : z2);
            s = op(s, __builtin_popcount(mask) % 2 ? inv(v) : v);
        }
        return s;
    }
};
