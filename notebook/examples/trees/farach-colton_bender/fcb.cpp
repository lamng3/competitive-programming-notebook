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

const int MAX_N = 5e5;
const int MAX_M = 2 * MAX_N; // euler tour length is 2n - 1

vi Adj[MAX_N+5];

struct Query { int u, v, id; };
vector<Query> queries;

/* ============================================================
    MODULE 0: log table
    ------------------------------------------------------------
    lg2[x] = floor(log2(x)), lg2[0] = -1
    lg2[x] = lg2[x/2] + 1
   ============================================================ */
vi lg2;

void buildLog(int m) {
    lg2.assign(m+1, -1);
    FOR(i, 1, m) lg2[i] = lg2[i/2] + 1;
}

void preprocess() {
    buildLog(MAX_M);
}

/* ============================================================
    MODULE 1: euler tour
    ------------------------------------------------------------
    input : Adj, root
    output: euler[]        vertices in visit order, size 2n - 1
            nodeStart[u]   first index of u in euler
            nodeHeight[u]  depth of u (root = 0)

    tour(u):
        write u
        for each child v:
            tour(v)
            write u again        <- comes back up through u

    => neighbouring heights in euler differ by exactly 1
    => lca(u, v) = shallowest vertex in euler[nodeStart[u] .. nodeStart[v]]
   ============================================================ */
vi euler, nodeStart, nodeHeight;

void eulerTour(int u, int p, int h) {
    nodeStart[u] = sz(euler);
    euler.pb(u);
    nodeHeight[u] = h;
    for (int v : Adj[u]) {
        if (v == p) continue;
        eulerTour(v, u, h+1);
        euler.pb(u);
    }
}

void buildEulerTour(int n, int root) {
    nodeStart.assign(n, -1);
    nodeHeight.assign(n, 0);
    euler.clear();
    euler.reserve(2*n);
    eulerTour(root, -1, 0);
}

/* ============================================================
    MODULE 2: +-1 RMQ (Farach-Colton and Bender)
    ------------------------------------------------------------
    input : arr[0..m) with |arr[i] - arr[i-1]| = 1
    query : argmin(l, r) = index of the min of arr[l..r], O(1)
    build : O(m)

    cut arr into blocks of size b = log2(m) / 2, then
        2a. block sparse table : sparse table over each block's min
        2b. block masks        : a block is b - 1 steps of +-1 -> a (b-1)-bit mask
        2c. mask tables        : for every mask, argmin of every [l, r] in a block
                                 (2^(b-1) <= sqrt(m) masks, b^2 entries each)

    argmin(l, r):
        same block       -> mask table
        different blocks -> min of
                              suffix of l's block       (mask table)
                              whole blocks in between   (sparse table)
                              prefix of r's block       (mask table)
   ============================================================ */
vi arr;
int block_size, block_cnt;

// index of the smaller of arr[i], arr[j]
int minIdx(int i, int j) {
    return arr[i] < arr[j] ? i : j;
}

/* ---------- 2a. block sparse table ----------
    st[b][0] = argmin of block b
    st[b][k] = minIdx(st[b][k-1], st[b + 2^(k-1)][k-1])   blocks [b, b + 2^k)
    query blocks [bl, br]: two overlapping ranges of 2^k blocks
*/
vii st;

void buildBlockSparseTable() {
    int m = sz(arr);
    st.assign(block_cnt, vi(lg2[block_cnt] + 1));
    REP(i, m) {
        int b = i / block_size;
        if (i % block_size == 0) st[b][0] = i;
        else st[b][0] = minIdx(st[b][0], i);
    }
    FOR(k, 1, lg2[block_cnt]) {
        REP(b, block_cnt) {
            int nb = b + (1 << (k-1));
            if (nb < block_cnt) st[b][k] = minIdx(st[b][k-1], st[nb][k-1]);
            else st[b][k] = st[b][k-1];
        }
    }
}

int querySparseTable(int bl, int br) {
    int k = lg2[br - bl + 1];
    return minIdx(st[bl][k], st[br - (1 << k) + 1][k]);
}

/* ---------- 2b. block masks (combinatorial bitmasking) ----------
    inside a block, position j (j >= 1) steps from j-1:
        bit j-1 = 1  if arr goes up   (arr[j] = arr[j-1] + 1)
        bit j-1 = 0  if arr goes down (arr[j] = arr[j-1] - 1)
    the mask alone fixes where the min of any [l, r] is,
    so blocks with the same mask share one table
    a short last block keeps 0s for its missing steps, never read by a query
*/
vi blockMask;

void buildBlockMasks() {
    int m = sz(arr);
    blockMask.assign(block_cnt, 0);
    FOR(i, 1, m-1) {
        int j = i % block_size;
        if (j > 0 && arr[i] > arr[i-1]) blockMask[i / block_size] |= 1 << (j-1);
    }
}

/* ---------- 2c. mask tables ----------
    for every mask, every l:
        walk r = l+1 .. b-1, h += (bit r-1 ? +1 : -1)
        maskTable[mask][l][r] = position of the lowest h so far
    depends only on the mask, not on arr
*/
vector<vii> maskTable;

void buildMaskTables() {
    int masks = 1 << (block_size - 1);
    maskTable.assign(masks, vii(block_size, vi(block_size)));
    REP(mask, masks) {
        REP(l, block_size) {
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

// argmin of arr over positions [l, r] of block b (l, r are offsets in the block)
int queryInBlock(int b, int l, int r) {
    return b * block_size + maskTable[blockMask[b]][l][r];
}

void buildRMQ() {
    int m = sz(arr);
    block_size = max(1, lg2[m] / 2);
    block_cnt = (m + block_size - 1) / block_size;
    buildBlockSparseTable(); // 2a
    buildBlockMasks();       // 2b
    buildMaskTables();       // 2c
}

int argmin(int l, int r) {
    if (l > r) swap(l, r);
    int bl = l / block_size, br = r / block_size;
    if (bl == br) return queryInBlock(bl, l % block_size, r % block_size);
    int ans = minIdx(queryInBlock(bl, l % block_size, block_size-1),
                     queryInBlock(br, 0, r % block_size));
    if (bl+1 <= br-1) ans = minIdx(ans, querySparseTable(bl+1, br-1));
    return ans;
}

/* ============================================================
    MODULE 3: LCA = euler tour + +-1 RMQ
    ------------------------------------------------------------
    arr[i] = nodeHeight[euler[i]]
    lca(u, v) = euler[argmin(nodeStart[u], nodeStart[v])]
   ============================================================ */
void buildLCA(int n, int root) {
    buildEulerTour(n, root);
    arr.resize(sz(euler));
    REP(i, sz(euler)) arr[i] = nodeHeight[euler[i]];
    buildRMQ();
}

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

    // build lca, root = vertex 1
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
