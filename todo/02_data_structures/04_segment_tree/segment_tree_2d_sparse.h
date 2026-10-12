#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Segment tree 2D sparse
// Section: 2. Data Structure / Segment Tree
// Status: written and tested, not studied yet
//
// A 2D segment tree on huge coordinates, when the points that will be assigned are
// known in advance. The outer tree is over the sorted distinct x's; each outer node
// keeps the sorted y's of its points and an inner segment tree over them. An inner
// leaf combines the values of all points in the node with that y, so after setting a
// point, each ancestor recomputes that one leaf from its two children.
// Point assignment and rectangle query O(log^2 P), commutative monoid, O(P log P) memory.

template <class T, class Op>
struct SegTree2DSparse {
    int n;
    vector<long long> xs;
    vector<vector<long long>> ys;
    vector<vector<T>> t;
    Op op;
    T id;

    SegTree2DSparse(vector<pair<long long, long long>> pts, Op op, T id) : op(op), id(id) {
        for (auto& p : pts) xs.push_back(p.first);
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        n = xs.size();
        ys.assign(2 * n, {});
        for (auto& [x, y] : pts)
            for (int i = xi(x) + n; i > 0; i >>= 1) ys[i].push_back(y);
        t.resize(2 * n);
        for (int i = 1; i < 2 * n; i++) {
            sort(ys[i].begin(), ys[i].end());
            ys[i].erase(unique(ys[i].begin(), ys[i].end()), ys[i].end());
            t[i].assign(2 * ys[i].size(), id);
        }
    }

    int xi(long long x) { return lower_bound(xs.begin(), xs.end(), x) - xs.begin(); }

    T leaf(int u, long long y) { // the value at y in node u, id if u has no point at y
        auto it = lower_bound(ys[u].begin(), ys[u].end(), y);
        if (it == ys[u].end() || *it != y) return id;
        return t[u][ys[u].size() + (it - ys[u].begin())];
    }

    void put(int u, long long y, T v) {
        int k = ys[u].size(), j = lower_bound(ys[u].begin(), ys[u].end(), y) - ys[u].begin() + k;
        t[u][j] = v;
        for (j >>= 1; j > 0; j >>= 1) t[u][j] = op(t[u][2 * j], t[u][2 * j + 1]);
    }

    // set the value of point (x, y), which must be one of the points given
    void set(long long x, long long y, T v) {
        int u = xi(x) + n;
        put(u, y, v);
        for (u >>= 1; u > 0; u >>= 1) put(u, y, op(leaf(2 * u, y), leaf(2 * u + 1, y)));
    }

    T inner(int u, long long y1, long long y2) { // over ys in [y1, y2)
        int k = ys[u].size();
        int l = lower_bound(ys[u].begin(), ys[u].end(), y1) - ys[u].begin() + k;
        int r = lower_bound(ys[u].begin(), ys[u].end(), y2) - ys[u].begin() + k;
        T res = id;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = op(res, t[u][l++]);
            if (r & 1) res = op(res, t[u][--r]);
        }
        return res;
    }

    // op over points with x in [x1, x2) and y in [y1, y2)
    T query(long long x1, long long y1, long long x2, long long y2) {
        T res = id;
        for (int l = xi(x1) + n, r = xi(x2) + n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = op(res, inner(l++, y1, y2));
            if (r & 1) res = op(res, inner(--r, y1, y2));
        }
        return res;
    }
};
