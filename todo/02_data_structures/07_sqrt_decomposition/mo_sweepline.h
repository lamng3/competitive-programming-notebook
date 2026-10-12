#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Mo sweepline
// Section: 2. Data Structure / Sqrt Decomposition
// Status: written and tested, not studied yet
//
// Mo's algorithm "offline twice" (Mo + sweepline): count pairs i < j inside [L, R]
// with rel(a_i, a_j), when inserting into the counting structure is the expensive
// part. Moving R to R+1 adds  #{j in [L, R] : rel(a_j, a_{R+1})}
//   = before(R+1 vs prefix R+1) - before(R+1 vs prefix L),
// where before(i vs prefix p) = #{j < p : rel(a_j, a_i)}. The first term is computed
// once for every i in one sweep. The second term has a fixed prefix L for a whole run
// of moves, so it becomes a task "at prefix L, sum before(i) over this range of i".
// A second sweep inserts a_0, a_1, ... once and answers all tasks at their prefix.
// Moves of L are the mirror image with after(i vs prefix p) = #{j < p : rel(a_i, a_j)}.
// Total: O(n) inserts and O(n sqrt q) cheap counts, instead of O(n sqrt q) inserts.
//
// S is a structure over values with:
//   S.insert(v)        S.before(v) = #inserted u with rel(u, v)
//   S.clear()          S.after(v)  = #inserted u with rel(v, u)
// Returns the answer of each query [L, R] (inclusive).

template <class S, class T>
vector<long long> mo_sweepline(const vector<T>& a, const vector<pair<int, int>>& qs, S& s) {
    int n = a.size(), q = qs.size();
    vector<long long> ans(q, 0);
    if (q == 0) return ans;
    // pre[i] = before(i vs prefix i), suf[i] = after(i vs prefix i + 1) (j = i included)
    vector<long long> pre(n + 1, 0), suf(n + 1, 0); // stored as prefix sums
    s.clear();
    for (int i = 0; i < n; i++) {
        long long b = s.before(a[i]);
        s.insert(a[i]);
        long long af = s.after(a[i]);
        pre[i + 1] = pre[i] + b;
        suf[i + 1] = suf[i] + af;
    }
    int B = max(1, (int)(n / sqrt(q)));
    vector<int> order(q);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int x, int y) {
        int bx = qs[x].first / B, by = qs[y].first / B;
        if (bx != by) return bx < by;
        return bx & 1 ? qs[x].second > qs[y].second : qs[x].second < qs[y].second;
    });
    struct Task { int lo, hi, sign, id; bool use_after; }; // sum over i in [lo, hi]
    vector<vector<Task>> at(n + 1); // tasks at prefix p (elements 0..p-1 inserted)
    vector<long long> delta(q, 0);
    int L = 0, R = -1;
    for (int id : order) {
        auto [l, r] = qs[id];
        // pairs gained/lost, each move expressed through prefix differences
        if (R < r) { // R grows: + sum before(i vs i) - sum before(i vs L)
            delta[id] += pre[r + 1] - pre[R + 1];
            at[L].push_back({R + 1, r, -1, id, false});
            R = r;
        }
        if (R > r) {
            delta[id] -= pre[R + 1] - pre[r + 1];
            at[L].push_back({r + 1, R, +1, id, false});
            R = r;
        }
        if (L > l) { // L shrinks: + sum after(i vs R+1) - sum after(i vs i+1)
            delta[id] -= suf[L] - suf[l];
            at[R + 1].push_back({l, L - 1, +1, id, true});
            L = l;
        }
        if (L < l) {
            delta[id] += suf[l] - suf[L];
            at[R + 1].push_back({L, l - 1, -1, id, true});
            L = l;
        }
    }
    s.clear();
    for (int p = 0; p <= n; p++) {
        for (auto& t : at[p]) {
            long long sum = 0;
            for (int i = t.lo; i <= t.hi; i++) sum += t.use_after ? s.after(a[i]) : s.before(a[i]);
            delta[t.id] += t.sign * sum;
        }
        if (p < n) s.insert(a[p]);
    }
    long long cur = 0;
    for (int id : order) cur += delta[id], ans[id] = cur;
    return ans;
}
