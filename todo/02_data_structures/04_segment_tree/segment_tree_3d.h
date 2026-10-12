#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Segment tree 3D
// Section: 2. Data Structure / Segment Tree
// Status: written and tested, not studied yet
//
// The 2D idea one level deeper: a segment tree over x of segment trees over y of
// segment trees over z, all iterative. Point assignment and box query in
// O(log n log m log k), commutative monoid. Memory 8 n m k: small dimensions only.

template <class T, class Op>
struct SegTree3D {
    int n, m, k;
    vector<T> t;
    Op op;
    T id;
    SegTree3D(int n, int m, int k, Op op, T id) : n(n), m(m), k(k), t((size_t)8 * n * m * k, id), op(op), id(id) {}
    T& at(int x, int y, int z) { return t[((size_t)x * 2 * m + y) * 2 * k + z]; }

    void set(int x, int y, int z, T v) {
        x += n, y += m, z += k;
        at(x, y, z) = v;
        for (int c = z >> 1; c > 0; c >>= 1) at(x, y, c) = op(at(x, y, 2 * c), at(x, y, 2 * c + 1));
        for (int b = y >> 1; b > 0; b >>= 1)
            for (int c = z; c > 0; c >>= 1) at(x, b, c) = op(at(x, 2 * b, c), at(x, 2 * b + 1, c));
        for (int a = x >> 1; a > 0; a >>= 1)
            for (int b = y; b > 0; b >>= 1)
                for (int c = z; c > 0; c >>= 1) at(a, b, c) = op(at(2 * a, b, c), at(2 * a + 1, b, c));
    }

    T qz(int x, int y, int z1, int z2) {
        T res = id;
        for (z1 += k, z2 += k; z1 < z2; z1 >>= 1, z2 >>= 1) {
            if (z1 & 1) res = op(res, at(x, y, z1++));
            if (z2 & 1) res = op(res, at(x, y, --z2));
        }
        return res;
    }

    T qy(int x, int y1, int y2, int z1, int z2) {
        T res = id;
        for (y1 += m, y2 += m; y1 < y2; y1 >>= 1, y2 >>= 1) {
            if (y1 & 1) res = op(res, qz(x, y1++, z1, z2));
            if (y2 & 1) res = op(res, qz(x, --y2, z1, z2));
        }
        return res;
    }

    // op over the box [x1, x2) x [y1, y2) x [z1, z2)
    T query(int x1, int y1, int z1, int x2, int y2, int z2) {
        T res = id;
        for (x1 += n, x2 += n; x1 < x2; x1 >>= 1, x2 >>= 1) {
            if (x1 & 1) res = op(res, qy(x1++, y1, y2, z1, z2));
            if (x2 & 1) res = op(res, qy(--x2, y1, y2, z1, z2));
        }
        return res;
    }
};
