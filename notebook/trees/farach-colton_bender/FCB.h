#pragma once
#include <bits/stdc++.h>
using namespace std;

/*
    LCA with Farach-Colton and Bender: O(n) build, O(1) per query
    follows https://cp-algorithms.com/graph/lca_farachcoltonbender.html
    notes: README.md next to this file

    lca(u, v) = shallowest vertex in euler_tour[first_visit[u] .. first_visit[v]]

    usage
        FCB fcb(adj, root);    adj is 0-indexed and undirected
        fcb.lca(u, v);  fcb.dist(u, v);  fcb.depth(u);

    dfs is recursive: a path of 5e5 vertices needs `ulimit -s 65520` locally
*/
class FCB {
public:
    FCB(const vector<vector<int>>& _adj, int root = 0) : n(_adj.size()), adj(_adj) {
        precompute_lca(root);
    }

    /*
        range [l, r] = [first_visit[v], first_visit[u]]
            same block       ->  lca_in_block
            different blocks ->  min of
                                   suffix of l's block    (lca_in_block)
                                   blocks in between      (sparse table)
                                   prefix of r's block    (lca_in_block)
        each part is O(1)
    */
    int lca(int v, int u) {
        int l = first_visit[v];
        int r = first_visit[u];
        if (l > r)
            swap(l, r);
        int bl = l / block_size;
        int br = r / block_size;
        if (bl == br)
            return euler_tour[lca_in_block(bl, l % block_size, r % block_size)];
        int ans1 = lca_in_block(bl, l % block_size, block_size - 1);
        int ans2 = lca_in_block(br, 0, r % block_size);
        int ans = min_by_h(ans1, ans2);
        if (bl + 1 < br) {
            int l = log_2[br - bl - 1];
            int ans3 = st[bl+1][l];
            int ans4 = st[br - (1 << l)][l];
            ans = min_by_h(ans, min_by_h(ans3, ans4));
        }
        return euler_tour[ans];
    }

    int depth(int v) {
        return height[v];
    }

    int dist(int u, int v) {
        return height[u] + height[v] - 2 * height[lca(u, v)];
    }

private:
    int n;
    vector<vector<int>> adj;

    int block_size, block_cnt;
    vector<int> first_visit;              // first index of v in euler_tour
    vector<int> euler_tour;               // v written on entry and after each child returns
    vector<int> height;                   // depth of v, root = 0
    vector<int> log_2;                    // log_2[x] = floor(log2(x))
    vector<vector<int>> st;               // st[b][k] = min of blocks [b, b + 2^k)
    vector<vector<vector<int>>> blocks;   // blocks[mask][l][r] = min of [l, r] inside a block
    vector<int> block_mask;               // bit j-1 = 1 if height goes +1 from offset j-1 to j

    /*
        euler tour: write v on entry, and again each time a child returns to v

        claim: the shallowest vertex between a visit of u and a visit of v is lca(u, v)
        proof:
            - u and v are in lca's subtree, and the tour stays inside that subtree
              from entering lca to leaving it, so nothing shallower than lca appears
            - from u's branch to v's branch the tour must come back up to lca
              (if u is the lca, u itself is in the range)
        any visit works, so first_visit is enough: no last visit is needed

        each step goes to a child or back to the parent, so neighbouring heights differ by 1
    */
    void dfs(int v, int p, int h) {
        first_visit[v] = euler_tour.size();
        euler_tour.push_back(v);
        height[v] = h;

        for (int u : adj[v]) {
            if (u == p)
                continue;
            dfs(u, v, h + 1);
            euler_tour.push_back(v); // back up through v
        }
    }

    // of two euler_tour indices, the one whose vertex is shallower
    int min_by_h(int i, int j) {
        return height[euler_tour[i]] < height[euler_tour[j]] ? i : j;
    }

    void precompute_log(int m) {
        log_2.assign(m + 1, -1);
        for (int i = 1; i <= m; i++)
            log_2[i] = log_2[i / 2] + 1;
    }

    /*
        cut the tour into blocks of size log2(m) / 2
        st[b][0] = min of block b
        st[b][k] = min of st[b][k-1] and st[b + 2^(k-1)][k-1]

        m / block_size blocks, each with log(m) levels: O(m) in total
        a query over blocks uses two runs of 2^k blocks that may overlap,
        which is fine for min: min(x, x) = x
    */
    void precompute_sparse_table(int m) {
        st.assign(block_cnt, vector<int>(log_2[block_cnt] + 1));
        for (int i = 0, j = 0, b = 0; i < m; i++, j++) {
            if (j == block_size)
                j = 0, b++;
            if (j == 0 || min_by_h(i, st[b][0]) == i)
                st[b][0] = i;
        }
        for (int l = 1; l <= log_2[block_cnt]; l++) {
            for (int i = 0; i < block_cnt; i++) {
                int ni = i + (1 << (l - 1));
                if (ni >= block_cnt)
                    st[i][l] = st[i][l-1];
                else
                    st[i][l] = min_by_h(st[i][l-1], st[ni][l-1]);
            }
        }
    }

    /*
        a block of size b is b - 1 steps of +1 or -1, so its shape is a (b-1)-bit mask
        bit j-1 = 1 when height goes +1 from offset j-1 to j

        claim: the mask alone decides where the min of [l, r] is
        proof: height at offset r = height at offset 0 + (sum of steps before r),
               so two blocks with the same mask differ only by a constant
    */
    void precompute_block_mask(int m) {
        block_mask.assign(block_cnt, 0);
        for (int i = 0, j = 0, b = 0; i < m; i++, j++) {
            if (j == block_size)
                j = 0, b++;
            if (j > 0 && min_by_h(i - 1, i) == i - 1)
                block_mask[b] += 1 << (j - 1);
        }
    }

    // precompute RMQ for each unique block
    void precompute_blocks(int m) {
        int FULL = 1 << (block_size - 1); // number of masks
        blocks.assign(FULL, {});
        for (int b = 0; b < block_cnt; b++) {
            int mask = block_mask[b];
            if (!blocks[mask].empty())
                continue;
            blocks[mask].assign(block_size, vector<int>(block_size));
            for (int l = 0; l < block_size; l++) {
                blocks[mask][l][l] = l;
                for (int r = l + 1; r < block_size; r++) {
                    blocks[mask][l][r] = blocks[mask][l][r - 1];
                    if (b * block_size + r < m)
                        blocks[mask][l][r] = min_by_h(b * block_size + blocks[mask][l][r],
                                b * block_size + r) - b * block_size;
                }
            }
        }
    }

    void precompute_lca(int root) {
        // get euler tour & indices of first occurrences
        first_visit.assign(n, -1);
        height.assign(n, 0);
        euler_tour.clear();
        euler_tour.reserve(2 * n);
        dfs(root, -1, 0);

        int m = euler_tour.size();
        precompute_log(m);
        block_size = max(1, log_2[m] / 2);
        block_cnt = (m + block_size - 1) / block_size;

        precompute_sparse_table(m);
        precompute_block_mask(m);
        precompute_blocks(m);
    }

    // euler_tour index of the min over offsets [l, r] of block b
    int lca_in_block(int b, int l, int r) {
        return blocks[block_mask[b]][l][r] + b * block_size;
    }
};
