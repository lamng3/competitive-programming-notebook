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

/*
    Codeforces 342E Xenia and Tree
    https://codeforces.com/contest/342/problem/E

    lca(u, v) = shallowest vertex in euler_tour[first_visit[u] .. first_visit[v]], O(1) by sparse table
    sqrt on queries: minDistRed is rebuilt by bfs every THRESHOLD reds,
    reds since then sit in changedNodes and are checked one by one
*/

const int MAX_N = 1e5;
const int THRESHOLD = 300;

int n;
vii adj;

vi first_visit;
vi euler_tour;
vi height;
vi log_2;
vii st; // st[i][j] = index of the shallowest vertex in euler_tour[i, i + 2^j)

void flatten(int v, int p, int h) {
    first_visit[v] = sz(euler_tour);
    euler_tour.pb(v);
    height[v] = h;

    for (int u : adj[v]) {
        if (u == p) continue;
        flatten(u, v, h + 1);
        euler_tour.pb(v);
    }
}

int min_by_h(int i, int j) {
    return height[euler_tour[i]] < height[euler_tour[j]] ? i : j;
}

void precompute_log(int m) {
    log_2.assign(m + 1, -1);
    FOR(i, 1, m) log_2[i] = log_2[i / 2] + 1;
}

void precompute_sparse_table() {
    int m = sz(euler_tour);
    st.assign(m, vi(log_2[m] + 1));
    REP(i, m) st[i][0] = i;
    FOR(j, 1, log_2[m]) {
        REP(i, m) {
            if (i + (1 << j) > m) continue;
            st[i][j] = min_by_h(st[i][j-1], st[i + (1 << (j-1))][j-1]);
        }
    }
}

void precompute_lca(int root) {
    first_visit.assign(n, -1);
    height.assign(n, 0);
    euler_tour.clear();
    euler_tour.reserve(2 * n);
    flatten(root, -1, 0);

    precompute_sparse_table();
}

int lca(int u, int v) {
    int l = first_visit[u], r = first_visit[v];
    if (l > r) swap(l, r);
    int k = log_2[r - l + 1];
    return euler_tour[min_by_h(st[l][k], st[r - (1 << k) + 1][k])];
}

int getDist(int u, int v) {
    return height[u] + height[v] - 2 * height[lca(u, v)];
}

vi changedNodes; // reds not yet in minDistRed
vi minDistRed;

void updateMinDistRed() {
    vi dist(n, -1);
    queue<int> q;
    for (int r : changedNodes) {
        dist[r] = 0;
        q.push(r);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] != -1) continue;
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
    REP(u, n) minDistRed[u] = min(minDistRed[u], dist[u]);
    changedNodes.clear();
}

void changeColor(int u) {
    changedNodes.pb(u);
    if (sz(changedNodes) >= THRESHOLD) updateMinDistRed();
}

int getMinDistRed(int u) {
    int res = minDistRed[u];
    for (int v : changedNodes) res = min(res, getDist(u, v));
    return res;
}

void preprocess() {
    precompute_log(2 * MAX_N);
}

void solve() {
    int q; cin >> n >> q;
    adj.assign(n, {});
    REP(i, n-1) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    precompute_lca(0);

    // vertex 1 starts red
    minDistRed.assign(n, INF);
    changedNodes = {0};
    updateMinDistRed();

    REP(i, q) {
        int t, u; cin >> t >> u;
        u--;
        if (t == 1) changeColor(u);
        else cout << getMinDistRed(u) << '\n';
    }
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
