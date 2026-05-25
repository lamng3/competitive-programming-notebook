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

const int MAXN = 1e5+5;

vi g[MAXN], gT[MAXN]; // gT = transpose of graph
vi order;
int vis[MAXN], id[MAXN];

void dfs1(int u) {
    vis[u] = 1;
    for (int v : g[u]) {
        if (!vis[v]) dfs1(v);
    }
    order.pb(u);
}

void dfs2(int u, int comp) {
    vis[u] = 1;
    for (int v : gT[u]) {
        if (!vis[v]) dfs2(v, comp);
    }
    id[u] = comp;
}

// 2360. Longest Cycle in a Graph [Hard]
class Solution {
public:
    int longestCycle(vi& edges) {
        int n = (int)edges.size();

        order.clear(); 
        for (int i = 0; i < n; i++) {
            g[i].clear();
            gT[i].clear();
            vis[i] = 0;
            id[i] = -1;
        }

        REP(i, n) {
            if (edges[i] != -1) {
                g[i].pb(edges[i]);
                gT[edges[i]].pb(i);
            }
        }

        memset(vis, 0, sizeof vis);
        REP(u, n) {
            if (!vis[u]) dfs1(u);
        }
        
        memset(vis, 0, sizeof vis);
        reverse(order.begin(), order.end());
        int comp = 0;
        for (int u : order) {
            if (!vis[u]) {
                comp++;
                dfs2(u, comp);
            }
        }

        // dbg(order);
        // REP(i, n) dbg(i, id[i]);

        int ans = -1;
        map<int,int> f;
        REP(i, n) {
            f[id[i]]++;
            if (f[id[i]] > 1) ans = max(ans, f[id[i]]);
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