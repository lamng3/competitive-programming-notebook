#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Segment tree wide
// Section: 2. Data Structure / Segment Tree
// Status: written and tested, not studied yet
//
// A segment tree with B = 16 children per node instead of 2: depth log_16 n, so a
// point update touches ~log2(n) / 4 nodes, and each node's children sit next to
// each other in memory (cache friendly). Here for prefix sums: level 0 is the array,
// level d + 1 holds sums of 16 consecutive level-d entries. A prefix query adds, at
// each level, the siblings to the left of the path: at most 15 per level.

template <class T>
struct WideSegTree {
    static const int B = 16;
    vector<vector<T>> lv; // lv[d][i] = sum of block i at level d
    WideSegTree(int n) {
        do {
            lv.push_back(vector<T>(n, 0));
            n = (n + B - 1) / B;
        } while (lv.back().size() > 1);
    }

    void add(int i, T v) {
        for (auto& level : lv) {
            level[i] += v;
            i /= B;
        }
    }

    // a[0] + ... + a[i - 1]
    T prefix(int i) {
        T s = 0;
        for (auto& level : lv) {
            int start = i - i % B; // siblings left of i in its group
            for (int j = start; j < i; j++) s += level[j];
            i /= B;
        }
        return s;
    }

    T sum(int l, int r) { return prefix(r) - prefix(l); } // a[l, r)
};
