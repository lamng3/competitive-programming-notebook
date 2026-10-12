#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Mo 3D
// Section: 2. Data Structure / Sqrt Decomposition
// Status: written and tested, not studied yet
//
// Mo's algorithm with point updates: a query (L, R, t) asks about the array after
// the first t updates. Now each query is a point in 3D and the window also moves in
// time. Sort by block of L, block of R, then t, with blocks of n^(2/3):
// O(n^(5/3)) total moves.
//
//   add(i), remove(i)       a[i] enters / leaves the window
//   apply(k, L, R)          apply update k; if its position is in [L, R], the window
//                           must swap the old value out and the new one in
//   undo(k, L, R)           the reverse
// A convenient way to write both: store each update as (pos, value) and swap the
// array value with the stored one, so apply and undo are the same function.

template <class Add, class Remove, class Apply, class Undo, class Answer>
void mo_3d(int n, const vector<array<int, 3>>& qs, Add add, Remove remove, Apply apply, Undo undo, Answer answer) {
    int q = qs.size();
    if (q == 0) return;
    int B = max(1, (int)cbrt((double)n * n));
    vector<int> order(q);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) {
        auto& x = qs[a]; auto& y = qs[b];
        if (x[0] / B != y[0] / B) return x[0] / B < y[0] / B;
        if (x[1] / B != y[1] / B) return x[1] / B < y[1] / B;
        return x[2] < y[2];
    });
    int L = 0, R = -1, T = 0; // T = updates applied
    for (int id : order) {
        auto [l, r, t] = qs[id];
        while (L > l) add(--L);
        while (R < r) add(++R);
        while (L < l) remove(L++);
        while (R > r) remove(R--);
        while (T < t) apply(T++, L, R);
        while (T > t) undo(--T, L, R);
        answer(id);
    }
}
