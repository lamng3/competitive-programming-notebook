#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Mo 2D hilbert curve ordering
// Section: 2. Data Structure / Sqrt Decomposition
// Status: written and tested, not studied yet
//
// Mo's algorithm with the queries visited along a Hilbert curve. The curve fills the
// (L, R) plane while only ever stepping to a neighbor, so nearby queries get nearby
// positions: total movement O(n sqrt q), usually noticeably less than block order.
// hilbert(x, y) is the index of (x, y) on the curve over a 2^k x 2^k grid.

inline long long hilbert(int x, int y, int k = 21) { // grid 2^k x 2^k, x, y < 2^k
    long long d = 0;
    for (int s = 1 << (k - 1); s > 0; s >>= 1) {
        int rx = (x & s) > 0, ry = (y & s) > 0;
        d += (long long)s * s * ((3 * rx) ^ ry);
        if (ry == 0) { // rotate the quadrant so the curve stays continuous
            if (rx == 1) x = s - 1 - x, y = s - 1 - y;
            swap(x, y);
        }
    }
    return d;
}

template <class Add, class Remove, class Answer>
void mo_hilbert(const vector<pair<int, int>>& qs, Add add, Remove remove, Answer answer) {
    int q = qs.size();
    vector<long long> key(q);
    for (int i = 0; i < q; i++) key[i] = hilbert(qs[i].first, qs[i].second);
    vector<int> order(q);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) { return key[a] < key[b]; });
    int L = 0, R = -1;
    for (int id : order) {
        auto [l, r] = qs[id];
        while (L > l) add(--L);
        while (R < r) add(++R);
        while (L < l) remove(L++);
        while (R > r) remove(R--);
        answer(id);
    }
}
