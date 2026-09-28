#include <bits/stdc++.h>
using namespace std;

using ll = long long;
// using i64 = int64_t;
// using u64 = uint64_t;
// using i128 = __int128;
// using u128 = unsigned __int128;

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
const int MOD = 1e9+7;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void preprocess() {
    
}

/* 
    if remove i, we only subtract i+1 onwards
    a[1]..a[i-1] is already good
    we will shift numbers to the left
    a[i+1]..a[n]
    only shift until difference = k
    max(0, a[i+1] - a[i-1] - k)
    calculate the jumps needed and add the prefix
    max(0, a[i+2] - a[i-1] - k)
*/
void solve() {
    int n, k; cin >> n >> k;
    vector<ll> a(n);
    REP(i, n) cin >> a[i];
    
    /*
        domino effect
        if a[i+1] shifted, then a[i+2] ... a[n] shifted
        a[i+1] = a[i-1] + k
        a[i+2] = a[i-1] + 2k
        a[i+3] = a[i-1] + 3k
        ...
        a[i+x] = a[i-1] + xk
        then need[i+x] = a[i+x] - a[i-1] - x*k
        need[i+1] + .. + need[i+x]
        = a[i+1] + .. + a[i+x] - a[i-1] * x - k * x * (x+1) / 2
    */
    vector<ll> pref(n, 0);
    REP(i, n) pref[i] = (i > 0 ? pref[i-1] : 0) + a[i];

    vector<ll> ans(n);
    REP(i, n) {
        if (i == 0 || i == n-1 || a[i-1] + k >= a[i+1]) {
            ans[i] = 0;
            continue;
        }
        // a[i-1] + k < a[i+1]
        // find largest x such that need[i+x] > 0 and need[i+x+1] <= 0
        int left = i, right = n;
        while (right - left > 0) {
            int mid = left + (right - left) / 2;
            if (a[mid] - a[i-1] - (ll)(mid-i) * k <= 0) right = mid;
            else left = mid+1; // last success
        }
        left--;
        if (left < i) {
            ans[i] = 0;
            continue;
        }
        int x = left - i;
        ll term1 = pref[left] - pref[i];
        ll term2 = a[i-1] * x;
        ll term3 = (ll)k * x * (x+1) / 2;
        ans[i] = term1 - term2 - term3;
    }

    REP(i, sz(ans)) cout << ans[i] << (i == sz(ans)-1 ? '\n' : ' ');
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