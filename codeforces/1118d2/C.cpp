#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<long long>;
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

/*
for target size L
j = lower_bound(all(a),L)
every a[i] in [j..n-1] we can cut
each a[i] can contributes floor(a[i]/L) pieces with floor(a[i]/L) cuts
if a[i] % L == 0: we only need floor(a[i]/L)-1 cuts;
*/
void solve() {
    int n, m; 
    cin >> n >> m;

    vi f(m + 1, 0);
    vi a(n);
    REP(i, n) {
        cin >> a[i];
        f[a[i]]++;
    }

    // cge[x] = total number of carrots >= x
    vll cge(m + 2, 0);
    FORD(i, m, 1) cge[i] = cge[i + 1] + f[i];

    vll ans(m + 1, 0);
    vll pref(m + 1, 0);

    FOR(L, 1, m) {
        int mxc = m / L;
        FOR(j, 1, mxc) pref[j] = pref[j - 1] + cge[j * L];

        for (int k = 1, p = 2; ; k++, p <<= 1) {
            int take = min(mxc, p - 1);
            ll extra = (1LL * p * L <= m ? f[p * L] : 0LL);

            ans[k] = max(ans[k], pref[take] + extra);
            if (p - 1 >= mxc) break;
        }
    }

    FOR(k, 1, m) ans[k] = max(ans[k], ans[k - 1]);
    FOR(k, 1, m) cout << ans[k] << (k == m ? '\n' : ' ');
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