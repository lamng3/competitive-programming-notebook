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
    ll x, y; cin >> x >> y;
    /*
        if ith bit of both x and y turned on, we want to move to i+1 bit of 1
        moving 1 bit to the other corresponds to -2^i and + 2^i
        x ^ y <= x + y as xor throws away bits
    */
    ll S = x+y, cur = 0;
    RFOR(i, 31) {
        // check if ith bit is turned on and can be move to x
        // we want cur to be as large as possible to minimize x - cur number of operations
        if (S & (1LL << i) && cur + (1LL << i) <= x) cur += 1LL << i;
    }
    cout << S << ' ' << x - cur << '\n';
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