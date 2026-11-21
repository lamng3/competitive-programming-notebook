#pragma once
#include <bits/stdc++.h>
#include <parlay/parallel.h>
using namespace std;

// Hillis and Steele's scan: inclusive prefix sums, out[i] = in[0] + ... + in[i],
// in rounds d = 1, 2, 4, ...: in each round, every element adds the element
// d places to its left. A round may read only the values from the round
// before; tmp is a second buffer of n elements for that.
// Aim: O(n log n) work and O(log n) rounds, for every n, including 0.
// Check: cpunit scan. Time: python3 notebook/parallel/prefix_sums/bench.py.

template <class T>
void scan_hillis_steele(const T* in, T* out, T* tmp, size_t n) {
    // TODO: write it. Until then, out is left as it is.
    (void)in, (void)out, (void)tmp, (void)n;
}
