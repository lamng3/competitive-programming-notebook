#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Sqrt decomposition light range update heavy point query commutative group
// Section: 2. Data Structure / Sqrt Decomposition
// Status: written and tested, not studied yet
//
// Range update in O(1), point query in O(sqrt n), for a commutative group.
// A range update is two point updates on the difference array d (d[l] += v,
// d[r] -= v), plus the block total of each. The value at i is the prefix of d:
// the totals of the whole blocks before i, then the elements of i's block up to i.

template <class T, class Op, class Inv>
struct SqrtRangeUpdate {
    int n, B;
    vector<T> d, blk;
    Op op;
    Inv inv;
    T id;
    SqrtRangeUpdate(int n, Op op, Inv inv, T id) : n(n), d(n + 1, id), op(op), inv(inv), id(id) {
        B = max(1, (int)sqrt(n));
        blk.assign(n / B + 2, id);
    }

    void point(int i, T v) { d[i] = op(d[i], v); blk[i / B] = op(blk[i / B], v); }

    // a[l, r) op= v
    void update(int l, int r, T v) { point(l, v); point(r, inv(v)); }

    T get(int i) {
        T res = id;
        for (int b = 0; b < i / B; b++) res = op(res, blk[b]);
        for (int k = i / B * B; k <= i; k++) res = op(res, d[k]);
        return res;
    }
};
