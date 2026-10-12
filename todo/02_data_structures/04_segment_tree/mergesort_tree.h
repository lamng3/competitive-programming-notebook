#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Mergesort tree
// Section: 2. Data Structure / Segment Tree
// Status: written and tested, not studied yet
//
// A segment tree whose node keeps its range's values sorted (the merge step of
// merge sort, kept). "How many a[i] < k for i in [l, r)?" splits [l, r) into
// O(log n) nodes and binary searches each: O(log^2 n). The k-th smallest of a range
// is a binary search over values on top of that. O(n log n) memory.

template <class T>
struct MergeSortTree {
    int n;
    vector<vector<T>> t;
    MergeSortTree(const vector<T>& a) : n(a.size()), t(2 * a.size()) {
        for (int i = 0; i < n; i++) t[n + i] = {a[i]};
        for (int i = n - 1; i > 0; i--) merge(t[2 * i].begin(), t[2 * i].end(), t[2 * i + 1].begin(), t[2 * i + 1].end(), back_inserter(t[i]));
    }

    // how many a[i] < k for i in [l, r)
    int count_less(int l, int r, T k) {
        int res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += lower_bound(t[l].begin(), t[l].end(), k) - t[l].begin(), l++;
            if (r & 1) --r, res += lower_bound(t[r].begin(), t[r].end(), k) - t[r].begin();
        }
        return res;
    }

    // the k-th smallest (0-indexed) of a[l, r): binary search over the sorted values
    T kth(int l, int r, int k) {
        const vector<T>& all = t[1].empty() ? t[n] : t[1]; // every value, sorted
        int lo = 0, hi = all.size() - 1;
        while (lo < hi) { // smallest value v with more than k elements <= v
            int mid = (lo + hi) / 2;
            if (count_less(l, r, all[mid]) + count_eq(l, r, all[mid]) > k) hi = mid;
            else lo = mid + 1;
        }
        return all[lo];
    }

    int count_eq(int l, int r, T k) {
        int res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += equal_range(t[l].begin(), t[l].end(), k).second - lower_bound(t[l].begin(), t[l].end(), k), l++;
            if (r & 1) --r, res += equal_range(t[r].begin(), t[r].end(), k).second - lower_bound(t[r].begin(), t[r].end(), k);
        }
        return res;
    }
};
