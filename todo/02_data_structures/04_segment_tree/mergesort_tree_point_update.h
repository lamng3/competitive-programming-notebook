#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Mergesort tree point update
// Section: 2. Data Structure / Segment Tree
// Status: written and tested, not studied yet
//
// A merge sort tree that also allows point assignment, offline: every value a
// position will ever hold is known up front (the initial array plus the updates).
// Each node keeps the sorted list of values its positions may ever hold, plus a
// Fenwick tree counting which are present now. An update is -1 at the old value and
// +1 at the new one in every node above the position; a count query is the usual
// O(log n) nodes, each a binary search plus a Fenwick prefix: O(log^2 n).

template <class T>
struct MergeSortTreeUpdatable {
    int n;
    vector<T> a;
    vector<vector<T>> vals; // per node: values that may appear, sorted, unique
    vector<vector<int>> ft;  // per node: Fenwick tree over vals

    // future: every (position, value) assignment that will happen
    MergeSortTreeUpdatable(const vector<T>& init, const vector<pair<int, T>>& future) : n(init.size()), a(init), vals(2 * init.size()), ft(2 * init.size()) {
        auto note = [&](int i, T v) { for (i += n; i > 0; i >>= 1) vals[i].push_back(v); };
        for (int i = 0; i < n; i++) note(i, init[i]);
        for (auto& [i, v] : future) note(i, v);
        for (int i = 1; i < 2 * n; i++) {
            sort(vals[i].begin(), vals[i].end());
            vals[i].erase(unique(vals[i].begin(), vals[i].end()), vals[i].end());
            ft[i].assign(vals[i].size() + 1, 0);
        }
        for (int i = 0; i < n; i++) bump(i, a[i], 1);
    }

    void bump(int i, T v, int d) {
        for (i += n; i > 0; i >>= 1) {
            int j = lower_bound(vals[i].begin(), vals[i].end(), v) - vals[i].begin() + 1;
            for (; j < (int)ft[i].size(); j += j & -j) ft[i][j] += d;
        }
    }

    void assign(int i, T v) {
        bump(i, a[i], -1);
        a[i] = v;
        bump(i, v, 1);
    }

    int node_less(int u, T k) {
        int j = lower_bound(vals[u].begin(), vals[u].end(), k) - vals[u].begin(), s = 0;
        for (; j > 0; j -= j & -j) s += ft[u][j];
        return s;
    }

    // how many a[i] < k for i in [l, r)
    int count_less(int l, int r, T k) {
        int res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += node_less(l++, k);
            if (r & 1) res += node_less(--r, k);
        }
        return res;
    }
};
