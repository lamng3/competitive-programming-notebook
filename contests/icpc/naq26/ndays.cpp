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
const int MOD = 998244353;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void preprocess() {
    
}

/*
1 + (1+2) + (1+2+3) + .. + (1+2+..+n)
1 appears n times
2 appear n-1 times
3 appears n-2 times
...
n appears 1 time

x appears n+1-x times
f(x) = x * (n+1-x) = (n+1) * x - x^2
sum f(x) with x = 1..n:
    (n+1) * (n+1) * n / 2 - (1^2 + 2^2 + .. + n^2)
    = (n+1) ^ 2 * n / 2 - n * (n+1) * (2n+1) / 6
    = n * (n+1) * 1/6 * (3n+3 - 2n - 1)
    = n * (n+1) * 1/6 * (n+2)
*/
ll modpow(ll a, ll b) {
    ll r = 1;
    while (b) {
        if (b&1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return r;
}

ll modinv(ll a) {
    return modpow(a, MOD-2);
}

void solve() {
    ll n; cin >> n;
    n %= MOD;
    ll ans = 1;
    ans = (ans * n) % MOD;
    ans = (ans * ((n+1) % MOD)) % MOD;
    ans = (ans * ((n+2) % MOD)) % MOD;
    ans = (ans * modinv(6)) % MOD;
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
