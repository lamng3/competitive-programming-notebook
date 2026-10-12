#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Continuous binary search
// Section: 1. Numeric
// Status: written and tested, not studied yet
//
// Binary search on real numbers: the smallest x in [lo, hi] with valid(x), for a
// valid that is False ... False True ... True. Iterate a fixed number of times
// instead of comparing hi - lo to an epsilon: 100 halvings shrink any double
// range below its precision, and the loop can never spin forever.

template <class F>
double first_true_real(double lo, double hi, F valid, int iters = 100) {
    for (int i = 0; i < iters; i++) {
        double mid = (lo + hi) / 2;
        if (valid(mid)) hi = mid;
        else lo = mid;
    }
    return hi;
}
