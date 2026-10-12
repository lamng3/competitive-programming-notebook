#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Parallel binary search
// Section: 1. Numeric
// Status: written and tested, not studied yet
//
// Many queries, each asking "after how many updates (of a fixed list of T updates)
// does my condition first hold?", with each condition monotone in the number of
// updates. Binary searching each query alone replays the updates per query.
// Instead, run all searches in lockstep: each round, sort queries by their
// midpoint, replay the updates once from the start, and check every query when the
// replay reaches its midpoint. log T rounds, each O(T + Q) plus the checks.
//
//   reset()      clear the structure (state before any update)
//   apply(t)     apply update t (0-indexed)
//   check(q)     does query q hold now?
// Returns, per query, the smallest number of updates after which it holds,
// or T + 1 if it never does.

template <class Reset, class Apply, class Check>
vector<int> parallel_binary_search(int q, int T, Reset reset, Apply apply, Check check) {
    vector<int> L(q, 0), R(q, T + 1); // answer in [L, R]; R = T + 1 means "never"
    while (true) {
        vector<pair<int, int>> todo; // (mid, query)
        for (int i = 0; i < q; i++) if (L[i] < R[i]) todo.push_back({(L[i] + R[i]) / 2, i});
        if (todo.empty()) break;
        sort(todo.begin(), todo.end());
        reset();
        int done = 0; // updates applied so far
        for (auto [mid, i] : todo) {
            while (done < mid) apply(done++);
            if (check(i)) R[i] = mid;
            else L[i] = mid + 1;
        }
    }
    return L;
}
