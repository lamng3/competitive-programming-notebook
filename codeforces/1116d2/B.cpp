#include <bits/stdc++.h>
using namespace std;

using ll = long long;
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
// const int MOD = 1e9+7;
const int MOD = 998244353;

void preprocess() {
    
}

void solve() {
    /* 
        n-1 dominos
        options: 001, 011, 100, 110, 
        at most 2 consecutive 0s or 1s
        and cannot 101 and 010

        dp[i][x] = #ways to replace s[0..i] with s[i] = x
        dp[i][x]
            if s[i-1] = x then s[i-2] = 1-x: dp[i][x] += dp[i-2][1-x]
            if s[i-1] = 1-x then s[i-2] = 1-x: dp[i][x] += dp[i-2][1-x]
        => dp[i][x] += dp[i-2][1-x] regardless s[i-1]
        therefore, s is alternating with step 2
            i, i+2, ...
            i+1, i+3, ...
    */
    int n; cin >> n;
    string s; cin >> s;
    string odd = "", even = "";
    REP(i,n) {
        if (i%2) odd += s[i];
        else even += s[i];
    }
    auto alternate = [&](string& a) {
        int ok1 = 1, ok2 = 1;
        REP(i,sz(a)) { // start with 0
            if ((i % 2 == 1 && a[i] == '0') || (i % 2 == 0 && a[i] == '1')) {
                ok1 = 0;
                break;
            }
        }
        REP(i,sz(a)) { // start with 1
            if ((i % 2 == 1 && a[i] == '1') || (i % 2 == 0 && a[i] == '0')) {
                ok2 = 0;
                break;
            }
        }
        return ok1 + ok2;
    };
    int ans = 0;
    ans += alternate(even) * alternate(odd);
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