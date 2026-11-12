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
    LCA with Farach-Colton and Bender: O(n) build, O(1) per query
    follows https://cp-algorithms.com/graph/lca_farachcoltonbender.html
    why it works: notebook/trees/farach-colton_bender/README.md
*/

const int MAX_N = 5e5;

int n;
vii adj;

int block_size, block_cnt;
vi first_visit;
vi euler_tour;
vi height;
vi log_2;
vii st;
vector<vii> blocks;
vi block_mask;

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
    FOR(i, 1, m)
        log_2[i] = log_2[i / 2] + 1;
}

// precompute minimum of each block and build sparse table
void precompute_sparse_table(int m) {
    st.assign(block_cnt, vi(log_2[block_cnt] + 1));
    for (int i = 0, j = 0, b = 0; i < m; i++, j++) {
        if (j == block_size)
            j = 0, b++;
        if (j == 0 || min_by_h(i, st[b][0]) == i)
            st[b][0] = i;
    }
    FOR(l, 1, log_2[block_cnt]) {
        REP(i, block_cnt) {
            int ni = i + (1 << (l - 1));
            if (ni >= block_cnt)
                st[i][l] = st[i][l-1];
            else
                st[i][l] = min_by_h(st[i][l-1], st[ni][l-1]);
        }
    }
}

// precompute mask for each block
void precompute_block_mask(int m) {
    block_mask.assign(block_cnt, 0);
    for (int i = 0, j = 0, b = 0; i < m; i++, j++) {
        if (j == block_size)
            j = 0, b++;
        if (j > 0 && min_by_h(i - 1, i) == i - 1)
            block_mask[b] += 1 << (j - 1);
    }
}

// precompute RMQ for each unique block
void precompute_blocks(int m) {
    int FULL = 1 << (block_size - 1); // number of masks
    blocks.assign(FULL, {});
    REP(b, block_cnt) {
        int mask = block_mask[b];
        if (!blocks[mask].empty())
            continue;
        blocks[mask].assign(block_size, vi(block_size));
        REP(l, block_size) {
            blocks[mask][l][l] = l;
            FOR(r, l + 1, block_size - 1) {
                blocks[mask][l][r] = blocks[mask][l][r - 1];
                if (b * block_size + r < m)
                    blocks[mask][l][r] = min_by_h(b * block_size + blocks[mask][l][r],
                            b * block_size + r) - b * block_size;
            }
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

    int m = sz(euler_tour);
    block_size = max(1, log_2[m] / 2);
    block_cnt = (m + block_size - 1) / block_size;

    precompute_sparse_table(m);
    precompute_block_mask(m);
    precompute_blocks(m);
}

int lca_in_block(int b, int l, int r) {
    return blocks[block_mask[b]][l][r] + b * block_size;
}

int lca(int v, int u) {
    int l = first_visit[v];
    int r = first_visit[u];
    if (l > r)
        swap(l, r);
    int bl = l / block_size;
    int br = r / block_size;
    // both ends in one block
    if (bl == br)
        return euler_tour[lca_in_block(bl, l % block_size, r % block_size)];
    // suffix of l's block, prefix of r's block
    int suffix = lca_in_block(bl, l % block_size, block_size - 1);
    int prefix = lca_in_block(br, 0, r % block_size);
    int ans = min_by_h(suffix, prefix);
    // whole blocks in between
    if (bl + 1 < br) {
        int k = log_2[br - bl - 1];
        int mid_left = st[bl + 1][k];           // blocks [bl+1, bl+1 + 2^k)
        int mid_right = st[br - (1 << k)][k];   // blocks [br - 2^k, br)
        ans = min_by_h(ans, min_by_h(mid_left, mid_right));
    }
    return euler_tour[ans];
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
