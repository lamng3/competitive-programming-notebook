#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): SWAG deque
// Section: 2. Data Structure / Sliding Window Aggregation
// Status: written and tested, not studied yet
//
// Sliding window aggregation on a deque: push and pop at both ends, and
// op(front, ..., back) in amortized O(1), for any associative op.
// Two stacks again, one per end, each storing running aggregates toward its bottom.
// When one end runs dry, split the other stack in half and rebuild both stacks:
// the halving keeps the amortized cost O(1) even when pops alternate ends.

template <class T, class Op>
struct SWAGDeque {
    // l holds the front part, top = queue front; r holds the back part, top = queue back.
    // la[i] = op(l[i], ..., l[0]) in queue order; ra[i] = op(r[0], ..., r[i]).
    vector<T> l, la, r, ra;
    Op op;
    SWAGDeque(Op op) : op(op) {}

    size_t size() { return l.size() + r.size(); }

    void push_front(T x) { l.push_back(x); la.push_back(la.empty() ? x : op(x, la.back())); }
    void push_back(T x) { r.push_back(x); ra.push_back(ra.empty() ? x : op(ra.back(), x)); }

    // rebuild from the queue order q, putting the first `cut` elements in front
    void rebuild(const vector<T>& q, size_t cut) {
        l.clear(), la.clear(), r.clear(), ra.clear();
        for (size_t i = cut; i-- > 0; ) push_front(q[i]);
        for (size_t i = cut; i < q.size(); i++) push_back(q[i]);
    }
    vector<T> order() { // the queue, front to back
        vector<T> q(l.rbegin(), l.rend());
        q.insert(q.end(), r.begin(), r.end());
        return q;
    }

    void pop_front() {
        if (l.empty()) { auto q = order(); rebuild(q, (q.size() + 1) / 2); }
        l.pop_back(), la.pop_back();
    }
    void pop_back() {
        if (r.empty()) { auto q = order(); rebuild(q, q.size() / 2); }
        r.pop_back(), ra.pop_back();
    }

    T front() { return l.empty() ? r.front() : l.back(); }
    T back() { return r.empty() ? l.front() : r.back(); }

    // op over the whole deque, front to back; needs size() > 0
    T query() {
        if (l.empty()) return ra.back();
        if (r.empty()) return la.back();
        return op(la.back(), ra.back());
    }
};
