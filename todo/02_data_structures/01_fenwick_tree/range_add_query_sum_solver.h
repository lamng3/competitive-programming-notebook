#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Range add query sum solver
// Section: 2. Data Structure / Fenwick Tree
// Status: written and tested, not studied yet
//
// Range add and range sum with two Fenwick trees, no lazy propagation.
// Adding v to a[l..r] changes the prefix sum S(x) by a function linear in x:
//   S(x) = sum_{i<=x} a_i = B1(x) * x - B2(x)
// where B1 is a Fenwick tree of the added slopes and B2 of the offsets.
// Add v on [l, r]: B1 += v at l, -v at r+1; B2 += v(l-1) at l, -v r at r+1.

template <class T>
struct RangeAddRangeSum {
    int n;
    vector<T> b1, b2;
    RangeAddRangeSum(int n) : n(n), b1(n + 2, 0), b2(n + 2, 0) {}

    void upd(vector<T>& b, int i, T v) { for (; i <= n + 1; i += i & -i) b[i] += v; }
    T qry(vector<T>& b, int i) { T s = 0; for (; i > 0; i -= i & -i) s += b[i]; return s; }

    // a[l..r] += v, 1-indexed
    void add(int l, int r, T v) {
        upd(b1, l, v), upd(b1, r + 1, -v);
        upd(b2, l, v * (l - 1)), upd(b2, r + 1, -v * r);
    }

    T prefix(int x) { return qry(b1, x) * x - qry(b2, x); }
    T sum(int l, int r) { return prefix(r) - prefix(l - 1); }
};
