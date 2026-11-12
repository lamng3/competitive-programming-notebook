#pragma once
#include <bits/stdc++.h>
using namespace std;

// https://cp-algorithms.com/graph/lca_farachcoltonbender.html
//
// Farach-Colton and Bender: LCA in O(n) build, O(1) per query.
// Same modules as notebook/examples/trees/farach-colton_bender/fcb.cpp.
//
//   FCB fcb(adj, root);    // adj: 0-indexed, undirected
//   fcb.lca(u, v);
//   fcb.argmin(l, r);      // the +-1 RMQ on its own, positions in the euler tour
//
// eulerTour is recursive: a path of 5e5 vertices needs a big stack
// (fine on Codeforces; locally run `ulimit -s 65520` first).

class FCB {
public:
    FCB(const vector<vector<int>>& _adj, int root = 0) : adj(_adj) {
        int n = adj.size();
        buildEulerTour(n, root);
        arr.resize(euler.size());
        for (int i = 0; i < (int)euler.size(); i++) arr[i] = nodeHeight[euler[i]];
        buildRMQ();
    }

    /* ============================================================
        MODULE 3: LCA = euler tour + +-1 RMQ
        ------------------------------------------------------------
        arr[i] = nodeHeight[euler[i]]
        lca(u, v) = euler[argmin(nodeStart[u], nodeStart[v])]
       ============================================================ */
    int lca(int u, int v) {
        return euler[argmin(nodeStart[u], nodeStart[v])];
    }

    int depth(int u) { return nodeHeight[u]; }

    int dist(int u, int v) {
        return nodeHeight[u] + nodeHeight[v] - 2 * nodeHeight[lca(u, v)];
    }

    // index of the min of arr[l..r] (either order)
    int argmin(int l, int r) {
        if (l > r) swap(l, r);
        int bl = l / block_size, br = r / block_size;
        if (bl == br) return queryInBlock(bl, l % block_size, r % block_size);
        int ans = minIdx(queryInBlock(bl, l % block_size, block_size-1),
                         queryInBlock(br, 0, r % block_size));
        if (bl+1 <= br-1) ans = minIdx(ans, querySparseTable(bl+1, br-1));
        return ans;
    }

private:
    vector<vector<int>> adj;

    /* ============================================================
        MODULE 0: log table
        ------------------------------------------------------------
        lg2[x] = floor(log2(x)), lg2[0] = -1
        lg2[x] = lg2[x/2] + 1
       ============================================================ */
    vector<int> lg2;

    void buildLog(int m) {
        lg2.assign(m+1, -1);
        for (int i = 1; i <= m; i++) lg2[i] = lg2[i/2] + 1;
    }

    /* ============================================================
        MODULE 1: euler tour
        ------------------------------------------------------------
        input : adj, root
        output: euler[]        vertices in visit order, size 2n - 1
                nodeStart[u]   first index of u in euler
                nodeHeight[u]  depth of u (root = 0)

        tour(u):
            write u
            for each child v:
                tour(v)
                write u again        <- comes back up through u

        => neighbouring heights in euler differ by exactly 1
        => lca(u, v) = shallowest vertex in euler[nodeStart[u] .. nodeStart[v]]
       ============================================================ */
    vector<int> euler, nodeStart, nodeHeight;

    void eulerTour(int u, int p, int h) {
        nodeStart[u] = euler.size();
        euler.push_back(u);
        nodeHeight[u] = h;
        for (int v : adj[u]) {
            if (v == p) continue;
            eulerTour(v, u, h+1);
            euler.push_back(u);
        }
    }

    void buildEulerTour(int n, int root) {
        nodeStart.assign(n, -1);
        nodeHeight.assign(n, 0);
        euler.clear();
        euler.reserve(2*n);
        eulerTour(root, -1, 0);
    }

