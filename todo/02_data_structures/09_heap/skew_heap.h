#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Skew heap
// Section: 2. Data Structure / Heap
// Status: written and tested, not studied yet
//
// A meldable min-heap: merge two heaps in O(log n) amortized, so push is "merge with
// a one-node heap" and pop is "merge the root's two children". Skew heap merge walks
// down the right spines and swaps children at every step, which keeps right spines
// short on average. A lazy "add to every key" tag rides on each node, pushed down
// when the node is touched: it is what makes merging heaps of shifted keys cheap
// (slope trick, DSU on trees with heaps). Nodes live in one pool; a heap is a root
// index, -1 for empty.

template <class T>
struct SkewHeap {
    vector<T> key, lazy;
    vector<int> l, r;

    int make(T k) { key.push_back(k), lazy.push_back(0), l.push_back(-1), r.push_back(-1); return key.size() - 1; }

    void push_down(int u) {
        if (lazy[u] == 0) return;
        for (int c : {l[u], r[u]}) if (c >= 0) key[c] += lazy[u], lazy[c] += lazy[u];
        lazy[u] = 0;
    }

    int merge(int a, int b) {
        if (a < 0) return b;
        if (b < 0) return a;
        if (key[b] < key[a]) swap(a, b);
        push_down(a);
        r[a] = merge(r[a], b);
        swap(l[a], r[a]);
        return a;
    }

    int push(int h, T k) { return merge(h, make(k)); }
    T top(int h) { return key[h]; }
    int pop(int h) { push_down(h); return merge(l[h], r[h]); }
    void add_all(int h, T v) { if (h >= 0) key[h] += v, lazy[h] += v; } // every key in h += v
};
