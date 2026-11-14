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
    LCA with an Euler tour + sparse table: O(n log n) build, O(1) per query
    the short version of fcb.cpp: the same tour, but one sparse table over the whole tour
    instead of blocks and masks
    as a class: notebook/trees/farach-colton_bender/FCB_simple.h
    why it works: notebook/trees/farach-colton_bender/README.md, Part 1 and Part 3
*/

const int MAX_N = 5e5;

int n;
vii adj;

vi first_visit;
vi euler_tour;
vi height;
vi log_2;
vii st; // st[k][i] = tour index of the shallowest entry in [i, i + 2^k)

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

// precompute all log values
void precompute_log(int m) {
    log_2.assign(m + 1, -1);
    FOR(i, 1, m) log_2[i] = log_2[i / 2] + 1;
}

// st[0][i] = i, a run of one entry
// st[k][i] = min of its two halves, [i, i + 2^(k-1)) and [i + 2^(k-1), i + 2^k)
void precompute_sparse_table(int m) {
    st.assign(log_2[m] + 1, {});
    st[0].resize(m);
    iota(all(st[0]), 0);
    FOR(k, 1, log_2[m]) {
        st[k].resize(m - (1 << k) + 1);
        for (int i = 0; i + (1 << k) <= m; i++) {
            st[k][i] = min_by_h(st[k-1][i], st[k-1][i + (1 << (k-1))]);
        }
    }
}

void precompute_lca(int root) {
    // get euler tour & indices of first occurrences
    first_visit.assign(n, -1);
    height.assign(n, 0);
    euler_tour.clear();
    euler_tour.reserve(2 * n);
    flatten(root, -1, 0);

    precompute_sparse_table(sz(euler_tour));
}

// the shallowest entry in euler_tour[first_visit[v] .. first_visit[u]]
int lca(int v, int u) {
    int l = first_visit[v];
    int r = first_visit[u];
    if (l > r) swap(l, r);
    // two runs of 2^k entries that cover [l, r], they may overlap
    int k = log_2[r - l + 1];
    return euler_tour[min_by_h(st[k][l], st[k][r - (1 << k) + 1])];
}

void preprocess() {
    // log values up to the longest euler tour, 2n - 1
    precompute_log(2 * MAX_N);
}

void solve() {
    // read tree
    int q; cin >> n >> q;
    adj.assign(n, {});
    REP(i, n-1) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    // precompute lca, rooted at vertex 1
    precompute_lca(0);

    // answer queries
    REP(i, q) {
        int u, v; cin >> u >> v;
        u--; v--;
        cout << lca(u, v) + 1 << '\n';
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
