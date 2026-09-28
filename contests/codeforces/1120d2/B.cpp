#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128;
using u128 = unsigned __int128;

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
// const int MOD = 998244353; // 1e9+7
const int MOD = 1e9+7;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void preprocess() {
    
}

/*
    each row has distinct minimum
    so k >= n, as k <= 2n then k-n <= n
    fill 1..n in row 1..n at position[0]
        remaining k-n we can move min element at row[i] to position col[i]
    originally we have n rows + (n-1) cols = 2n-1 distinct values
        each move we reduce cols by 1
    what if k = 2*n
*/
void solve() {
    int n, k; cin >> n >> k;
    if (k < n || k >= 2*n) { cout << -1 << '\n'; return; }
    vii A(n, vi(n, 0));
    REP(i, n) A[i][0] = i+1;
    int need = 2*n-1 - k;
    RFOR(i, n) {
        if (need <= 0) break;
        swap(A[i][0], A[i][i]);
        need--;
    }
    int x = n+1;
    REP(i, n) REP(j, n) if (A[i][j] == 0) A[i][j] = x++;
    REP(i, n) REP(j, n) {
        cout << A[i][j] << (j == n-1 ? '\n' : ' ');
    }
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
