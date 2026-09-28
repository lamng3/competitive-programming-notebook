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
const int MOD = 1e9+7;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void preprocess() {
    
}

void solve() {
    int n; cin >> n;
    vi a(n);
    REP(i, n) cin >> a[i];
    // for all i
    // once a[i] = 1, it will always stay as 1
    // a[i] = 2 will flip between 0 and 2
    int odd = 0, even1 = 0, even2 = 0;
    REP(i, n) {
        if (a[i] % 2) odd += 1;
        else {
            int need = a[i] / 2;
            if (need % 2) even1 += 1;
            else even2 += 1;
        }
    }
    int ans = max({odd, even1, even2});
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