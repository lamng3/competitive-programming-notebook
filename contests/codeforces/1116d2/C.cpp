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
        goal is to not hold a hot potato
        supposed 2 teams start with R and B
            goal for each team is to minimize R and B
            R + B = X with X = initial number of hot potatos
        a1: keep potato (0)
        a2: pass potato (R-1 B+1) or (R+1 B-1)
        in consecutive potatos, only the last one s[i] = 1 and s[i+1] = 0 can move
        optimally when consecutive potatos yields higher points:
            for B and ends at B: B keep
            for A and ends at A: A keep
            for B and ends at A: A move, and cascade
            for A and ends at B: B move, and cascade
        for k arbitrary number of rounds, potatos will be pushed up 

        supposed [L..R] = 11111 and s[R+1] = 0 and R-L+1 = m
        if m odd:
            L and R are red
            when move s[R] to s[R+1] is beneficial to red
            next round s[R-1] will move to empty space R
            ...
            at the end it will end at [L+1..R+1] which is beneficial to red
        if m even:
            L red and R blue
            when move s[R] to s[R+1] is beneficial to blue
            next round s[L] will move to empty space R
            ...
            at the end it will end at [L+1..R+1] which is equal
            so will always be beneficial or equal
        supposedly have space after R+1, then we just need to continue moving
    */
    int n, k; cin >> n >> k;
    string s; cin >> s;
    vi ans = {0, 0};
    REP(i, 2*n) ans[1-i%2] += (s[i] == '1');
    REP(i, 2*n) {
        if (s[i] == '1' && s[(i+1)%(2*n)] == '0') {
            ans[i%2] += 1;
            ans[1-i%2] -= 1;
        }
    }
    cout << ans[0] << ' ' << ans[1] << '\n';
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