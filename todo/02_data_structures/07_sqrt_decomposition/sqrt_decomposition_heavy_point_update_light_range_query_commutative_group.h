#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Sqrt decomposition heavy point update light range query commutative group
// Section: 2. Data Structure / Sqrt Decomposition
// Status: written and tested, not studied yet
//
// Point update in O(sqrt n), range query in O(1), for a commutative group.
// Keep prefix sums inside each block and prefix sums over whole blocks:
//   prefix(i) = blockpre[i / B] + inner[i]
// An update rewrites the inner prefixes of its block (O(B)) and the block prefixes
// after it (O(n / B)). Useful when queries far outnumber updates.

template <class T, class Op, class Inv>
struct SqrtUpdateHeavy {
    int n, B;
    vector<T> a, inner, blockpre; // inner[i] = op over its block up to and including i
    Op op;
    Inv inv;
    T id;
    SqrtUpdateHeavy(const vector<T>& a, Op op, Inv inv, T id) : n(a.size()), a(a), inner(a.size()), op(op), inv(inv), id(id) {
        B = max(1, (int)sqrt(n));
        blockpre.assign(n / B + 2, id);
        for (int b = 0; b * B < n; b++) rebuild(b);
    }

    void rebuild(int b) {
        for (int i = b * B; i < min(n, (b + 1) * B); i++) inner[i] = i == b * B ? a[i] : op(inner[i - 1], a[i]);
        for (int c = b; c * B < n; c++) blockpre[c + 1] = op(blockpre[c], inner[min(n, (c + 1) * B) - 1]);
    }

    void set(int i, T v) { a[i] = v; rebuild(i / B); }

    T prefix(int i) { return i == 0 ? id : op(blockpre[(i - 1) / B], inner[i - 1]); } // a[0, i)
    T query(int l, int r) { return op(prefix(r), inv(prefix(l))); }                  // a[l, r)
};
