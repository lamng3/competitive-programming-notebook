#pragma once
#include <bits/stdc++.h>
#include <parlay/parallel.h>
using namespace std;

// Blelloch's scan: inclusive prefix sums with two sweeps over a balanced binary
// tree whose leaves are the elements. Going up, each node learns the sum of
// its leaves; coming down, each node learns the sum of everything to the
// left of its leaves. Recursion with parlay::par_do works, and so do loops
// over the levels of a tree laid out in the array.
// Aim: O(n) work and O(log n) depth, for every n, including 0.
// Check: cppar prefix_sums --check. Time: cppar prefix_sums.

template <class T>
void scan_blelloch(const T* in, T* out, size_t n) {
    // TODO: write it, then delete this line and the next.
    throw logic_error("not written yet");
}
