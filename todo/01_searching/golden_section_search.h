#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Golden section search
// Section: 1. Numeric
// Status: written and tested, not studied yet
//
// Maximize a unimodal f on the reals [lo, hi]. Ternary search with the probes at
// the golden ratio: after a step, one old probe lands exactly where the next round
// needs it, so each round costs one new evaluation and shrinks the range by
// 1 / phi ~ 0.618 (ternary search pays two evaluations for 2/3).

template <class F>
double golden_max(double lo, double hi, F f, int iters = 200) {
    const double r = (sqrt(5.0) - 1) / 2; // 1 / phi
    double x1 = hi - r * (hi - lo), x2 = lo + r * (hi - lo);
    double f1 = f(x1), f2 = f(x2);
    for (int i = 0; i < iters; i++) {
        if (f1 < f2) {
            lo = x1;
            x1 = x2, f1 = f2;
            x2 = lo + r * (hi - lo);
            f2 = f(x2);
        } else {
            hi = x2;
            x2 = x1, f2 = f1;
            x1 = hi - r * (hi - lo);
            f1 = f(x1);
        }
    }
    return (lo + hi) / 2;
}
