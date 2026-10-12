#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Mo 2D
// Section: 2. Data Structure / Sqrt Decomposition
// Status: written and tested, not studied yet
//
// Mo's algorithm: answer offline range queries [L, R] by moving one window.
// See each query as a point (L, R) in the plane; the cost is the length of the
// path that visits them all. Sort by block of L (block = n / sqrt q), then by R,
// alternating the R direction per block (zig-zag): O(n sqrt q) total moves.
//
// The caller keeps the window state:
//   add(i)     a[i] enters        remove(i)   a[i] leaves
//   answer(id) record the answer of query id for the current window

template <class Add, class Remove, class Answer>
void mo_2d(int n, const vector<pair<int, int>>& qs, Add add, Remove remove, Answer answer) {
    int q = qs.size();
    if (q == 0) return;
    int B = max(1, (int)(n / sqrt(q)));
    vector<int> order(q);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) {
        int ba = qs[a].first / B, bb = qs[b].first / B;
        if (ba != bb) return ba < bb;
        return ba & 1 ? qs[a].second > qs[b].second : qs[a].second < qs[b].second;
    });
    int L = 0, R = -1; // empty window
    for (int id : order) {
        auto [l, r] = qs[id];
        while (L > l) add(--L); // expand first: the window never turns inside out
        while (R < r) add(++R);
        while (L < l) remove(L++);
        while (R > r) remove(R--);
        answer(id);
    }
}
