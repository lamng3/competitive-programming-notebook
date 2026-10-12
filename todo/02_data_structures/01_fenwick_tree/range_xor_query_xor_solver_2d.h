#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Range xor query xor solver 2D
// Section: 2. Data Structure / Fenwick Tree
// Status: written and tested, not studied yet
//
// Rectangle XOR-update and rectangle XOR-query. In the sum version a point update
// counts (x - i + 1)(y - j + 1) times; under XOR only the parity of that count
// matters, and x - i + 1 is odd exactly when i and x have the same parity. So keep
// four 2D Fenwick trees, one per (i mod 2, j mod 2), and a prefix query reads only
// the tree matching (x mod 2, y mod 2).

struct RectXorRectXor {
    int n, m;
    vector<vector<long long>> t[2][2];
    RectXorRectXor(int n, int m) : n(n), m(m) {
        for (auto& a : t) for (auto& v : a) v.assign(n + 2, vector<long long>(m + 2, 0));
    }

    void point(int x, int y, long long d) {
        auto& b = t[x & 1][y & 1];
        for (int i = x; i <= n + 1; i += i & -i)
            for (int j = y; j <= m + 1; j += j & -j) b[i][j] ^= d;
    }

    // a[x1..x2][y1..y2] ^= d
    void update(int x1, int y1, int x2, int y2, long long d) {
        point(x1, y1, d), point(x1, y2 + 1, d), point(x2 + 1, y1, d), point(x2 + 1, y2 + 1, d);
    }

    // XOR of a[1..x][1..y]: update at (i, j) counts when (x - i + 1)(y - j + 1) is odd,
    // that is i = x (mod 2) and j = y (mod 2)
    long long prefix(int x, int y) {
        long long s = 0;
        auto& b = t[x & 1][y & 1];
        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j) s ^= b[i][j];
        return s;
    }

    long long query(int x1, int y1, int x2, int y2) {
        return prefix(x2, y2) ^ prefix(x1 - 1, y2) ^ prefix(x2, y1 - 1) ^ prefix(x1 - 1, y1 - 1);
    }
};
