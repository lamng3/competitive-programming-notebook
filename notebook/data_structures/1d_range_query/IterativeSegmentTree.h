#pragma once
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+5;
int tree[2 * N];

template <typename T>
struct IterativeSegmentTree {
    int n;
    
    // build the tree in O(n)
    void build() {
        for (int i = n-1; i > 0; i--) {
            tree[i] = tree[i << 1] + tree[i << 1 | 1];
        }
    }

    // point update in O(log n): set A[p] = value
    void update(int p, int v) {
        // set value at the leaf, then walk up the tree
        for (tree[p += n] = value; p > 1; p >>= 1) {
            // tree[p ^ 1] safely gets the sibling of p
            tree[p >> 1] = tree[p] + tree[p ^ 1];
        }
    }

    int query(int l, int r) {
        int res = 0;
        // walk up the tree from both ends
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            // if l is a right child, include it and move right
            if (l & 1) res += tree[l++];
            // if r is a right child, include its left sibling
            if (r & 1) res += tree[--r];
        }
        return res;
    }
};
