#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Solve cubic equation
// Section: 1. Numeric
// Status: written and tested, not studied yet
//
// Real roots of a x^3 + b x^2 + c x + d = 0 (a != 0), sorted, a repeated root once.
// The closed forms (Cardano, the trigonometric form) branch on the sign of a
// discriminant, and rounding makes "zero" look positive: a double root gets lost.
// Instead use the derivative. Its roots (a quadratic) cut the line into pieces where
// the cubic is monotone, so each piece holds at most one root, found by bisection.
// A critical point where the cubic is (nearly) zero is itself a double root.

vector<double> solve_cubic(double a, double b, double c, double d) {
    double B = b / a, C = c / a, D = d / a; // monic: x^3 + B x^2 + C x + D
    auto f = [&](double x) { return ((x + B) * x + C) * x + D; };
    double R = 1 + max({fabs(B), fabs(C), fabs(D)}); // every root lies in [-R, R]
    vector<double> cuts = {-R};
    double disc = 4 * B * B - 12 * C; // roots of 3x^2 + 2Bx + C
    if (disc > 0) {
        double s = sqrt(disc);
        cuts.push_back((-2 * B - s) / 6);
        cuts.push_back((-2 * B + s) / 6);
    } else if (disc == 0) cuts.push_back(-B / 3);
    cuts.push_back(R);
    vector<double> xs;
    for (size_t i = 1; i + 1 < cuts.size(); i++) { // a critical point on the x axis: a double root
        double x = cuts[i], scale = 1 + fabs(x * x * x) + fabs(B * x * x) + fabs(C * x) + fabs(D);
        if (fabs(f(x)) <= 1e-9 * scale) xs.push_back(x);
    }
    for (size_t i = 0; i + 1 < cuts.size(); i++) { // a sign change on a monotone piece: one root
        double lo = cuts[i], hi = cuts[i + 1];
        if ((f(lo) < 0) == (f(hi) < 0)) continue;
        bool up = f(lo) < 0;
        for (int it = 0; it < 200; it++) {
            double mid = (lo + hi) / 2;
            if ((f(mid) < 0) == up) lo = mid;
            else hi = mid;
        }
        xs.push_back((lo + hi) / 2);
    }
    sort(xs.begin(), xs.end());
    vector<double> out;
    for (double x : xs) if (out.empty() || fabs(x - out.back()) > 1e-6 * (1 + fabs(x))) out.push_back(x);
    return out;
}
