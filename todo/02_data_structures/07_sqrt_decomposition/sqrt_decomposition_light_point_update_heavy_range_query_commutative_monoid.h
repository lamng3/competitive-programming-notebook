#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Sqrt decomposition light point update heavy range query commutative monoid
// Section: 2. Data Structure / Sqrt Decomposition
// Status: written and tested, not studied yet
//
// Point update in O(1), range query in O(sqrt n), for a commutative monoid (no
// inverse: min, max, gcd, OR). An update writes the value and marks its block dirty;
// a query recomputes the dirty blocks it reads, once, and then combines whole blocks
// plus the partial ends. Every update dirties at most one block, so the recompute
// work is O(B) per update amortized, and a query is O(n / B + B).

template <class T, class Op>
struct SqrtQueryHeavy {
    int n, B;
    vector<T> a, blk;
    vector<char> dirty;
    Op op;
    T id;
    SqrtQueryHeavy(const vector<T>& a, Op op, T id) : n(a.size()), a(a), op(op), id(id) {
        B = max(1, (int)sqrt(n));
        blk.assign(n / B + 1, id), dirty.assign(n / B + 1, 1);
    }

    void set(int i, T v) { a[i] = v; dirty[i / B] = 1; }

    T block(int b) {
        if (dirty[b]) {
            blk[b] = id;
            for (int i = b * B; i < min(n, (b + 1) * B); i++) blk[b] = op(blk[b], a[i]);
            dirty[b] = 0;
        }
        return blk[b];
    }

    T query(int l, int r) { // a[l, r)
        T res = id;
        while (l < r && l % B) res = op(res, a[l++]);
        while (l + B <= r) res = op(res, block(l / B)), l += B;
        while (l < r) res = op(res, a[l++]);
        return res;
    }
};
