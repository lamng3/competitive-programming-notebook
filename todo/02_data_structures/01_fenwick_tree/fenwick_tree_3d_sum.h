#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Fenwick tree 3D sum
// Section: 2. Data Structure / Fenwick Tree
// Status: written and tested, not studied yet
//
// Three nested Fenwick loops: point add and prefix-box sum in O(log^3 n).
// box() is inclusion-exclusion over the 8 corners of the box.

template <class T>
struct Fenwick3D {
    int n, m, k;
    vector<T> ft; // flattened (n+1) x (m+1) x (k+1)
    Fenwick3D(int n, int m, int k) : n(n), m(m), k(k), ft((size_t)(n + 1) * (m + 1) * (k + 1), 0) {}
    T& at(int x, int y, int z) { return ft[((size_t)x * (m + 1) + y) * (k + 1) + z]; }

    void add(int x, int y, int z, T v) {
        for (int i = x; i <= n; i += i & -i)
            for (int j = y; j <= m; j += j & -j)
                for (int l = z; l <= k; l += l & -l) at(i, j, l) += v;
    }

    T sum(int x, int y, int z) {
        T s = 0;
        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j)
                for (int l = z; l > 0; l -= l & -l) s += at(i, j, l);
        return s;
    }

    T box(int x1, int y1, int z1, int x2, int y2, int z2) {
        T s = 0;
        for (int mask = 0; mask < 8; mask++) {
            int x = mask & 1 ? x1 - 1 : x2, y = mask & 2 ? y1 - 1 : y2, z = mask & 4 ? z1 - 1 : z2;
            T v = sum(x, y, z);
            s += __builtin_popcount(mask) % 2 ? -v : v;
        }
        return s;
    }
};
