#pragma once
#include <bits/stdc++.h>
#include <parlay/parallel.h>
using namespace std;

// TODO (study): Scan, Blelloch
// Section: 19. Parallel Algorithms
// Status: not written yet
//
// Inclusive prefix sums with two sweeps over a balanced binary tree whose
// leaves are the elements. Going up, each node learns the sum of its
// leaves; coming down, each node learns the sum of everything to the left
// of its leaves. Recursion with parlay::par_do works, and so do loops over
// the levels of a tree laid out in the array.
// Aim: O(n) work and O(log n) depth, for every n, including 0.
// Check with `cpunit todo_parallel`, time with `python3 bench.py`.

template <class T>
void scan_blelloch(const T* in, T* out, size_t n) {
    // TODO: write it. Until then, out is left as it is.
    (void)in, (void)out, (void)n;
}
