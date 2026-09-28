#pragma once
#include <bits/stdc++.h>
using namespace std;

struct SparseST {
    struct Node {
        int lazy = -1;
        int tracked = 0;
        Node* left = nullptr;
        Node* right = nullptr;
    };

    int N;
    Node* root;

    SparseST(int n) {
        N = n;
        root = new Node();
    }

    void apply(Node* node, int tl, int tr, int val) {
        node->tracked = val * (tr - tl + 1);
        node->lazy = val;
    }

    void push(Node* node, int tl, int tr) {
        if (node->lazy == -1) return;
        if (!node->left) node->left = new Node();
        if (!node->right) node->right = new Node();
        int tm = tl + (tr - tl) / 2;
        apply(node->left, tl, tm, node->lazy);
        apply(node->right, tm + 1, tr, node->lazy);
        node->lazy = -1;
    }

    void update(Node* node, int tl, int tr, int ql, int qr, int val) {
        if (ql > qr) return;
        if (ql == tl && tr == qr) {
            apply(node, tl, tr, val);
            return;
        }
        push(node, tl, tr);
        int tm = tl + (tr - tl) / 2;
        update(node->left, tl, tm, ql, min(tm, qr), val);
        update(node->right, tm + 1, tr, max(tm + 1, ql), qr, val);
        node->tracked = node->left->tracked + node->right->tracked;
    }

    int query(Node* node, int tl, int tr, int ql, int qr) {
        if (ql > qr) return 0;
        if (ql == tl && tr == qr) return node->tracked;
        push(node, tl, tr);
        int tm = tl + (tr - tl) / 2;
        int left = query(node->left, tl, tm, ql, min(tm, qr));
        int right = query(node->right, tm + 1, tr, max(tm + 1, ql), qr);
        return left + right;
    }

    void update(int ql, int qr, int val) {
        update(root, 0, N - 1, ql, qr, val);
    }

    int query(int ql, int qr) {
        return query(root, 0, N - 1, ql, qr);
    }
};