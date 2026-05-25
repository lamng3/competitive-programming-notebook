// g++ -std=c++17 -DLOCAL template.cpp -o solution
#include <bits/stdc++.h>
using namespace std;

#pragma region Debug
#ifdef LOCAL
template<typename T, typename U>
ostream& operator<<(ostream& os, const pair<T,U>& p) {
    return os << "(" << p.first << ", " << p.second << ")";
}
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    os << "[";
    for (int i = 0; i < (int)v.size(); i++) os << (i ? ", " : "") << v[i];
    return os << "]";
}
template<typename T>
ostream& operator<<(ostream& os, const set<T>& s) {
    os << "{";
    int i = 0;
    for (auto& x : s) os << (i++ ? ", " : "") << x;
    return os << "}";
}
template<typename K, typename V>
ostream& operator<<(ostream& os, const map<K,V>& m) {
    os << "{";
    int i = 0;
    for (auto& [k, v] : m) os << (i++ ? ", " : "") << k << ": " << v;
    return os << "}";
}
void _dbg() { cerr << endl; }
template<typename T, typename... A>
void _dbg(T t, A... a) { cerr << " " << t; if constexpr(sizeof...(a)) cerr << ","; _dbg(a...); }
#define dbg(...) cerr << "\033[35m[" << #__VA_ARGS__ << "]\033[0m:", _dbg(__VA_ARGS__)
#else
#define dbg(...)
#endif
#pragma endregion

using ll = long long;
using vi = vector<int>;
using vii = vector<vector<int>>;
using pii = pair<int, int>;

#define REP(i, n) for (int i = 0; i < (n); i++)
#define FOR(i, a, b) for (int i = (a); i <= (b); i++)
#define FORD(i, a, b) for (int i = (a); i >= (b); i--)
#define RFOR(i, n) for (int i = (n) - 1; i >= 0; i--)

#define fi first
#define se second
#define pb push_back

const int INF = 1e9;
const ll LLINF = 2e18;

const int MOD = 1e9+7;

const int MAXNODES = 1e5+5;
const int MAXSTEPS = 25;

vi g[MAXNODES];
int lift[MAXNODES][MAXSTEPS];
int depth[MAXNODES];

// 3559. Number of Ways to Assign Edge Weights II [Hard]
class Solution {
private:
    ll binpow(ll a, ll b) {
        a %= MOD;
        ll res = 1;
        while (b) {
            if (b % 2) res = (res * a) % MOD;
            a = (a * a) % MOD;
            b >>= 1;
        }
        return res;
    }

public:
    void buildTree(int n, const vii& edges) {
        FOR(i, 0, n) g[i].clear();

        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].pb(v);
            g[v].pb(u);
        }
    }

    void dfs(int u, int p, int d) {
        depth[u] = d;
        lift[u][0] = p;
        for (int v : g[u]) {
            if (v != p) {
                dfs(v, u, d + 1);
            }
        }
    }

    void buildLift(int n) {
        FOR(j, 1, MAXSTEPS - 1) {
            FOR(i, 1, n) { 
                if (lift[i][j - 1] != -1) {
                    lift[i][j] = lift[lift[i][j - 1]][j - 1];
                }
            }
        }
    }

    int moveK(int node, int k) {
        REP(j, MAXSTEPS) {
            if (k & (1 << j)) {
                node = lift[node][j];
                if (node == -1) break;
            }
        }
        return node;
    }

    int getLCA(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        
        u = moveK(u, depth[u] - depth[v]);
        if (u == v) return u;

        RFOR(j, MAXSTEPS) {
            if (lift[u][j] != lift[v][j] && lift[u][j] != -1) {
                u = lift[u][j];
                v = lift[v][j];
            }
        }
        
        return lift[u][0]; 
    }

    int pathLength(int u, int v) {
        int lca = getLCA(u, v);
        return depth[u] + depth[v] - 2 * depth[lca];
    }

    int query(int u, int v) {
        int N = pathLength(u, v);
        if (N == 0) return 0;
        return binpow(2, N-1);
    }

    vi assignEdgeWeights(vii& edges, vii& queries) {
        int n = edges.size() + 1;

        memset(lift, -1, sizeof lift);
        buildTree(n, edges);
        
        dfs(1, -1, 0);
        buildLift(n);

        int m = (int)queries.size();
        vi ans(m);
        REP(i, m) {
            ans[i] = query(queries[i][0], queries[i][1]);
        }
        return ans;
    }
};

#if !defined(CPTEST) && (defined(LOCAL) || defined(ONLINE_JUDGE))
void preprocess() {

}

void solve() {

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    preprocess();
    int tt = 1;
    // cin >> tt;
    while (tt--) solve();
    return 0;
}
#endif