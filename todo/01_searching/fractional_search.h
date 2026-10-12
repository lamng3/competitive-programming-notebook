#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Fractional search
// Section: 1. Numeric
// Status: written and tested, not studied yet
//
// Binary search over fractions: the smallest p/q with q <= N such that pred(p, q)
// holds, for a pred monotone in the value p/q (False below a threshold, True above).
// Walk the Stern-Brocot tree from (0/1, 1/0): every fraction with small denominator
// is a mediant on the way. A plain walk can take O(N) steps in one direction, so
// each run of same-direction steps is one exponential + binary search:
// O(log^2 N) calls of pred. The two boundaries are always Stern-Brocot neighbors,
// so when neither can move, no fraction with terms <= N lies between them.

using ll = long long;

// pred(p, q) is monotone in the value p/q; pred(N, 1) must hold.
// Returns the smallest p/q with p, q <= N where pred holds, in lowest terms.
template <class Pred>
pair<ll, ll> smallest_fraction(ll N, Pred pred) {
    ll lp = 0, lq = 1, hp = 1, hq = 0; // lo = 0/1 is invalid, hi = 1/0 stands for +infinity
    if (pred(0, 1)) return {0, 1};
    // largest k with ok(k), for ok true at 0 and monotone: double, then halve
    auto largest = [](auto ok) {
        ll k = 0, step = 1;
        while (ok(k + step)) k += step, step *= 2;
        while (step > 1) {
            step /= 2;
            if (ok(k + step)) k += step;
        }
        return k;
    };
    while (true) {
        // hi steps toward lo while it stays valid: (hp + k lp) / (hq + k lq)
        ll a = largest([&](ll k) {
            ll p = hp + k * lp, q = hq + k * lq;
            return p <= N && q <= N && pred(p, q);
        });
        hp += a * lp, hq += a * lq;
        // lo steps toward hi while it stays invalid: (lp + k hp) / (lq + k hq)
        ll b = largest([&](ll k) {
            ll p = lp + k * hp, q = lq + k * hq;
            return p <= N && q <= N && !pred(p, q);
        });
        lp += b * hp, lq += b * hq;
        if (a == 0 && b == 0) break; // neither boundary moves: they are neighbors
    }
    return {hp, hq};
}
