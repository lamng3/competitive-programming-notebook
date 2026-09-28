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

void preprocess() {
    
}

void solve() {
    int n, c; cin >> n >> c;
    vi a(n);
    REP(i, n) cin >> a[i];

    vi pref(n, 0);
    REP(i, n) pref[i] = (i > 0 ? pref[i-1] : 0) + (a[i] == c);

    map<int,vi> pos;
    REP(i, n) if (a[i] != c) pos[a[i]].pb(i);

    int tot = pref[n-1], ans = tot;

    auto kadane = [&](const vi& add) {
        int best = 0, x = 0;
        REP(i, sz(add)) {
            x = max(1, x + add[i]);
            best = max(best, x);
        }
        return best;
    };

    for (auto& [x, v] : pos) {
        vi add(sz(v), 1);
        // include (v[i],v[i+1]] with (-oo,v[0]] = 1
        REP(i, sz(v)-1) add[i+1] = 1 - (pref[v[i+1]] - pref[v[i]]);

        int gain = kadane(add);
        ans = max(ans, tot + gain);
    }

    cout << ans << '\n';
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