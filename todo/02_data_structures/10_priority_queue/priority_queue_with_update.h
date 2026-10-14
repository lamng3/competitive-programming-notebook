#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Priority queue with update
// Section: 2. Data Structure / Priority Queue
// Status: written and tested, not studied yet
//
// A binary min-heap over items 0..n-1 that also knows where each item sits, so it
// can change an item's priority or remove it in O(log n). std::priority_queue
// cannot do either; the usual workaround (push duplicates, skip stale ones) wastes
// memory. Typical use: Dijkstra or Prim with decrease-key.
//   set(i, p)   insert item i with priority p, or change its priority
//   erase(i)    remove item i if present
//   top() / pop()

template <class T>
struct IndexedHeap {
    vector<int> heap, pos; // pos[i] = index of item i in heap, -1 if absent
    vector<T> pri;
    IndexedHeap(int n) : pos(n, -1), pri(n) {}

    bool empty() { return heap.empty(); }
    bool contains(int i) { return pos[i] >= 0; }
    int top() { return heap[0]; }
    T priority(int i) { return pri[i]; }

    void swap_at(int a, int b) { swap(heap[a], heap[b]); pos[heap[a]] = a; pos[heap[b]] = b; }
    void up(int k) { while (k > 0 && pri[heap[k]] < pri[heap[(k - 1) / 2]]) swap_at(k, (k - 1) / 2), k = (k - 1) / 2; }
    void down(int k) {
        while (true) {
            int c = 2 * k + 1;
            if (c >= (int)heap.size()) break;
            if (c + 1 < (int)heap.size() && pri[heap[c + 1]] < pri[heap[c]]) c++;
            if (!(pri[heap[c]] < pri[heap[k]])) break;
            swap_at(k, c), k = c;
        }
    }

    void set(int i, T p) {
        if (pos[i] < 0) { pos[i] = heap.size(); heap.push_back(i); pri[i] = p; up(pos[i]); return; }
        pri[i] = p;
        up(pos[i]), down(pos[i]);
    }

    void erase(int i) {
        if (pos[i] < 0) return;
        int k = pos[i];
        swap_at(k, heap.size() - 1);
        heap.pop_back(), pos[i] = -1;
        if (k < (int)heap.size()) up(k), down(k);
    }

    int pop() { int i = heap[0]; erase(i); return i; }
};
