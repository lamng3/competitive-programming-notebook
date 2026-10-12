#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Mo 2D rectilinear spanning tree ordering
// Section: 2. Data Structure / Sqrt Decomposition
// Status: written and tested, not studied yet
//
// Mo's algorithm in the order of a Manhattan minimum spanning tree of the query
// points (L, R). Walking the tree in DFS order travels each edge at most twice, so
// the window moves at most 2 * (MST weight) + the cost of the first query: never
// more than about twice the best possible tour.
//
// The Manhattan MST: for every point, only the nearest point in each of the 8
// octants can be a useful neighbor, and by symmetry 4 sweeps find them all. Each
// sweep sorts by x + y, and an ordered map holds the points still waiting for
// their nearest neighbor in the octant.
// Then Kruskal on those O(4q) edges.

vector<array<long long, 3>> manhattan_mst_edges(vector<pair<long long, long long>> p) { // (w, i, j)
    int n = p.size();
    vector<array<long long, 3>> edges;
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    for (int k = 0; k < 4; k++) {
        sort(id.begin(), id.end(), [&](int i, int j) {
            return p[i].first + p[i].second < p[j].first + p[j].second; // by x + y
        });
        map<long long, int> best; // key -y: points still waiting for their octant neighbor
        for (int i : id) {
            for (auto it = best.lower_bound(-p[i].second); it != best.end(); it = best.erase(it)) {
                int j = it->second;
                long long dx = p[i].first - p[j].first, dy = p[i].second - p[j].second;
                if (dy > dx) break;
                edges.push_back({dx + dy, i, j});
            }
            best[-p[i].second] = i;
        }
        for (auto& q : p) {
            if (k & 1) q.first = -q.first;
            else swap(q.first, q.second);
        }
    }
    return edges;
}

template <class Add, class Remove, class Answer>
void mo_mst(const vector<pair<int, int>>& qs, Add add, Remove remove, Answer answer) {
    int q = qs.size();
    if (q == 0) return;
    vector<pair<long long, long long>> p(q);
    for (int i = 0; i < q; i++) p[i] = {qs[i].first, qs[i].second};
    auto edges = manhattan_mst_edges(p);
    sort(edges.begin(), edges.end());
    vector<int> par(q);
    iota(par.begin(), par.end(), 0);
    function<int(int)> find = [&](int v) { return par[v] == v ? v : par[v] = find(par[v]); };
    vector<vector<int>> g(q);
    for (auto& [w, i, j] : edges) {
        int a = find(i), b = find(j);
        if (a != b) par[a] = b, g[i].push_back(j), g[j].push_back(i);
    }
    // DFS order of the tree, iteratively
    vector<int> order, st = {0};
    vector<bool> seen(q, false);
    seen[0] = true;
    while (!st.empty()) {
        int u = st.back(); st.pop_back();
        order.push_back(u);
        for (int v : g[u]) if (!seen[v]) seen[v] = true, st.push_back(v);
    }
    int L = 0, R = -1;
    for (int id : order) {
        auto [l, r] = qs[id];
        while (L > l) add(--L);
        while (R < r) add(++R);
        while (L < l) remove(L++);
        while (R > r) remove(R--);
        answer(id);
    }
}