    /* ============================================================
        MODULE 2: +-1 RMQ (Farach-Colton and Bender)
        ------------------------------------------------------------
        input : arr[0..m) with |arr[i] - arr[i-1]| = 1
        query : argmin(l, r) = index of the min of arr[l..r], O(1)
        build : O(m)

        cut arr into blocks of size b = log2(m) / 2, then
            2a. block sparse table : sparse table over each block's min
            2b. block masks        : a block is b - 1 steps of +-1 -> a (b-1)-bit mask
            2c. mask tables        : for every mask, argmin of every [l, r] in a block
                                     (2^(b-1) <= sqrt(m) masks, b^2 entries each)

        argmin(l, r):
            same block       -> mask table
            different blocks -> min of
                                  suffix of l's block       (mask table)
                                  whole blocks in between   (sparse table)
                                  prefix of r's block       (mask table)
       ============================================================ */
    vector<int> arr;
    int block_size, block_cnt;

    // index of the smaller of arr[i], arr[j]
    int minIdx(int i, int j) {
        return arr[i] < arr[j] ? i : j;
    }

    /* ---------- 2a. block sparse table ----------
        st[b][0] = argmin of block b
        st[b][k] = minIdx(st[b][k-1], st[b + 2^(k-1)][k-1])   blocks [b, b + 2^k)
        query blocks [bl, br]: two overlapping ranges of 2^k blocks
    */
    vector<vector<int>> st;

    void buildBlockSparseTable() {
        int m = arr.size();
        st.assign(block_cnt, vector<int>(lg2[block_cnt] + 1));
        for (int i = 0; i < m; i++) {
            int b = i / block_size;
            if (i % block_size == 0) st[b][0] = i;
            else st[b][0] = minIdx(st[b][0], i);
        }
        for (int k = 1; k <= lg2[block_cnt]; k++) {
            for (int b = 0; b < block_cnt; b++) {
                int nb = b + (1 << (k-1));
                if (nb < block_cnt) st[b][k] = minIdx(st[b][k-1], st[nb][k-1]);
                else st[b][k] = st[b][k-1];
            }
        }
    }

    int querySparseTable(int bl, int br) {
        int k = lg2[br - bl + 1];
        return minIdx(st[bl][k], st[br - (1 << k) + 1][k]);
    }

    /* ---------- 2b. block masks (combinatorial bitmasking) ----------
        inside a block, position j (j >= 1) steps from j-1:
            bit j-1 = 1  if arr goes up   (arr[j] = arr[j-1] + 1)
            bit j-1 = 0  if arr goes down (arr[j] = arr[j-1] - 1)
        the mask alone fixes where the min of any [l, r] is,
        so blocks with the same mask share one table
        a short last block keeps 0s for its missing steps, never read by a query
    */
    vector<int> blockMask;

    void buildBlockMasks() {
        int m = arr.size();
        blockMask.assign(block_cnt, 0);
        for (int i = 1; i < m; i++) {
            int j = i % block_size;
            if (j > 0 && arr[i] > arr[i-1]) blockMask[i / block_size] |= 1 << (j-1);
        }
    }

    /* ---------- 2c. mask tables ----------
        for every mask, every l:
            walk r = l+1 .. b-1, h += (bit r-1 ? +1 : -1)
            maskTable[mask][l][r] = position of the lowest h so far
        depends only on the mask, not on arr
    */
    vector<vector<vector<int>>> maskTable;

    void buildMaskTables() {
        int masks = 1 << (block_size - 1);
        maskTable.assign(masks, vector<vector<int>>(block_size, vector<int>(block_size)));
        for (int mask = 0; mask < masks; mask++) {
            for (int l = 0; l < block_size; l++) {
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

    // argmin of arr over positions [l, r] of block b (l, r are offsets in the block)
    int queryInBlock(int b, int l, int r) {
        return b * block_size + maskTable[blockMask[b]][l][r];
    }

    void buildRMQ() {
        int m = arr.size();
        buildLog(m);
        block_size = max(1, lg2[m] / 2);
        block_cnt = (m + block_size - 1) / block_size;
        buildBlockSparseTable(); // 2a
        buildBlockMasks();       // 2b
        buildMaskTables();       // 2c
    }
};
