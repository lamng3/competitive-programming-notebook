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

// LCA with Farach-Colton and Bender: O(n) build, O(1) per query
// notes: notebook/trees/farach-colton_bender/README.md

const int MAX_N = 5e5;
const int MAX_M = 2 * MAX_N; // euler tour has 2n - 1 entries

vi Adj[MAX_N+5];

struct Query { int u, v, id; };
vector<Query> queries;

// ---------- log table ----------

vi lg2; // lg2[x] = floor(log2(x)), lg2[0] = -1

void buildLog(int m) {
    lg2.assign(m+1, -1);
    FOR(i, 1, m) lg2[i] = lg2[i/2] + 1;
}

void preprocess() {
    buildLog(MAX_M);
}

// ---------- euler tour ----------

vi euler;      // vertices in visit order, u written on entry and after each child
vi nodeStart;  // first index of u in euler, the only position a query needs
vi nodeHeight; // depth of u, root = 0

void eulerTour(int u, int p, int h) {
    nodeStart[u] = sz(euler);
    euler.pb(u);
    nodeHeight[u] = h;
    for (int v : Adj[u]) {
        if (v == p) continue;
        eulerTour(v, u, h+1);
        euler.pb(u); // back up through u
    }
}

void buildEulerTour(int n, int root) {
    nodeStart.assign(n, -1);
    nodeHeight.assign(n, 0);
    euler.clear();
    euler.reserve(2*n);
    eulerTour(root, -1, 0);
}

// ---------- +-1 RMQ ----------
// argmin(l, r) = position of the min of arr[l..r], neighbours of arr differ by exactly 1

vi arr;
int block_size, block_cnt;

int minIdx(int i, int j) {
    return arr[i] < arr[j] ? i : j;
}

vii st; // st[b][k] = position of the min of blocks [b, b + 2^k)

void buildBlockSparseTable() {
    int m = sz(arr);
    st.assign(block_cnt, vi(lg2[block_cnt] + 1));
    // min of each block
    REP(i, m) {
        int b = i / block_size;
        if (i % block_size == 0) st[b][0] = i;
        else st[b][0] = minIdx(st[b][0], i);
    }
    // double the span
    FOR(k, 1, lg2[block_cnt]) {
        REP(b, block_cnt) {
            int nb = b + (1 << (k-1));
            if (nb < block_cnt) st[b][k] = minIdx(st[b][k-1], st[nb][k-1]);
            else st[b][k] = st[b][k-1];
        }
    }
}

// min of blocks [bl, br], two overlapping runs of 2^k blocks
int querySparseTable(int bl, int br) {
    int k = lg2[br - bl + 1];
    return minIdx(st[bl][k], st[br - (1 << k) + 1][k]);
}

vi blockMask; // bit j-1 = 1 if the block steps up from offset j-1 to j

void buildBlockMasks() {
    int m = sz(arr);
    blockMask.assign(block_cnt, 0);
    FOR(i, 1, m-1) {
        int j = i % block_size;
        if (j > 0 && arr[i] > arr[i-1]) blockMask[i / block_size] |= 1 << (j-1);
    }
}

vector<vii> maskTable; // maskTable[mask][l][r] = offset of the min of [l, r] in a block of that shape

void buildMaskTables() {
    int masks = 1 << (block_size - 1);
    maskTable.assign(masks, vii(block_size, vi(block_size)));
    REP(mask, masks) {
        REP(l, block_size) {
            // walk right from l, keep where the running height is lowest
            int h = 0, best = 0, pos = l;
            maskTable[mask][l][l] = l;
            FOR(r, l+1, block_size-1) {
                h += (mask >> (r-1) & 1) ? 1 : -1;
                if (h < best) best = h, pos = r;
                maskTable[mask][l][r] = pos;
            }
        }
    }
}

// min over offsets [l, r] of block b
int queryInBlock(int b, int l, int r) {
    return b * block_size + maskTable[blockMask[b]][l][r];
}

void buildRMQ() {
    int m = sz(arr);
    block_size = max(1, lg2[m] / 2);
    block_cnt = (m + block_size - 1) / block_size;
    buildBlockSparseTable();
    buildBlockMasks();
    buildMaskTables();
}

int argmin(int l, int r) {
    if (l > r) swap(l, r);
    int bl = l / block_size, br = r / block_size;
    // both ends in one block
    if (bl == br) return queryInBlock(bl, l % block_size, r % block_size);
    // suffix of l's block, prefix of r's block
    int ans = minIdx(queryInBlock(bl, l % block_size, block_size-1),
                     queryInBlock(br, 0, r % block_size));
    // whole blocks in between
    if (bl+1 <= br-1) ans = minIdx(ans, querySparseTable(bl+1, br-1));
    return ans;
}

// ---------- lca ----------

void buildLCA(int n, int root) {
    buildEulerTour(n, root);
    // heights along the tour
    arr.resize(sz(euler));
    REP(i, sz(euler)) arr[i] = nodeHeight[euler[i]];
    buildRMQ();
}

// shallowest vertex between the first visits of u and v
int lca(int u, int v) {
    return euler[argmin(nodeStart[u], nodeStart[v])];
}

void solve() {
    // read input
    int n, q; cin >> n >> q;
    REP(i, n) Adj[i].clear();
    REP(i, n-1) {
        int a, b; cin >> a >> b;
        a--; b--;
        Adj[a].pb(b);
        Adj[b].pb(a);
    }
    queries.clear();
    REP(i, q) {
        int u, v; cin >> u >> v;
        u--; v--;
        queries.pb({u, v, i});
    }

    // build lca, rooted at vertex 1
    buildLCA(n, 0);

    // answer queries
    for (auto& [u, v, id] : queries) cout << lca(u, v) + 1 << '\n';
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
