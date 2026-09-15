#pragma once
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vii = vector<vector<int>>;
using pii = pair<int, int>;

#define REP(i, n) for (int i = 0; i < (n); i++)
#define FOR(i, a, b) for (int i = (a); i <= (b); i++)
#define FORD(i, a, b) for (int i = (a); i >= (b); i--)
#define RFOR(i, n) for (int i = (n) - 1; i >= 0; i--)

#define fi first
#define se second
#define pb push_back

const int INF = 1e9+7;
const int MOD = 1e9+7;

const int MAX_N = 2e5+5;

struct PersistentSparseST {
    struct Node {
        ll sum = 0;
        int left = 0, right = 0;
    };

    int N;
    vector<Node> tree;

    PersistentSparseST(int n) : N(n) {
        tree.reserve(MAX_N);
        tree.pb(Node());
    }

    int join(int l, int r) {
        tree.pb(Node{tree[l].sum + tree[r].sum, l, r});
        return tree.size()-1;
    }

    int update(int v, int tl, int tr, int pos, int val) {
        if (tl == tr) {
            tree.pb(Node{(ll)val, 0, 0});
            return tree.size()-1;
        }
        int tm = tl + (tr - tl) / 2;
        int lc = (v == 0) ? 0 : tree[v].left;
        int rc = (v == 0) ? 0 : tree[v].right;
        if (pos <= tm) return join(update(lc, tl, tm, pos, val), rc);
        else return join(lc, update(rc, tm+1, tr, pos, val));
    }

    ll query(int v, int tl, int tr, int ql, int qr) {
        if (v == 0 || ql > qr) return 0;
        if (ql == tl && tr == qr) return tree[v].sum;
        int tm = tl + (tr - tl) / 2;
        ll left = query(tree[v].left, tl, tm, ql, min(tm, qr));
        ll right = query(tree[v].right, tm+1, tr, max(tm+1, ql), qr);
        return left + right;
    }

    int update(int root, int pos, int val) {
        return update(root, 0, N-1, pos, val);
    }

    ll query(int root, int ql, int qr) {
        return query(root, 0, N-1, ql, qr);
    }
};