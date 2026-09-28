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

/*
    n = 2: ABAABBAB
        A: 0 23  6
        B:  1  45 7
    n = 3: AABABCACBBCC
        A: 01 3  6
        B:   2 4   89
        C:      5 7  1011
*/
void solve() {
    int n; cin >> n;
    vi x(4*n);
    auto fill2 = [&](int i, int a, int b) {
        if (i >= 4*n) return;
        int posa[4] = {0,2,3,6};
        int posb[4] = {1,4,5,7};
        for (int j : posa) x[i+j] = a;
        for (int j : posb) x[i+j] = b;
    };
    auto fill3 = [&](int i, int a, int b, int c) {
        if (i >= 4*n) return;
        int posa[4] = {0,1,3,6};
        int posb[4] = {2,4,8,9};
        int posc[4] = {5,7,10,11};
        for (int j : posa) x[i+j] = a;
        for (int j : posb) x[i+j] = b;
        for (int j : posc) x[i+j] = c;
    };
    int i = 0, a = 1, b = 2;
    if (n%2) {
        fill3(0,1,2,3);
        a = 4;
        b = 5;
        i += 12;
    }
    while (i < 4*n) {
        fill2(i,a,b);
        a += 2;
        b += 2;
        i += 8;
    }
    REP(i,4*n) cout << x[i] << (i==4*n-1 ? '\n' : ' ');
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