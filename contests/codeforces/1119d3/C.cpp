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

void print(const vi& a) {
    REP(i, sz(a)) cout << a[i] << (i == sz(a)-1 ? '\n' : ' ');
}

void solve() {
    int n; cin >> n;
    vi a(n);
    REP(i, n) cin >> a[i];
    
    vi pos1, pos2;
    REP(i, n) {
        if (a[i] == 1) pos1.pb(i);
        if (a[i] == -1) pos2.pb(i);
    }

    if (pos2.empty()) {
        print(a);
        return;
    }
    
    if (pos1.empty()) {
        if (sz(pos2) == 1) a[pos2[0]] = 1;
        else {
            int sj = pos2.front(), ej = pos2.back();
            for (int i : pos2) a[i] = (i == sj || i == ej) ? 1 : 0;
        }
        print(a);
        return;
    }

    for (int i : pos2) a[i] = 0;
    if (pos2.front() < pos1.front()) a[pos2.front()] = 1;
    if (pos2.back() > pos1.back()) a[pos2.back()] = 1;
    print(a);
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