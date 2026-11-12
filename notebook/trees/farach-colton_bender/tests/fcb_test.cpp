// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall fcb_test.cpp -o /tmp/fcbtest && /tmp/fcbtest
#include "../FCB.h"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)

// lca by climbing parents
int bruteLca(int u, int v, const vector<int>& par, const vector<int>& dep) {
    while (dep[u] > dep[v]) u = par[u];
    while (dep[v] > dep[u]) v = par[v];
    while (u != v) u = par[u], v = par[v];
    return u;
}

int main() {
    // 1) the complete binary tree from the problem statement, 0-indexed
    vector<vector<int>> g(7);
    vector<pair<int, int>> edges = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}};
    for (auto [a, b] : edges) g[a].push_back(b), g[b].push_back(a);
    FCB fcb(g, 0);
    CHECK(fcb.lca(3, 4) == 1);
    CHECK(fcb.lca(3, 5) == 0);
    CHECK(fcb.lca(1, 3) == 1);
    CHECK(fcb.lca(5, 6) == 2);
    CHECK(fcb.lca(2, 0) == 0);
    CHECK(fcb.dist(3, 6) == 4);

    // 2) a single vertex
    FCB one(vector<vector<int>>(1), 0);
    CHECK(one.lca(0, 0) == 0);

    // 3) random trees (paths, bushy, random) and random roots against parent climbing
    mt19937 rng(7);
    for (int it = 0; it < 300; it++) {
        int n = rng() % 200 + 1, shape = rng() % 3;
        vector<vector<int>> adj(n);
        for (int i = 1; i < n; i++) {
            int j = shape == 0 ? i-1 : shape == 1 ? rng() % i : i-1 - rng() % min(i, 3);
            adj[i].push_back(j), adj[j].push_back(i);
        }
        int root = rng() % n;
        vector<int> par(n, -1), dep(n, 0), order = {root};
        for (int k = 0; k < (int)order.size(); k++) {
            int u = order[k];
            for (int v : adj[u]) if (v != par[u]) par[v] = u, dep[v] = dep[u] + 1, order.push_back(v);
        }
        FCB f(adj, root);
        for (int q = 0; q < 200; q++) {
            int u = rng() % n, v = rng() % n;
            CHECK(f.lca(u, v) == bruteLca(u, v, par, dep));
        }
    }

    printf("\n%d checks, %d failed.\n", checks, fails);
    return fails ? 1 : 0;
}
