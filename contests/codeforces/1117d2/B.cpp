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
    vi b(m);
    REP(i,m) cin >> b[i];
    /* 
        a[i] .. b[j]
        1) a[i] can reduce to a[i+1]-1 then jump to a[i+1]
        2) b[j] can reduce to b[j+1]-1 then jump to b[j+1]
        3) min(a[i] - a[i+1] + 1, b[j] - b[j+1] + 1)
        4) until i reaches n-1 or j reaches m-1
    */
    int sa = 0, sb = 0;
    REP(i,n) sa += i < n-1 ? (a[i] - a[i+1] + 1) : a[i];
    REP(i,m) sb += i < m-1 ? (b[i] - b[i+1] + 1) : b[i];
    cout << (sa >= sb ? 1 : 2) << '\n';
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