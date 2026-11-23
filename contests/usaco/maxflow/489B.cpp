#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
template<class T, class U>
ostream& operator<<(ostream& os, const pair<T, U>& p) {
    return os << "(" << p.first << ", " << p.second << ")";
}
template<class T, class = void>
struct is_iterable : false_type {};
template<class T>
struct is_iterable<T, void_t<decltype(begin(declval<T&>())), decltype(end(declval<T&>()))>> : true_type {};
template<class T, enable_if_t<is_iterable<T>::value && !is_convertible_v<T, string_view>, int> = 0>
ostream& operator<<(ostream& os, const T& a) {
    os << "[";
    bool first = true;
    for (const auto& x : a) {
        if (!first) os << ", ";
        first = false;
        os << x;
    }
    return os << "]";
}
template<class T, class... A>
void _dbg(const T& t, const A&... a) {
    cerr << " " << t;
    if constexpr (sizeof...(a)) {
        cerr << ",";
        _dbg(a...);
    } else cerr << endl;
}
#define dbg(...) (cerr << "[" << #__VA_ARGS__ << "]:", _dbg(__VA_ARGS__))
#else
#define dbg(...)
#endif

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
// const int MOD = 998244353; // 1e9+7
const int MOD = 1e9+7;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void preprocess() {
    
}

int k;
vii capacity;
vii Adj;

int bfs(int s, int t, vi& parent) {
    vi vis(k, 0);
    vis[s] = 1;

    queue<pii> q;
    q.push({s, INF});

    while (!q.empty()) {
        auto [cur, flow] = q.front();
        q.pop();
        for (int nxt : Adj[cur]) {
            if (vis[nxt] || capacity[cur][nxt] <= 0) continue;
            vis[nxt] = 1;
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
    vi parent(k);
    int new_flow;
    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow; 
        // reconstruct
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
    int n; cin >> n;
    vi a(n); 
    REP(i,n) cin >> a[i];
    
    int m; cin >> m;
    vi b(m); 
    REP(j,m) cin >> b[j];

    int s = 0, t = m+n+1;
    k = t+1;

    capacity.assign(k, vi(k, 0));
    Adj.assign(k, vi());

    auto add_edge = [&](int u, int v, int cap) {
        Adj[u].pb(v);
        Adj[v].pb(u);
        capacity[u][v] = cap;
    };

    REP(i,n) add_edge(s, i+1, 1);
    REP(j,m) add_edge(n+j+1, t, 1);

    REP(i,n) {
        REP(j,m) {
            if (abs(a[i] - b[j]) > 1) continue;
            add_edge(i+1, n+j+1, 1);
        }
    }

    int ans = maxflow(s, t);
    cout << ans << '\n';
}

int main() {
    // freopen("name.in", "r", stdin);
    // freopen("name.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cerr.tie(0);
    preprocess();
    int tt = 1;
    // cin >> tt;
    while (tt--) solve();
    return 0;
}
