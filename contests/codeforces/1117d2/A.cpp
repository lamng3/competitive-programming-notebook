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
    vector<string> w(n);
    vi f(26, 0);
    REP(i,n) {
        cin >> w[i];
        f[w[i][0]-'a']++;
    }
    vector<string> a(m);
    REP(i,m) cin >> a[i];
    REP(i,m) {
        for (auto& c : a[i]) {
            if (f[c-'A'] > 0) continue;
            cout << "NO" << '\n';
            return;            
        }
    }
    cout << "YES" << '\n';
    return;
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
