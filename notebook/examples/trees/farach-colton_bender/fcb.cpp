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
const int MAX_M = 2 * MAX_N; // the euler tour has 2n - 1 entries
vi Adj[MAX_N+5];

struct Query { int u, v, id; };
vector<Query> queries;

vi lg2;

void preprocess() {
    // precompute log values up to the euler tour length, not just n
    lg2.assign(MAX_M + 1, -1);
    FOR(i, 1, MAX_M) lg2[i] = lg2[i/2] + 1;
}

// euler tour: write u on entry and again after each child returns,
// so neighbouring heights differ by exactly 1 (the +-1 property FCB needs)
vi nodeStart; // first position of u in the tour
vi nodeHeight;
vi euler;
void tour(int u, int p, int h) {
    nodeStart[u] = sz(euler);
    euler.pb(u);
    nodeHeight[u] = h;
    for (int v : Adj[u]) {
        if (v == p) continue;
        tour(v, u, h+1);
        euler.pb(u);
    }
}

// of two tour positions, the one whose vertex is higher up (smaller height)
int minByH(int i, int j) {
    return nodeHeight[euler[i]] < nodeHeight[euler[j]] ? i : j;
}

int block_size, block_cnt;
vii st;          // st[b][k]: tour position of the min over blocks [b, b + 2^k)
vi blockMask;    // bit j-1 set when the tour goes down from j-1 to j inside the block
vector<vii> inBlock; // inBlock[mask][l][r]: offset of the min of [l, r] in such a block

// lowest common ancestor of a and b
int lca(int a, int b) {
    int l = nodeStart[a], r = nodeStart[b];
    if (l > r) swap(l, r);
    int bl = l / block_size, br = r / block_size;
    auto inside = [&](int blk, int x, int y) {
        return blk * block_size + inBlock[blockMask[blk]][x][y];
    };
    if (bl == br) return euler[inside(bl, l % block_size, r % block_size)];
    // suffix of the left block, prefix of the right block
    int ans = minByH(inside(bl, l % block_size, block_size - 1), inside(br, 0, r % block_size));
    // whole blocks strictly between them: two overlapping sparse table ranges
    if (bl + 1 < br) {
        int k = lg2[br - bl - 1];
        ans = minByH(ans, minByH(st[bl+1][k], st[br - (1 << k)][k]));
    }
    return euler[ans];
}

void solve() {
    // read input
    int n, q; cin >> n >> q;
    REP(i, n) Adj[i].clear();
    REP(i, n-1) {
        int a, b; cin >> a >> b;
        a--; b--;
        Adj[a].pb(b); // edges are undirected: store both ways
        Adj[b].pb(a);
    }
    queries.clear();
    REP(i, q) {
        int u, v; cin >> u >> v;
        u--; v--;
        queries.pb({u, v, i});
    }

    // run euler tour
    nodeStart.assign(n, -1);
    nodeHeight.assign(n, 0);
    euler.clear();
    euler.reserve(2 * n);
    tour(0, -1, 0);

    // compute block size
    int m = sz(euler);
    block_size = max(1, lg2[m]/2);
    block_cnt = (m + block_size - 1) / block_size;

    // build sparse table: level 0 holds each block's min, level k doubles the span
    st.assign(block_cnt, vi(lg2[block_cnt] + 1));
    REP(i, m) {
        int b = i / block_size;
        if (i % block_size == 0 || minByH(i, st[b][0]) == i) st[b][0] = i;
    }
    FOR(k, 1, lg2[block_cnt]) {
        REP(b, block_cnt) {
            int nb = b + (1 << (k-1));
            st[b][k] = nb < block_cnt ? minByH(st[b][k-1], st[nb][k-1]) : st[b][k-1];
        }
    }

    // compute block masks: a block's shape is its block_size - 1 steps of +-1
    blockMask.assign(block_cnt, 0);
    FOR(i, 1, m-1) {
        int j = i % block_size;
        if (j > 0 && nodeHeight[euler[i]] > nodeHeight[euler[i-1]])
            blockMask[i / block_size] |= 1 << (j-1);
    }

    // in-block tables, one per mask that occurs, built from the mask alone:
    // walk the steps from l and keep where the running height is lowest.
    // A short last block reads its missing steps as 0 (going up), which is
    // safe since queries never reach past the end of the tour.
    inBlock.assign(1 << (block_size - 1), {});
    REP(b, block_cnt) {
        int mask = blockMask[b];
        if (!inBlock[mask].empty()) continue;
        inBlock[mask].assign(block_size, vi(block_size));
        REP(l, block_size) {
            int h = 0, best = 0, pos = l;
            inBlock[mask][l][l] = l;
            FOR(r, l+1, block_size-1) {
                h += (mask >> (r-1) & 1) ? 1 : -1;
                if (h < best) best = h, pos = r;
                inBlock[mask][l][r] = pos;
            }
        }
    }

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
