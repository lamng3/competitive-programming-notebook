#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Fenwick tree 2D sparse sum
// Section: 2. Data Structure / Fenwick Tree
// Status: written and tested, not studied yet
//
// A 2D Fenwick tree when the grid is huge but the update points are known in
// advance (offline). Node i of the outer tree only ever sees the y's of points
// whose x it covers, so it stores just those, sorted, with its own inner Fenwick
// tree: O(P log P) memory instead of n * m. Queries can be anywhere.
//
//   Fenwick2DSparse<ll> f(points);   every (x, y) that will ever be updated
//   f.add(x, y, v);                  (x, y) must be one of them
//   f.sum(x, y)                      sum over points with px <= x and py <= y

template <class T>
struct Fenwick2DSparse {
    vector<long long> xs;
    vector<vector<long long>> ys;
    vector<vector<T>> ft;

    Fenwick2DSparse(vector<pair<long long, long long>> pts) {
        for (auto& p : pts) xs.push_back(p.first);
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        int n = xs.size();
        ys.assign(n + 1, {});
        sort(pts.begin(), pts.end(), [](auto& a, auto& b) { return a.second < b.second; });
        for (auto& [x, y] : pts)
            for (int i = xi(x); i <= n; i += i & -i)
                if (ys[i].empty() || ys[i].back() != y) ys[i].push_back(y);
        ft.resize(n + 1);
        for (int i = 1; i <= n; i++) ft[i].assign(ys[i].size() + 1, 0);
    }

    int xi(long long x) { return lower_bound(xs.begin(), xs.end(), x) - xs.begin() + 1; } // 1-indexed

    void add(long long x, long long y, T v) {
        for (int i = xi(x); i < (int)ft.size(); i += i & -i) {
            int j = lower_bound(ys[i].begin(), ys[i].end(), y) - ys[i].begin() + 1;
            for (; j < (int)ft[i].size(); j += j & -j) ft[i][j] += v;
        }
    }

    T sum(long long x, long long y) {
        T s = 0;
        int i = upper_bound(xs.begin(), xs.end(), x) - xs.begin(); // last x <= query
        for (; i > 0; i -= i & -i) {
            int j = upper_bound(ys[i].begin(), ys[i].end(), y) - ys[i].begin();
            for (; j > 0; j -= j & -j) s += ft[i][j];
        }
        return s;
    }
};
