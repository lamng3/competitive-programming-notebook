// https://codeforces.com/problemset/problem/342/E
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

const int MAX_N = 1e5;
const int MAX_M = 1e5;

// input
int n, m;

// adj matrix
vi Adj[MAX_N+5];

// euler
vi euler;
vi height;
vi first_visit;

// log base 2
vi lg2;

// decomposition
int block_size, block_cnt;
vii st;
vi block_mask;
vector<vii> blocks;
int B = 300;

// changed nodes
vi changed;
vi dist;

void preprocess() {
    
}

void precompute_log2() {
    // build lg2
    lg2.assign(2 * n + 1, 0);
    lg2[0] = -1;
    FOR(i, 1, 2 * n) lg2[i] = lg2[i/2] + 1;
}

void flatten(int u, int p, int h) {
    first_visit[u] = sz(euler);
    euler.pb(u);
    height[u] = h;
    for (int v : Adj[u]) {
        if (v == p) continue;
        flatten(v, u, h+1);
        euler.pb(u);
    }
}

int min_by_h(int i, int j) {
    return height[euler[i]] < height[euler[j]] ? i : j;
}

void precompute_sparse_table(int k) {
    st.assign(block_cnt, vi(lg2[block_cnt] + 1));

    // st[b][0] = min of block b
    REP(i, k) {
        int b = i / block_size, j = i % block_size;
        if (j == 0) st[b][0] = i;
        else st[b][0] = min_by_h(st[b][0], i);
    }

    // st[b][j] = min of blocks[b..b+2^(j-1)) and blocks[b+2^(j-1)..b+2^j)
    FOR(j, 1, lg2[block_cnt]) {
        REP(b, block_cnt) {
            if (b + (1 << j) > block_cnt) continue;
            st[b][j] = min_by_h(st[b][j-1], st[b + (1<<(j-1))][j-1]);
        }
    }
}

void precompute_block_mask(int k) {
    block_mask.assign(block_cnt, 0);
    REP(i, k) {
        int b = i / block_size, j = i % block_size;
        if (j > 0 && height[euler[i]] > height[euler[i-1]]) block_mask[b] |= (1 << (j-1));
    }
}

void precompute_blocks(int k) {
    int FULL = 1 << (block_size - 1);
    blocks.assign(FULL, {});
    REP(b, block_cnt) {
        int mask = block_mask[b];

        if (!blocks[mask].empty()) continue;
        blocks[mask].assign(block_size, vi(block_size));

        int offset = b * block_size;
        REP(l, block_size) {
            blocks[mask][l][l] = l;
            FOR(r, l+1, block_size-1) {
                blocks[mask][l][r] = blocks[mask][l][r-1];
                if (offset + r >= k) continue;
                blocks[mask][l][r] = min_by_h(offset + blocks[mask][l][r], offset + r) - offset;
            }
        }
    }
}

void precompute_lca() {
    // euler tour
    euler.clear();
    height.assign(n, -1);
    first_visit.assign(n, 0);
    flatten(0, -1, 0);

    // decomposition
    int k = sz(euler);
    block_size = max(1, lg2[k] / 2);
    block_cnt = (k + block_size - 1) / block_size;

    precompute_sparse_table(k);
    precompute_block_mask(k);
    precompute_blocks(k);
}

int lca_in_block(int b, int l, int r) {
    int offset = b * block_size;
    return blocks[block_mask[b]][l][r] + offset;
}

int lca_between_blocks(int bl, int br) {
    int k = lg2[br - bl + 1];
    return min_by_h(st[bl][k], st[br - (1<<k) + 1][k]);
}

int lca(int u, int v) {
    int l = first_visit[u];
    int r = first_visit[v];
    if (l > r) swap(l, r);
    int bl = l / block_size;
    int br = r / block_size;
    // in same block
    if (bl == br) return euler[lca_in_block(bl, l % block_size, r % block_size)];
    // suffix of l
    int suffix = lca_in_block(bl, l % block_size, block_size-1);
    // prefix of r
    int prefix = lca_in_block(br, 0, r % block_size);
    int ans = min_by_h(suffix, prefix);
    // blocks in between
    if (bl + 1 < br) ans = min_by_h(ans, lca_between_blocks(bl+1, br-1));
    return euler[ans];
}

void rebuild() {
    queue<int> q;
    for (int u : changed) {
        dist[u] = 0;
        q.push(u);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : Adj[u]) {
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    changed.clear();
}

void paint(int v) {
    changed.pb(v);
    if (sz(changed) >= B) rebuild();
}

int getDist(int u, int v) {
    return height[u] + height[v] - 2 * height[lca(u, v)];
}

void getMinDistRed(int v) {
    int res = dist[v];
    for (int u : changed) res = min(res, getDist(u, v));
    cout << res << '\n';
}

void solve() {
    // read input
    cin >> n >> m;
    REP(i, n) Adj[i].clear();
    REP(i, n-1) {
        int a, b; cin >> a >> b;
        a--; b--;
        Adj[a].pb(b);
        Adj[b].pb(a);
    }
    
    precompute_log2();
    precompute_lca();

    dist = height;

    REP(i, m) {
        int t, v; cin >> t >> v;
        v--;
        if (t == 1) paint(v);
        else getMinDistRed(v);
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
    while (tt--) solve();
    return 0;
}
