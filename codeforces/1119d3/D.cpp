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

/*
    wlog x <= y <= z
    x + y + z >= 2z
    then x + y >= z
*/
void solve() {
    int n; cin >> n;
    vi a(n);
    REP(i, n) cin >> a[i];

    map<int,int> f;
    REP(i, n) f[a[i]]++;

    if (f[0] == 0) {
        string s;
        REP(i, n) s += (char)('A' + i%3);
        cout << "YES" << '\n';
        cout << s << '\n';
        return;
    }

    if (f[0] == 1) {
        cout << "NO" << '\n';
        return;
    }

    string s; 
    int takeA = 0, takeB = 0;
    REP(i, n) {
        if (a[i] > 0) s += 'C';
        else {  
            if (!takeA) {
                s += 'A';
                takeA = 1;
            }
            else if (!takeB) {
                s += 'B';
                takeB = 1;
            }
            else s += 'A';
        }
    }
    cout << "YES" << '\n';
    cout << s << '\n';
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