#pragma once
#include <bits/stdc++.h>
using namespace std;

class LazySegmentTree {
    int N;
    vector<int> A;
    vector<int> lazy;
    vector<int> st;

    LazySegmentTree(int n, const vector<int>& a) {
        N = n;
        A = a;
        st.resize(4 * N);
        lazy.resize(4 * N);
    } 

    void build(int v, int tl, int tr) {
        if (tl == tr) {
            st[v] = A[tl];
            return;
        }
        int tm = tl + (tr - tl) / 2;
        build(v*2+1, tl, tm);
        build(v*2+2, tm+1, tr);
        st[v] = st[v*2+1] + st[v*2+2];
    }

    void push(int v) {
        st[v*2+1] += lazy[v];
        st[v*2+2] += lazy[v];
        lazy[v*2+1] += lazy[v];
        lazy[v*2+2] += lazy[v];
        lazy[v] = 0;
    }

    void update(int v, int tl, int tr, int ql, int qr, int add) {
        if (ql > qr) return;
        if (ql == tl && tr == qr) {
            st[v] += add;
            lazy[v] += add;
            return;
        }
        push(v);
        int tm = tl + (tr - tl) / 2;
        update(v*2+1, tl, tm, ql, min(tm, qr), add);
        update(v*2+2, tm+1, tr, max(tm+1, ql), qr, add);
        st[v] = st[v*2+1] + st[v*2+2];
    }

    int query(int v, int tl, int tr, int ql, int qr) {
        if (ql > qr) return 0;
        if (ql == tl && tr == qr) return st[v];
        push(v);
        int tm = tl + (tr - tl) / 2;
        int left = query(v*2+1, tl, tm, ql, min(tm, qr));
        int right = query(v*2+2, tm+1, tr, max(tm+1, ql), qr);
        return left + right;
    }
};