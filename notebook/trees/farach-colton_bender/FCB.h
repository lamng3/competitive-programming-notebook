#pragma once
#include <bits/stdc++.h>
using namespace std;

/*
    LCA with Farach-Colton and Bender: O(n) build, O(1) per query
    follows https://cp-algorithms.com/graph/lca_farachcoltonbender.html
    why it works: README.md next to this file

    FCB fcb(adj, root);    adj is 0-indexed and undirected
    fcb.lca(u, v);  fcb.dist(u, v);  fcb.depth(u);

    dfs is recursive: a path of 5e5 vertices needs `ulimit -s 65520` locally
*/
class FCB {
public:
    FCB(const vector<vector<int>>& _adj, int root = 0) : n(_adj.size()), adj(_adj) {
        precompute_lca(root);
    }

    int lca(int v, int u) {
        int l = first_visit[v];
        int r = first_visit[u];
        if (l > r)
            swap(l, r);
        int bl = l / block_size;
        int br = r / block_size;
        // both ends in one block
        if (bl == br)
            return euler_tour[lca_in_block(bl, l % block_size, r % block_size)];
        // suffix of l's block, prefix of r's block
        int suffix = lca_in_block(bl, l % block_size, block_size - 1);
        int prefix = lca_in_block(br, 0, r % block_size);
        int ans = min_by_h(suffix, prefix);
        // whole blocks in between
        if (bl + 1 < br) {
            int k = log_2[br - bl - 1];
            int mid_left = st[bl + 1][k];           // blocks [bl+1, bl+1 + 2^k)
            int mid_right = st[br - (1 << k)][k];   // blocks [br - 2^k, br)
            ans = min_by_h(ans, min_by_h(mid_left, mid_right));
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
    vector<int> first_visit;
    vector<int> euler_tour;
    vector<int> height;
    vector<int> log_2;
    vector<vector<int>> st;
    vector<vector<vector<int>>> blocks;
    vector<int> block_mask;

    void dfs(int v, int p, int h) {
        first_visit[v] = euler_tour.size();
        euler_tour.push_back(v);
        height[v] = h;

        for (int u : adj[v]) {
            if (u == p)
                continue;
            dfs(u, v, h + 1);
            euler_tour.push_back(v);
        }
    }

    int min_by_h(int i, int j) {
        return height[euler_tour[i]] < height[euler_tour[j]] ? i : j;
    }

    // precompute all log values
    void precompute_log(int m) {
        log_2.assign(m + 1, -1);
        for (int i = 1; i <= m; i++)
            log_2[i] = log_2[i / 2] + 1;
    }

    // precompute minimum of each block and build sparse table
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

    // precompute mask for each block
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

    int lca_in_block(int b, int l, int r) {
        return blocks[block_mask[b]][l][r] + b * block_size;
    }
};
