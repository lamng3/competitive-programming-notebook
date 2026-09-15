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
    int n; cin >> n;
    vi x(n);
    int mxx = 0;
    REP(i, n) {
        cin >> x[i];
        mxx = max(mxx, x[i]);
    }
    
    // construct mobius function
    vi mu(mxx+5);
    mu[1] = -1;
    FOR(i, 1, mxx) {
        if (mu[i]) {
            mu[i] = -mu[i];
            for (int j = 2*i; j <= mxx; j+=i) mu[j] += mu[i];
        }
    }

    // count frequencies of divisors
    vi f(mxx+5, 0);
    REP(i, n) f[x[i]]++;

    vi cnt(mxx+5, 0);
    FOR(g, 1, mxx) {
        if (mu[g] == 0) continue;
        for (int j = g; j <= mxx; j+=g) cnt[g] += f[j];
    }

    ll ans = 0;
    FOR(g, 1, mxx) {
        if (mu[g] == 0 || cnt[g] < 2) continue;
        ans += (ll)mu[g] * ((ll)cnt[g] * (cnt[g]-1) / 2);
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