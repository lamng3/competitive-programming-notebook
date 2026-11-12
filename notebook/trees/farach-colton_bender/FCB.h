#pragma once
#include <bits/stdc++.h>
using namespace std;

/*
    LCA with Farach-Colton and Bender: O(n) build, O(1) per query
    https://cp-algorithms.com/graph/lca_farachcoltonbender.html
    worked example: notebook/examples/trees/farach-colton_bender/fcb.cpp

    usage
        FCB fcb(adj, root);    adj is 0-indexed and undirected
        fcb.lca(u, v);
        fcb.dist(u, v);
        fcb.depth(u);
        fcb.argmin(l, r);      the +-1 RMQ on its own, over euler tour positions

    idea
        walk the tree as an euler tour, writing down every vertex we pass.
        between the first visits of u and v, the shallowest vertex is lca(u, v).
        neighbouring heights in the tour differ by exactly 1, which lets the
        range-min over them answer in O(1) after O(n) work.

    build steps
        1. euler tour       euler[], nodeStart[], nodeHeight[]
        2. heights          arr[i] = nodeHeight[euler[i]]
        3. log table        lg2[]
        4. +-1 RMQ on arr   block sparse table, block masks, mask tables

    query
        lca(u, v) = euler[argmin(nodeStart[u], nodeStart[v])]

    note
        eulerTour is recursive, so a path of 5e5 vertices needs a big stack:
        fine on Codeforces, locally run `ulimit -s 65520` first
*/
class FCB {
public:
    FCB(const vector<vector<int>>& _adj, int root = 0) : adj(_adj) {
        int n = adj.size();
        buildEulerTour(n, root);
        arr.resize(euler.size());
        for (int i = 0; i < (int)euler.size(); i++) arr[i] = nodeHeight[euler[i]];
        buildLog(arr.size());
        buildRMQ();
    }

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
        if (bl == br) return queryInBlock(bl, l % block_size, r % block_size);
        int ans = minIdx(queryInBlock(bl, l % block_size, block_size-1),
                         queryInBlock(br, 0, r % block_size));
        if (bl+1 <= br-1) ans = minIdx(ans, querySparseTable(bl+1, br-1));
        return ans;
    }

private:
    vector<vector<int>> adj;

    /*
        EULER TOUR
        ----------
        write u, and write it again each time a child returns to it

            tour(u):
                write u
                for each child v:
                    tour(v)
                    write u

        euler[]        every vertex in the order we pass it, 2n - 1 entries
        nodeStart[u]   where u first appears in euler
        nodeHeight[u]  depth of u, root = 0

        every step goes down to a child or back up to the parent,
        so neighbouring heights in euler differ by exactly 1
    */
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

    /*
        LOG TABLE
        ---------
        lg2[x] = floor(log2(x)), lg2[0] = -1
    */
    vector<int> lg2;

    void buildLog(int m) {
        lg2.assign(m+1, -1);
        for (int i = 1; i <= m; i++) lg2[i] = lg2[i/2] + 1;
    }

    /*
        +-1 RMQ
        -------
        argmin(l, r) = position of the min of arr[l..r], O(1),
        for any arr whose neighbours differ by exactly 1

        cut arr into blocks of b = log2(m) / 2 entries; a query splits into

            l ... ] [ block ] [ block ] ... [ block ] [ ... r
            suffix of     whole blocks in between      prefix of
            l's block                                  r's block

        whole blocks      sparse table over the block minimums
        inside a block    a block is b - 1 steps of +1 / -1, a (b-1)-bit mask,
                          so precompute the answers for every mask once
                          (2^(b-1) <= sqrt(m) masks, b^2 answers each)
    */
    vector<int> arr;
    int block_size, block_cnt;

    // position of the smaller of arr[i], arr[j]
    int minIdx(int i, int j) {
        return arr[i] < arr[j] ? i : j;
    }

    // ---- sparse table over blocks ----
    /*
        st[b][0] = position of the min of block b
        st[b][k] = position of the min of blocks [b, b + 2^k)
        blocks [bl, br] = two overlapping runs of 2^k blocks, k = lg2[br - bl + 1]
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

    // ---- block masks ----
    /*
        bit j-1 of a block's mask is the step from offset j-1 to j
            1 = up    arr[j] = arr[j-1] + 1
            0 = down  arr[j] = arr[j-1] - 1
        blocks with the same mask have their mins in the same places
        a short last block reads its missing steps as 0; no query reaches them
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

    // ---- mask tables ----
    /*
        maskTable[mask][l][r] = offset of the min of [l, r] in a block shaped like mask
        walk right from l with a running height h, keep where h was lowest
        built from the mask alone, never reads arr
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

    // position of the min over offsets [l, r] of block b
    int queryInBlock(int b, int l, int r) {
        return b * block_size + maskTable[blockMask[b]][l][r];
    }

    // ---- build ----
    void buildRMQ() {
        int m = arr.size();
        block_size = max(1, lg2[m] / 2);
        block_cnt = (m + block_size - 1) / block_size;
        buildBlockSparseTable();
        buildBlockMasks();
        buildMaskTables();
    }
};
