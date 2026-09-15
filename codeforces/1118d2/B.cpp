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
    int n, m; cin >> n >> m;
    vi a(n);
    REP(i,n) cin >> a[i];

    map<int,int> f;
    REP(i,n) f[a[i]]++;

    sort(all(a));
    a.erase(unique(all(a)), a.end());

    int na = sz(a);

    vi suffmx(na,0);
    RFOR(i,na) suffmx[i] = max((i < na-1 ? suffmx[i+1] : 0), f[a[i]]);

    vi suffsum(na,0);
    RFOR(i,na) suffsum[i] = (i < na-1 ? suffsum[i+1] : 0) + f[a[i]];

    int ans = 0;
    REP(i,na) {
        // cut a[j] to a[i] and (a[j] - a[i])
        int nxt = i < na-1 ? suffmx[i+1] : 0;
        ans = max(ans, f[a[i]] + nxt);

        // if a[j] > a[i]
        int doub = f.count(a[i]*2) ? f[a[i]*2] : 0;
        ans = max(ans, suffsum[i] + doub);

        // target size not in a
        if (a[i] % 2 == 0) {
            int half = a[i]/2;
            int j = upper_bound(all(a), half) - a.begin();
            int x = (j < na ? suffsum[j] : 0);
            ans = max(ans, x + f[a[i]]);
        }
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
    cin >> tt;
    while (tt--) solve();
    return 0;
}