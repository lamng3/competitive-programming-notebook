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

/*
    profit of path a -> ... -> b telescopes: sum (v[i] - v[j]) = v[a] - v[b]
    so only endpoints matter, count ordered pairs (a, b) with v[a] - v[b] = k

    n nodes, n edges, connected => exactly one cycle
    remove cycle edges -> each cycle node roots a tree, comp[u] = root
        comp[a] == comp[b]: 1 simple path
        comp[a] != comp[b]: 2 simple paths (either way around cycle)
                            (cycle of length 2 = multi-edge, same city sequence -> 1)
    ans = mul * (all pairs) - (mul - 1) * (pairs in same comp) + (k == 0 ? n : 0)
*/
void solve() {
    int n; ll k; cin >> n >> k;
    vector<ll> v(n);
    REP(i, n) cin >> v[i];
    vii G(n);
    vi deg(n, 0);
    REP(i, n) {
        int a, b; cin >> a >> b; a--; b--;
        G[a].pb(b); G[b].pb(a);
        deg[a]++; deg[b]++;
    }

    // peel leaves, what remains is the cycle
    vector<bool> onCycle(n, true);
    queue<int> q;
    REP(u, n) if (deg[u] == 1) q.push(u);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        onCycle[u] = false;
        for (int v : G[u]) if (onCycle[v] && --deg[v] == 1) q.push(v);
    }
    int cycleLen = 0;
    REP(u, n) cycleLen += onCycle[u];

    // label tree hanging off each cycle node
    vi comp(n, -1);
    REP(r, n) {
        if (!onCycle[r]) continue;
        comp[r] = r;
        vi st = {r};
        while (!st.empty()) {
            int u = st.back(); st.pop_back();
            for (int v : G[u]) {
                if (onCycle[v] || comp[v] != -1) continue;
                comp[v] = r;
                st.pb(v);
            }
        }
    }

    // ordered pairs a != b with v[a] - v[b] = k
    auto countPairs = [&](const vi& nodes) -> ll {
        map<ll, ll> cnt;
        for (int u : nodes) cnt[v[u]]++;
        ll res = 0;
        for (auto& [x, c] : cnt) {
            if (k == 0) res += c * (c - 1);
            else if (cnt.count(x - k)) res += c * cnt[x - k];
        }
        return res;
    };

    vi everyone(n);
    iota(all(everyone), 0);
    vii groups(n);
    REP(u, n) groups[comp[u]].pb(u);

    ll mul = (cycleLen >= 3 ? 2 : 1);
    ll total = countPairs(everyone);
    ll same = 0;
    REP(r, n) if (!groups[r].empty()) same += countPairs(groups[r]);

    ll ans = mul * total - (mul - 1) * same + (k == 0 ? n : 0);
    cout << ans << "\n";
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
