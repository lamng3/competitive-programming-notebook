// g++ -std=c++17 -DLOCAL template.cpp -o solution
#include <bits/stdc++.h>
using namespace std;

#pragma region Debug
#ifdef LOCAL
template<typename T, typename U>
ostream& operator<<(ostream& os, const pair<T,U>& p) {
    return os << "(" << p.first << ", " << p.second << ")";
}
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    os << "[";
    for (int i = 0; i < (int)v.size(); i++) os << (i ? ", " : "") << v[i];
    return os << "]";
}
template<typename T>
ostream& operator<<(ostream& os, const set<T>& s) {
    os << "{";
    int i = 0;
    for (auto& x : s) os << (i++ ? ", " : "") << x;
    return os << "}";
}
template<typename K, typename V>
ostream& operator<<(ostream& os, const map<K,V>& m) {
    os << "{";
    int i = 0;
    for (auto& [k, v] : m) os << (i++ ? ", " : "") << k << ": " << v;
    return os << "}";
}
void _dbg() { cerr << endl; }
template<typename T, typename... A>
void _dbg(T t, A... a) { cerr << " " << t; if constexpr(sizeof...(a)) cerr << ","; _dbg(a...); }
#define dbg(...) cerr << "\033[35m[" << #__VA_ARGS__ << "]\033[0m:", _dbg(__VA_ARGS__)
#else
#define dbg(...)
#endif
#pragma endregion

using ll = long long;
using vi = vector<int>;
using vii = vector<vector<int>>;
using pii = pair<int, int>;

#define REP(i, n) for (int i = 0; i < (n); i++)
#define FOR(i, a, b) for (int i = (a); i <= (b); i++)
#define FORD(i, a, b) for (int i = (a); i >= (b); i--)
#define RFOR(i, n) for (int i = (n) - 1; i >= 0; i--)

#define fi first
#define se second
#define pb push_back

const int INF = 1e9;
const ll LLINF = 2e18;

const int MOD = 1e9+7;
const int MOD_NTT = 998244353; // number theoretic transform (NTT)

int di[4] = {1,0,-1,0};
int dj[4] = {0,1,0,-1};

// 1391. Check if There is a Valid Path in a Grid [Medium]
class Solution {
public:
    vii transform(int x) {
        if (x == 1) return {{0,0,0},{1,1,1},{0,0,0}};
        if (x == 2) return {{0,1,0},{0,1,0},{0,1,0}};
        if (x == 3) return {{0,0,0},{1,1,0},{0,1,0}};
        if (x == 4) return {{0,0,0},{0,1,1},{0,1,0}};
        if (x == 5) return {{0,1,0},{1,1,0},{0,0,0}};
        if (x == 6) return {{0,1,0},{0,1,1},{0,0,0}};
        return {{0,0,0},{0,0,0},{0,0,0}};
    }

    bool inrange(int i, int j, int M, int N) {
        return 0 <= i && i < M && 0 <= j && j < N;
    }

    void floodfill(int i, int j, int M, int N, vii& g) {
        if (!inrange(i, j, M, N) || g[i][j] != 1) return;
        g[i][j] = 2;
        for (int k = 0; k < 4; k++) {
            int ni = i + di[k], nj = j + dj[k];
            floodfill(ni, nj, M, N, g);
        }
    }

    bool hasValidPath(vii& grid) {
        int m = (int)grid.size(), n = (int)grid[0].size();
        int M = 3*m, N = 3*n;

        vii g(M, vi(N, 0));
        REP(i, m) {
            REP(j, n) {
                vii cell = transform(grid[i][j]);
                REP(ii, 3) {
                    REP(jj, 3) {
                        g[i*3+ii][j*3+jj] = cell[ii][jj];
                    }
                }
            }
        }

        // floodfill from first cell
        int si = -1, sj = -1;
        REP(i, 3) {
            REP(j, 3) {
                if (g[i][j]) {
                    si = i;
                    sj = j;
                    break;
                }
            }
        }

        floodfill(si, sj, M, N, g);

        bool ok = false;
        // (3 * (m-1), 3 * (n-1))
        REP(i, 3) {
            REP(j, 3) {
                if (g[3*(m-1)+i][3*(n-1)+j]) {
                    ok = true;
                    break;
                }
            }
        }
        return ok;
    }
};

#if !defined(CPTEST) && (defined(LOCAL) || defined(ONLINE_JUDGE))
void preprocess() {
    
}

// cout << Solution().solve() << '\n';
void solve() {
    
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
#endif