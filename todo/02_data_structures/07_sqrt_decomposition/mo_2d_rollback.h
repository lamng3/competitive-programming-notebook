#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Mo 2D rollback
// Section: 2. Data Structure / Sqrt Decomposition
// Status: written and tested, not studied yet
//
// Mo's algorithm when elements can be added but not removed (max of a window,
// distinct count with a "last seen" trick, DSU unions): add and roll back instead.
// Group queries by the block of L. For one block, sort by R and grow the right part
// from the block's end; for each query, add the few elements from L to the block's
// end, answer, and roll those back. Queries inside a single block are done directly.
// O(n sqrt q) adds in total.
//
// The caller's structure provides:
//   add(i)       a[i] enters
//   snapshot()   remember the current state (one level is enough)
//   rollback()   return to the last snapshot
//   reset()      empty window
//   answer(id)

template <class Add, class Snap, class Roll, class Reset, class Answer>
void mo_rollback(int n, const vector<pair<int, int>>& qs, Add add, Snap snapshot, Roll rollback, Reset reset, Answer answer) {
    int q = qs.size();
    if (q == 0) return;
    int B = max(1, (int)(n / sqrt(q)));
    vector<int> order(q);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) {
        int ba = qs[a].first / B, bb = qs[b].first / B;
        return ba != bb ? ba < bb : qs[a].second < qs[b].second;
    });
    int i = 0;
    while (i < q) {
        int block = qs[order[i]].first / B, end = min(n, (block + 1) * B); // right part starts at end
        reset();
        int R = end - 1;
        for (; i < q && qs[order[i]].first / B == block; i++) {
            auto [l, r] = qs[order[i]];
            if (r < end) { // the whole query is inside the block: brute force
                snapshot();
                for (int k = l; k <= r; k++) add(k);
                answer(order[i]);
                rollback();
                continue;
            }
            while (R < r) add(++R);
            snapshot();
            for (int k = end - 1; k >= l; k--) add(k);
            answer(order[i]);
            rollback();
        }
    }
}
