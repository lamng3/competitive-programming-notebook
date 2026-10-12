#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Double parallel binary search
// Section: 1. Numeric
// Status: written and tested, not studied yet
//
// Parallel binary search where each query's answer is a real number.
// Every query has a monotone predicate in t (False ... True); we want each query's
// threshold. One "round" sorts the queries by their current midpoints and sweeps
// t upward once, so all queries share one pass of the expensive sweep.
//
//   reset()          start a sweep from the beginning
//   advance(t)       move the sweep's state forward to time t (t only grows)
//   check(q)         is query q's predicate true at the current time?
// After `iters` rounds each answer is within (hi - lo) / 2^iters of the threshold.

template <class Reset, class Advance, class Check>
vector<double> parallel_binary_search_real(int q, double lo, double hi, int iters,
                                           Reset reset, Advance advance, Check check) {
    vector<double> L(q, lo), R(q, hi);
    vector<int> order(q);
    for (int it = 0; it < iters; it++) {
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) { return L[a] + R[a] < L[b] + R[b]; });
        reset();
        for (int i : order) {
            double mid = (L[i] + R[i]) / 2;
            advance(mid);
            if (check(i)) R[i] = mid;
            else L[i] = mid;
        }
    }
    return R;
}
