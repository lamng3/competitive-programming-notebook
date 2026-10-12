#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Discrete ternary search
// Section: 1. Numeric
// Status: written and tested, not studied yet
//
// Maximize a unimodal f on the integers [lo, hi]. On integers, ternary search is
// really a binary search on the slope: the first x with f(x) >= f(x + 1) is the top.
// Needs f strictly increasing then strictly decreasing (a plateau only at the top),
// otherwise "which side am I on" is undecidable from two points.

template <class F>
long long ternary_max_int(long long lo, long long hi, F f) {
    long long left = lo, right = hi, ans = hi;
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        if (mid == hi || f(mid) >= f(mid + 1)) { // at or past the top
            ans = mid;
            right = mid - 1;
        } else left = mid + 1;
    }
    return ans;
}
