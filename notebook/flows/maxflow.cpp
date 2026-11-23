#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128;
using u128 = unsigned __int128;

using vi = vector<int>;
using vii = vector<vector<int>>;
using pii = pair<int, int>;

#define REP(i, n) for (int i = 0; i < (n); i++)
#define FOR(i, a, b) for (int i = (a); i <= (b); i++)
#define FORD(i, a, b) for (int i = (a); i >= (b); i--)
#define RFOR(i, n) for (int i = (n) - 1; i >= 0; i--)

#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())

#define fi first
#define se second
#define pb push_back

const int INF = 1e9+7;
const int MOD = 1e9+7;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int n;
vii capacity;
vii Adj;

int bfs(int s, int t, vi& parent) {
    vector<bool> vis(n, false);
    vis[s] = true;

    queue<pii> q;
    q.push({s, INF});

    while (!q.empty()) {
        auto [cur, flow] = q.front();
        q.pop();
        
        for (int nxt : Adj[cur]) {
            if (vis[nxt] || capacity[cur][nxt] <= 0) continue;
            vis[nxt] = true;
            parent[nxt] = cur;
            int new_flow = min(flow, capacity[cur][nxt]);
            if (nxt == t) return new_flow;
            q.push({nxt, new_flow});
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vi parent(n);
    int new_flow;
    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;

        // reconstruct f(u, v) += C and f(v,u) -= C with C = min residual in augmenting path
        int cur = t;
        while (cur != s) {
            int prv = parent[cur];
            capacity[prv][cur] -= new_flow;
            capacity[cur][prv] += new_flow;
            cur = prv;
        }
    }
    
    return flow;
}

void solve() {
    
}

int main() {
    // freopen("name.in", "r", stdin);
    // freopen("name.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    // cin >> tt;
    while (tt--) solve();
    return 0;
}