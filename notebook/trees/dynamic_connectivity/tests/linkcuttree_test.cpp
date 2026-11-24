// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall linkcuttree_test.cpp -o /tmp/lcttest && /tmp/lcttest
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
#define REP(i, n) for (int i = 0; i < (n); i++)
#define FOR(i, a, b) for (int i = (a); i <= (b); i++)
#define FORD(i, a, b) for (int i = (a); i >= (b); i--)
#define sz(x) (int)((x).size())
#define fi first
#define se second
#define pb push_back
#include "../LinkCutTree.h"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)

// the nodes on the path from u to v in the forest, or nothing if they are not connected
vi treePath(int n, const set<pii>& edges, int u, int v) {
    vector<vi> adj(n + 1);
    for (auto [a, b] : edges) {
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vi from(n + 1, -1);
    from[u] = 0;
    queue<int> q;
    q.push(u);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int y : adj[x]) if (from[y] == -1) {
            from[y] = x;
            q.push(y);
        }
    }
    if (from[v] == -1) return {};
    vi p = {u};
    for (int x = v; x != u; x = from[x]) p.pb(x);
    return p;
}

int main() {
    // 1) by hand: the path 1-2-3 and the lone node 4, with value i on node i
    LinkCutTree t(4);
    FOR(i, 1, 4) t.assign(i, i);
    t.link(1, 2);
    t.link(2, 3);
    CHECK(t.connected(1, 3) && !t.connected(1, 4));
    CHECK(t.query(1, 3) == 6 && t.query(3, 2) == 5 && t.query(2, 2) == 2);
    t.cut(3, 2);
    CHECK(!t.connected(1, 3) && t.connected(2, 1));
    t.link(3, 4);
    t.link(4, 1);                 // 3-4-1-2
    CHECK(t.query(3, 2) == 10 && t.findRoot(2) == t.findRoot(3));

    // 2) random forests against a breadth-first search
    mt19937 rng(11);
    REP(it, 400) {
        int n = rng() % 12 + 1;
        LinkCutTree s(n);
        vector<ll> a(n + 1);
        set<pii> edges;
        REP(q, 300) {
            int u = rng() % n + 1, v = rng() % n + 1, op = rng() % 5;
            vi p = treePath(n, edges, u, v);
            if (op == 0 && p.empty()) {
                s.link(u, v);
                edges.insert({min(u, v), max(u, v)});
            }
            else if (op == 1 && sz(edges)) {
                auto [x, y] = *next(edges.begin(), rng() % sz(edges));
                edges.erase({x, y});
                if (rng() % 2) swap(x, y);
                s.cut(x, y);
            }
            else if (op == 2) {
                CHECK(s.connected(u, v) == !p.empty());
            }
            else if (op == 3) {
                ll x = ll(rng() % 21) - 10;
                s.assign(u, x);
                a[u] = x;
            }
            else if (!p.empty()) {
                ll want = 0;
                for (int x : p) want += a[x];
                CHECK(s.query(u, v) == want);
            }
        }
    }

    printf("\n%d checks, %d failed.\n", checks, fails);
    return fails ? 1 : 0;
}
