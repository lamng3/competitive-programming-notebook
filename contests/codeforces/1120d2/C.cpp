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
// const int MOD = 998244353; // 1e9+7
const int MOD = 1e9+7;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void preprocess() {
    
}

/*
    f(B,k) = a[k]
    difference array
    set -k for [a[k] * k .. (a[k]+1) * k - 1]
*/
void solve() {
    int n; cin >> n;
    vi a(n+1);
    FOR(i,1,n) cin >> a[i];
 
    vi diff(n+5, 0);
    FOR(k,1,n) {
        int L = min((ll)a[k] * k, (ll)n), R = min(((ll)a[k]+1) * k - 1, (ll)n);
        // cout << k << ' ' << L << ' ' << R << '\n';
        // remove [L..R]
        diff[L] -= 1;
        diff[R+1] += 1;
    }
    FOR(i,1,n) diff[i] += diff[i-1];
    
    vi B;
    REP(x,n) if (diff[x] == 0) B.pb(x);
 
    int m = sz(B);
    cout << m << '\n';
    if (m == 0) { cout << '\n'; return; }
    REP(i,m) cout << B[i] << (i == m-1 ? '\n' : ' ');
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
