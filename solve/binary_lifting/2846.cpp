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
const int MOD_NTT = 998244353; // number theoretic transform (NTT)

const int MAXNODES = 1e4+5;
const int MAXSTEPS = 20;

int lift[MAXNODES][MAXSTEPS];
vector<pii> g[MAXNODES];
int parent[MAXNODES], depth[MAXNODES];

// count[u][w] = # times w appears from root to u
int cnt[MAXNODES][30];

// 2846. Minimum Edge Weight Equilibrium Queries in a Tree [Hard]
class Solution {
public:
    void flatten(int u, int p, int d) {
        depth[u] = d;
        parent[u] = p;
        lift[u][0] = p;
        
        for (auto pr : g[u]) {
            int v = pr.fi, w = pr.se;
            if (v != p) {
                REP(i, 27) cnt[v][i] = cnt[u][i];
                cnt[v][w]++;
                flatten(v, u, d+1);
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

    int getLCA(int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        int diff = abs(depth[a] - depth[b]);
        a = moveK(a, diff);
        if (a == b) return a;
        RFOR(j, MAXSTEPS) {
            if (a != -1 && b != -1 && lift[a][j] != lift[b][j]) {
                a = lift[a][j];
                b = lift[b][j];
            }
        }
        return lift[a][0];
    }

    int query(int u, int v) {
        int lca = getLCA(u, v);
        int tot = depth[u] + depth[v] - 2 * depth[lca];
        int dom = 0;
        REP(w, 27) {
            int fw = cnt[u][w] + cnt[v][w] - 2 * cnt[lca][w];
            dom = max(dom, fw);
        }
        return tot - dom;
    }

    vi minOperationsQueries(int n, vii& edges, vii& queries) {
        REP(i, n) {
            g[i].clear();
            depth[i] = parent[i] = -1;
        }
        memset(lift, -1, sizeof lift);
        memset(cnt, 0, sizeof cnt);

        for (auto& e : edges) {
            // track weights
            int u = e[0], v = e[1], w = e[2];
            g[u].pb({v, w});
            g[v].pb({u, w});
        }

        flatten(0, -1, 0);

        FOR(j, 1, MAXSTEPS) {
            REP(i, n) {
                if (lift[i][j-1] != -1) {
                    lift[i][j] = lift[lift[i][j-1]][j-1];
                }
            }
        }

        int m = (int)queries.size();
        vi ans(m);
        REP(i, m) {
            int u = queries[i][0], v = queries[i][1];
            ans[i] = query(u, v);
        }
        return ans;
    }
};

#if !defined(CPTEST) && (defined(LOCAL) || defined(ONLINE_JUDGE))
void preprocess() {
    
}

// cout << Solution().solve() << '\n';
void solve() {
    
}

int main() {
    // freopen("name.in", "r", stdin);
    // freopen("name.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    preprocess();
    int tt = 1;
    // cin >> tt;
    while (tt--) solve();
    return 0;
}
#endif