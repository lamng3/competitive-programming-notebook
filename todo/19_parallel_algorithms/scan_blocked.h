#pragma once
#include <bits/stdc++.h>
#include <parlay/parallel.h>
using namespace std;

// TODO (study): Scan, blocked
// Section: 19. Parallel Algorithms
// Status: not written yet
//
// Inclusive prefix sums for real machines: split the array into blocks of
// a few thousand elements, and let each block run a plain sequential loop.
// Two parallel passes over the blocks, with a small step in between.
// Aim: O(n) work and as few passes over memory as you can manage, for
// every n, including 0.
// Check with `cpunit todo_parallel`, time with `python3 bench.py`.

template <class T>
void scan_blocked(const T* in, T* out, size_t n) {
    // TODO: write it. Until then, out is left as it is.
    (void)in, (void)out, (void)n;
}
