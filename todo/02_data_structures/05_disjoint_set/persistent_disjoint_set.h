#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Persistent disjoint set
// Section: 2. Data Structure / Disjoint Set
// Status: written and tested, not studied yet
//
// Union-find where every unite makes a new version and old versions stay queryable:
// "were a and b connected after the first k unions?" for any k, online.
// Path compression rewrites history, so it is out; union by size alone keeps every
// find O(log n) steps. parent[] and size[] become persistent arrays (a path-copying
// segment tree over the indices), so each step costs O(log n): find is O(log^2 n),
// unite makes O(log n) new nodes.

struct PersistentDSU {
    int n;
    vector<int> L, R, val; // persistent segment tree nodes; node 0 unused
    vector<int> roots;     // version v: roots[2v] = parent array, roots[2v+1] = size array

    PersistentDSU(int n) : n(n), L(1), R(1), val(1) {
        vector<int> par(n), one(n, 1);
        iota(par.begin(), par.end(), 0);
        roots = {build(par, 0, n - 1), build(one, 0, n - 1)};
    }

    int node(int l, int r, int v) { L.push_back(l), R.push_back(r), val.push_back(v); return L.size() - 1; }
    int build(const vector<int>& a, int lo, int hi) {
        if (lo == hi) return node(0, 0, a[lo]);
        int mid = (lo + hi) / 2;
        int l = build(a, lo, mid), r = build(a, mid + 1, hi);
        return node(l, r, 0);
    }
    int get(int u, int i, int lo, int hi) {
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (i <= mid) u = L[u], hi = mid;
            else u = R[u], lo = mid + 1;
        }
        return val[u];
    }
    int set(int u, int i, int v, int lo, int hi) { // a new root; u is untouched
        if (lo == hi) return node(0, 0, v);
        int mid = (lo + hi) / 2;
        if (i <= mid) return node(set(L[u], i, v, lo, mid), R[u], 0);
        return node(L[u], set(R[u], i, v, mid + 1, hi), 0);
    }

    int versions() { return roots.size() / 2; } // version 0 = nothing united

    int find(int ver, int x) {
        int pr = roots[2 * ver];
        for (int p; (p = get(pr, x, 0, n - 1)) != x; ) x = p;
        return x;
    }

    // unite a and b on top of version ver; returns the new version's number
    int unite(int ver, int a, int b) {
        int pr = roots[2 * ver], sr = roots[2 * ver + 1];
        a = find(ver, a), b = find(ver, b);
        if (a != b) {
            int sa = get(sr, a, 0, n - 1), sb = get(sr, b, 0, n - 1);
            if (sa < sb) swap(a, b), swap(sa, sb);
            pr = set(pr, b, a, 0, n - 1);
            sr = set(sr, a, sa + sb, 0, n - 1);
        }
        roots.push_back(pr), roots.push_back(sr);
        return versions() - 1;
    }

    bool same(int ver, int a, int b) { return find(ver, a) == find(ver, b); }
    int size(int ver, int x) { return get(roots[2 * ver + 1], find(ver, x), 0, n - 1); }
};
