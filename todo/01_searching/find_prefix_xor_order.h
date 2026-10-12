#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Find prefix XOR order
// Section: 1. Numeric
// Status: written and tested, not studied yet
//
// Rank questions about XORs, answered with a binary trie over the values.
// Insert numbers v; then for a query x, the k-th smallest value of (v ^ x) over
// the stored v, or how many stored v have v ^ x < bound. Walk the bits from the
// top: at each level, the child that keeps the bit of (v ^ x) at 0 holds all the
// smaller results. The classic use: prefix XORs P[i], and "subarrays with XOR < k"
// is, for each r, counting P[l] with P[l] ^ P[r] < k.

struct XorTrie {
    static const int B = 30;
    vector<array<int, 2>> ch = {{0, 0}};
    vector<int> cnt = {0};

    void insert(int v) {
        int u = 0;
        cnt[0]++;
        for (int b = B - 1; b >= 0; b--) {
            int c = v >> b & 1;
            if (!ch[u][c]) {
                ch[u][c] = ch.size();
                ch.push_back({0, 0});
                cnt.push_back(0);
            }
            u = ch[u][c];
            cnt[u]++;
        }
    }

    // k-th smallest (0-indexed) of v ^ x over stored v; needs k < size
    int kth(int x, int k) {
        int u = 0, res = 0;
        for (int b = B - 1; b >= 0; b--) {
            int same = x >> b & 1; // this child gives bit 0 in v ^ x
            int c = ch[u][same];
            if (c && cnt[c] > k) u = c;
            else {
                if (c) k -= cnt[c];
                u = ch[u][same ^ 1];
                res |= 1 << b;
            }
        }
        return res;
    }

    // how many stored v have (v ^ x) < bound
    int count_less(int x, int bound) {
        int u = 0, res = 0;
        for (int b = B - 1; b >= 0 && u >= 0; b--) {
            int xb = x >> b & 1, bb = bound >> b & 1;
            if (bb) { // bit 0 here is already smaller: take that whole subtree
                if (ch[u][xb]) res += cnt[ch[u][xb]];
                u = ch[u][xb ^ 1] ? ch[u][xb ^ 1] : -1;
            } else u = ch[u][xb] ? ch[u][xb] : -1;
        }
        return res;
    }
};
