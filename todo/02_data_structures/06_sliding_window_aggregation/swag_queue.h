#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): SWAG queue
// Section: 2. Data Structure / Sliding Window Aggregation
// Status: written and tested, not studied yet
//
// Sliding window aggregation: a queue that answers op(front, ..., back) in O(1) for
// any associative op, even one with no inverse (min, max, gcd, matrix product).
// Two stacks: pushes go on the back stack, which tracks the aggregate of everything
// in it; pops come off the front stack, where each entry stores the aggregate from
// itself to the end of that stack. When the front stack runs dry, move the whole
// back stack over, recomputing suffix aggregates: each element moves once, so all
// operations are amortized O(1). Order is preserved, so op need not commute.

template <class T, class Op>
struct SWAGQueue {
    vector<T> front_val, front_agg; // front_agg[i] = op(front_val[i], ..., front_val[0]) in queue order
    vector<T> back_val;
    T back_agg;
    bool has_back = false;
    Op op;
    SWAGQueue(Op op) : op(op) {}

    size_t size() { return front_val.size() + back_val.size(); }

    void push(T x) {
        back_val.push_back(x);
        back_agg = has_back ? op(back_agg, x) : x;
        has_back = true;
    }

    void pop() {
        if (front_val.empty()) { // move the back stack over; the queue front ends on top
            for (int i = back_val.size() - 1; i >= 0; i--) {
                front_val.push_back(back_val[i]);
                front_agg.push_back(front_agg.empty() ? back_val[i] : op(back_val[i], front_agg.back()));
            }
            back_val.clear();
            has_back = false;
        }
        front_val.pop_back(), front_agg.pop_back();
    }

    // op over the whole queue, front to back; needs size() > 0
    T query() {
        if (front_val.empty()) return back_agg;
        if (!has_back) return front_agg.back();
        return op(front_agg.back(), back_agg);
    }
};
