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

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;

int n;
vi a;

namespace Sub1 {
    bool istask() {
        return n <= 20;
    }
    void execute() {
        /*
            n-1 partition points
        */
        int ans = 0;
        REP(mask, 1<<(n-1)) {
            int last = 0;
            int run = a[0], ok = 1, cnt = 0;
            REP(i, n-1) {
                if (mask&(1<<i)) {
                    if (run < last || run <= 0) {
                        ok = 0;
                        break;
                    }
                    last = run;
                    run = 0;
                    cnt++;
                }
                run += a[i+1];
            }
            if (run < last || run <= 0) ok = 0;
            else last = run;
            if (ok) ans = max(ans, cnt+1);
        }
        cout << ans << '\n';
    }
}

namespace Sub2 {
    bool istask() {
        return n <= 700;
    }
    void execute() {
        vi pref(n, 0);
        REP(i, n) pref[i] = (i > 0 ? pref[i-1] : 0) + a[i];
        auto sum = [&](int L, int R) {
            return pref[R] - (L > 0 ? pref[L-1] : 0);
        };

        /*
            dp[i][j] = max # partitions of a[0..i] such that last segment is a[j..i]
        */
        vii dp(n, vi(n, -INF));
        REP(i, n) if (sum(0, i) > 0) dp[i][0] = 1;
        REP(i, n) {
            // ending at a[j..i]
            FOR(j, 1, i) {
                if (sum(j, i) <= 0) continue;
                REP(k, j) {
                    if (sum(k, j-1) <= sum(j, i) && dp[j-1][k] > 0) {
                        dp[i][j] = max(dp[i][j], dp[j-1][k] + 1);
                    }
                }
            }
        }
        int ans = 0;
        REP(j, n) ans = max(ans, dp[n-1][j]);
        cout << ans << '\n';
    }
}

namespace Sub3 {
    bool istask() {
        return n <= 2500;
    }
    void execute() {
        
    }
}

namespace Sub4 {
    bool istask() {
        int r = 0;
        REP(i, n) r += abs(a[i]);
        return r <= 1e4;
    }
    void execute() {
        
    }
}

namespace Full {
    void run() {
        
    }
}

void preprocess() {
    
}

void solve() {
    cin >> n;
    a.resize(n);
    REP(i, n) cin >> a[i];

    if (Sub1::istask()) { Sub1::execute(); return; }
    if (Sub2::istask()) { Sub2::execute(); return; }
    if (Sub3::istask()) { Sub3::execute(); return; }
    if (Sub4::istask()) { Sub4::execute(); return; }
    Full::run();
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