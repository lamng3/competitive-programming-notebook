#pragma once
#include <bits/stdc++.h>
using namespace std;

// LCA with Farach-Colton and Bender: O(n) build, O(1) per query
// notes: README.md next to this file
//
//   FCB fcb(adj, root);    adj is 0-indexed and undirected
//   fcb.lca(u, v);  fcb.dist(u, v);  fcb.depth(u);
//   fcb.argmin(l, r);      the +-1 RMQ on its own, over euler tour positions
//
// eulerTour is recursive: a path of 5e5 vertices needs `ulimit -s 65520` locally

class FCB {
public:
    FCB(const vector<vector<int>>& _adj, int root = 0) : adj(_adj) {
        int n = adj.size();
        buildEulerTour(n, root);
        // heights along the tour
        arr.resize(euler.size());
        for (int i = 0; i < (int)euler.size(); i++) arr[i] = nodeHeight[euler[i]];
        buildLog(arr.size());
        buildRMQ();
    }

    // shallowest vertex between the first visits of u and v
    int lca(int u, int v) {
        return euler[argmin(nodeStart[u], nodeStart[v])];
    }

    int depth(int u) {
        return nodeHeight[u];
    }

    int dist(int u, int v) {
        return nodeHeight[u] + nodeHeight[v] - 2 * nodeHeight[lca(u, v)];
    }

    // position of the min of arr[l..r], l and r in either order
    int argmin(int l, int r) {
        if (l > r) swap(l, r);
        int bl = l / block_size, br = r / block_size;
        // both ends in one block
        if (bl == br) return queryInBlock(bl, l % block_size, r % block_size);
        // suffix of l's block, prefix of r's block
        int ans = minIdx(queryInBlock(bl, l % block_size, block_size-1),
                         queryInBlock(br, 0, r % block_size));
        // whole blocks in between
        if (bl+1 <= br-1) ans = minIdx(ans, querySparseTable(bl+1, br-1));
        return ans;
    }

private:
    vector<vector<int>> adj;

    // ---------- euler tour ----------

    vector<int> euler;      // vertices in visit order, u written on entry and after each child
    vector<int> nodeStart;  // first index of u in euler, the only position a query needs
    vector<int> nodeHeight; // depth of u, root = 0

    void eulerTour(int u, int p, int h) {
        nodeStart[u] = euler.size();
        euler.push_back(u);
        nodeHeight[u] = h;
        for (int v : adj[u]) {
            if (v == p) continue;
            eulerTour(v, u, h+1);
            euler.push_back(u); // back up through u
        }
    }

    void buildEulerTour(int n, int root) {
        nodeStart.assign(n, -1);
        nodeHeight.assign(n, 0);
        euler.clear();
        euler.reserve(2*n);
        eulerTour(root, -1, 0);
    }

    // ---------- log table ----------

    vector<int> lg2; // lg2[x] = floor(log2(x)), lg2[0] = -1

    void buildLog(int m) {
        lg2.assign(m+1, -1);
        for (int i = 1; i <= m; i++) lg2[i] = lg2[i/2] + 1;
    }

    // ---------- +-1 RMQ ----------
    // argmin(l, r) = position of the min of arr[l..r], neighbours of arr differ by exactly 1

    vector<int> arr;
    int block_size, block_cnt;

    int minIdx(int i, int j) {
        return arr[i] < arr[j] ? i : j;
    }

    vector<vector<int>> st; // st[b][k] = position of the min of blocks [b, b + 2^k)

    void buildBlockSparseTable() {
        int m = arr.size();
        st.assign(block_cnt, vector<int>(lg2[block_cnt] + 1));
        // min of each block
        for (int i = 0; i < m; i++) {
            int b = i / block_size;
            if (i % block_size == 0) st[b][0] = i;
            else st[b][0] = minIdx(st[b][0], i);
        }
        // double the span
        for (int k = 1; k <= lg2[block_cnt]; k++) {
            for (int b = 0; b < block_cnt; b++) {
                int nb = b + (1 << (k-1));
                if (nb < block_cnt) st[b][k] = minIdx(st[b][k-1], st[nb][k-1]);
                else st[b][k] = st[b][k-1];
            }
        }
    }

    // min of blocks [bl, br], two overlapping runs of 2^k blocks
    int querySparseTable(int bl, int br) {
        int k = lg2[br - bl + 1];
        return minIdx(st[bl][k], st[br - (1 << k) + 1][k]);
    }

    vector<int> blockMask; // bit j-1 = 1 if the block steps up from offset j-1 to j

    void buildBlockMasks() {
        int m = arr.size();
        blockMask.assign(block_cnt, 0);
        for (int i = 1; i < m; i++) {
            int j = i % block_size;
            if (j > 0 && arr[i] > arr[i-1]) blockMask[i / block_size] |= 1 << (j-1);
        }
    }

    // maskTable[mask][l][r] = offset of the min of [l, r] in a block of that shape
    vector<vector<vector<int>>> maskTable;

    void buildMaskTables() {
        int masks = 1 << (block_size - 1);
        maskTable.assign(masks, vector<vector<int>>(block_size, vector<int>(block_size)));
        for (int mask = 0; mask < masks; mask++) {
            for (int l = 0; l < block_size; l++) {
                // walk right from l, keep where the running height is lowest
                int h = 0, best = 0, pos = l;
                maskTable[mask][l][l] = l;
                for (int r = l+1; r < block_size; r++) {
                    h += (mask >> (r-1) & 1) ? 1 : -1;
                    if (h < best) best = h, pos = r;
                    maskTable[mask][l][r] = pos;
                }
            }
        }
    }

    // min over offsets [l, r] of block b
    int queryInBlock(int b, int l, int r) {
        return b * block_size + maskTable[blockMask[b]][l][r];
    }

    void buildRMQ() {
        int m = arr.size();
        block_size = max(1, lg2[m] / 2);
        block_cnt = (m + block_size - 1) / block_size;
        buildBlockSparseTable();
        buildBlockMasks();
        buildMaskTables();
    }
};
