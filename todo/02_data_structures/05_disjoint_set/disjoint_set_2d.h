#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Disjoint set 2D
// Section: 2. Data Structure / Disjoint Set
// Status: written and tested, not studied yet
//
// Union-find over the cells of an n x m grid: a cell (r, c) is element r * m + c.
// unite_neighbors(same) joins every pair of 4-adjacent cells for which same(a, b)
// says they belong together, so components() counts the regions of a picture and
// size(r, c) is the area of the region containing (r, c).

struct DSU2D {
    int n, m;
    vector<int> par, sz;
    int comps;
    DSU2D(int n, int m) : n(n), m(m), par(n * m), sz(n * m, 1), comps(n * m) { iota(par.begin(), par.end(), 0); }

    int id(int r, int c) { return r * m + c; }
    int find(int v) { return par[v] == v ? v : par[v] = find(par[v]); }
    int find(int r, int c) { return find(id(r, c)); }

    bool unite(int r1, int c1, int r2, int c2) {
        int a = find(r1, c1), b = find(r2, c2);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a, sz[a] += sz[b], comps--;
        return true;
    }

    template <class Same>
    void unite_neighbors(Same same) {
        for (int r = 0; r < n; r++)
            for (int c = 0; c < m; c++) {
                if (r + 1 < n && same(r, c, r + 1, c)) unite(r, c, r + 1, c);
                if (c + 1 < m && same(r, c, r, c + 1)) unite(r, c, r, c + 1);
            }
    }

    int size(int r, int c) { return sz[find(r, c)]; }
    int components() { return comps; }
};
