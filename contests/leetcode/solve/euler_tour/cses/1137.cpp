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

class Solution {
// LeetCode method function
// void solve() {}
public:

};

#if !defined(CPTEST) && (defined(LOCAL) || defined(ONLINE_JUDGE))
void preprocess() {
    
}

struct BIT {
    int n;
    vector<ll> a, bit;

    BIT(const vi& arr) {
        n = (int)arr.size();
        a.resize(n);
        REP(i, n) a[i] = (ll)arr[i];
        bit.assign(n+1, 0);
        for (int i = 1; i <= n; i++) add(i, a[i-1]);
    }

    void update(int i, ll u) {
        ll diff = u - a[i-1];
        a[i-1] = u;
        add(i, diff);
    }

    void add(int i, ll u) {
        for (; i <= n; i += i & -i) bit[i] += u;
    }

    ll sum(int i) {
        ll res = 0;
        for (; i > 0; i -= i & -i) res += bit[i];
        return res;
    }

    ll sum(int L, int R) {
        if (L > R) return 0;
        return sum(R) - sum(L-1);
    }
};

vi S, E, sz;
vi euler;
int timer;
void flatten(int u, int p, const vii& g, const vi& v) {
    S[u] = timer++;
    euler.pb(v[u]);
    for (int x : g[u]) {
        if (x != p) {
            flatten(x, u, g, v);
        }
    }
    E[u] = timer;
    sz[S[u]] = E[u] - S[u];
}

// cout << Solution().solve() << '\n';
void solve() {
    int n, q; cin >> n >> q;
    
    vi v(n);
    REP(i, n) cin >> v[i];

    vii g(n, vi());
    REP(i, n-1) {
        int a, b; cin >> a >> b;
        --a; --b;
        g[a].pb(b);
        g[b].pb(a);
    }

    S.resize(n);
    E.resize(n);
    sz.resize(n);
    euler.reserve(n);
    timer = 0;

    // flatten values
    flatten(0, -1, g, v);

    // dbg(S);
    // dbg(E);
    // dbg(sz);
    // dbg(euler);

    BIT bit(euler);

    REP(i, q) {
        int T; cin >> T;
        if (T == 1) {
            int s, x; cin >> s >> x;
            --s;
            bit.update(S[s]+1, x);
        }
        else if (T == 2) {
            int s; cin >> s;
            --s;
            ll ans = bit.sum(S[s]+1, E[s]);
            cout << ans << '\n';
        }
    }
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