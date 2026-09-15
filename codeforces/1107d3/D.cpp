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
    /*
        a[i] can +1 any number of times
        a[i] can -1 only when a[i-1] + 1
        that means a[i] - X then a[i-1] + X
        process from end
    */
    int n; cin >> n;
    vector<ll> a(n);
    REP(i,n) cin >> a[i];
    vector<ll> b(n);
    REP(i,n) cin >> b[i];
    ll add = 0;
    RFOR(i,n) {
        if (a[i] + add <= b[i]) {
            add = 0;
            continue;
        }
        add = a[i] + add - b[i];
    }
    cout << (add == 0 ? "YES" : "NO") << '\n';
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