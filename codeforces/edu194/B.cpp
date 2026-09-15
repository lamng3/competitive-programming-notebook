#include <bits/stdc++.h>
using namespace std;

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
const int MOD = 998244353; // 1e9+7

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void preprocess() {
    
}

void solve() {
    ll x, y, k; cin >> x >> y >> k;
    /*
        y = px + r
        y+i = p(x+i) + (r + i - ip)
        let a = x+i and d = y-x
        then y+i mod x+i becomes: (a+d) mod a = d mod a
        if a > d then d%a = d
        else a <= d then d%a, at most
        a > d when x+i > y-x, meaning y < 2x+i
        so i > y-2x
    */
    ll d = y-x;
    ll left = x, right = x+k-1;
    ll ans = 0;
    for (ll a = left; a <= min(right, d); a++) ans += d % a;
    ll mid = max(left, d+1); // a > d
    if (mid <= right) ans += d * (right - mid + 1);
    cout << ans << '\n';
}

int main() {
    // freopen("name.in", "r", stdin);
    // freopen("name.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    preprocess();
    int tt = 1;
    cin >> tt;
    while (tt--) solve();
    return 0;
}