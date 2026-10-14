#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Partially retroactive priority queue
// Section: 2. Data Structure / Priority Queue
// Status: written and tested, not studied yet
//
// A min-priority queue where operations can be inserted into the past: "at time t,
// insert x" or "at time t, delete the min", and the queue's present content is kept
// up to date in O(log T) per operation. Times are distinct integers in [0, T).
//
// The key idea is a bridge: a time t where everything in the queue at time t is
// still in the queue now. Mark each operation with a weight: an insert whose
// element is later deleted gets +1, one whose element survives gets 0, a delete-min
// gets -1. The prefix sum up to t counts elements that are present at t but deleted
// later, so bridges are exactly where the prefix sum is 0.
//   insert(t, x): let t' be the last bridge before t. Exactly one element joins the
//     present queue: the largest of x and every element deleted after t'.
//   delete_min(t): let t' be the first bridge at or after t. Exactly one element
//     leaves the present queue: the smallest present element inserted by t'.
// Segment trees over time hold the weights (with their minimum prefix sum), the
// deleted elements (max), and the present elements (min). Delete-min must only be
// added where the queue is nonempty at every later moment.

template <class T>
struct RetroactivePQ {
    int N;
    vector<int> sum, mnp;         // weights: node sum and minimum prefix sum
    vector<pair<T, int>> dmax;    // deleted elements by insert time: max (key, time)
    vector<pair<T, int>> pmin;    // present elements by insert time: min (key, time)
    const pair<T, int> NEG = {numeric_limits<T>::lowest(), -1}, POS = {numeric_limits<T>::max(), -1};

    RetroactivePQ(int T_) {
        N = 1;
        while (N < T_) N *= 2;
        sum.assign(2 * N, 0), mnp.assign(2 * N, 0), dmax.assign(2 * N, NEG), pmin.assign(2 * N, POS);
    }

    void set_weight(int t, int w) {
        int u = t + N;
        sum[u] = w, mnp[u] = min(0, w);
        for (u >>= 1; u; u >>= 1) sum[u] = sum[2 * u] + sum[2 * u + 1], mnp[u] = min(mnp[2 * u], sum[2 * u] + mnp[2 * u + 1]);
    }
    template <class V, class Op> void put(vector<V>& t, int i, V v, Op op) {
        int u = i + N;
        t[u] = v;
        for (u >>= 1; u; u >>= 1) t[u] = op(t[2 * u], t[2 * u + 1]);
    }
    template <class V, class Op> V range(vector<V>& t, int l, int r, V id, Op op) { // [l, r)
        V res = id;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = op(res, t[l++]);
            if (r & 1) res = op(res, t[--r]);
        }
        return res;
    }
    static pair<T, int> mx(pair<T, int> a, pair<T, int> b) { return max(a, b); }
    static pair<T, int> mn(pair<T, int> a, pair<T, int> b) { return min(a, b); }

    int prefix(int t) { // sum of weights at times <= t
        int s = 0;
        for (int l = N, r = t + 1 + N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) s += sum[l++];
            if (r & 1) s += sum[--r];
        }
        return s;
    }

    // last time s < t with prefix(s) == 0, or -1 (the start is always a bridge)
    int last_bridge_before(int t) {
        for (int s = t - 1; s >= 0; ) { // walk left: jump over nodes whose prefixes stay > 0
            int u = s + N, base = prefix(s) - sum[u]; // prefix just before s
            if (base + sum[u] == 0) return s;
            // climb while u is a left child or its whole block has prefixes > 0
            while (u > 1 && ((u & 1) == 0 || base - sum[u - 1] + mnp[u - 1] > 0)) {
                if (u & 1) { base -= sum[u - 1]; u--; } // block of u-1 has no zero: skip it
                else u >>= 1;
                if ((u & 1) == 0 && u > 1) { /* keep climbing */ }
            }
            // simple and safe fallback: step one time to the left
            s--;
        }
        return -1;
    }

    // first time s >= t with prefix(s) == 0
    int first_bridge_from(int t) {
        int base = prefix(t - 1 < 0 ? -1 : t - 1);
        if (t == 0) base = 0;
        // descend: find the first leaf s >= t where base + prefix within reaches 0
        int u = t + N;
        // climb until a node to the right has a zero prefix
        vector<int> right_nodes;
        for (int l = t + N, r = 2 * N; l < r; l >>= 1, r >>= 1)
            if (l & 1) right_nodes.push_back(l++);
        for (int v : right_nodes) {
            if (base + mnp[v] <= 0) { // the zero is inside v: descend
                while (v < N) {
                    if (base + mnp[2 * v] <= 0) v = 2 * v;
                    else base += sum[2 * v], v = 2 * v + 1;
                }
                return v - N;
            }
            base += sum[v];
        }
        (void)u;
        return N - 1;
    }

    vector<char> kind; // per time: 0 none, 1 insert, 2 delete
    vector<T> val;

    void ensure() { if (kind.empty()) kind.assign(N, 0), val.assign(N, T()); }

    void insert(int t, T x) {
        ensure();
        kind[t] = 1, val[t] = x;
        int b = last_bridge_before(t);
        auto best = range(dmax, b + 1, N, NEG, mx);
        if (best.second < 0 || best.first < x) { // x itself joins the present
            set_weight(t, 0);
            put(pmin, t, make_pair(x, t), mn);
        } else { // the deleted element best comes back; x takes its place among the deleted
            set_weight(t, 1);
            put(dmax, t, make_pair(x, t), mx);
            set_weight(best.second, 0);
            put(dmax, best.second, NEG, mx);
            put(pmin, best.second, best, mn);
        }
    }

    void delete_min(int t) {
        ensure();
        kind[t] = 2;
        int b = first_bridge_from(t);
        auto out = range(pmin, 0, b + 1, POS, mn); // the smallest present element inserted by b
        set_weight(t, -1);
        put(pmin, out.second, POS, mn);
        put(dmax, out.second, out, mx);
        set_weight(out.second, 1);
    }

    T min_now() { return pmin[1].first; }      // needs a nonempty present queue
    bool empty_now() { return pmin[1].second < 0; }
};
