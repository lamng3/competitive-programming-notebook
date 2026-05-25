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

// 2^30 ~ 1e9
// relationships: i -> (i*2) and (i*2+1)
// LCA(a, b) -> depth a and b

// 2509. Cycle Length Queries in a Tree [Hard]
class Solution {
public:
    int depth(int a) {
        int res = 0;
        while (a) {
            res++;
            a >>= 1;
        }
        return res;
    }

    int lift(int a, int k) {
        REP(i, k) {
            a >>= 1;
            if (a == 0) break;
        }
        return a;
    }

    int query(int n, int a, int b) {
        int da = depth(a);
        int db = depth(b);
        int K = abs(da - db);
        if (da < db) swap(a, b);

        int res = 1; // included new edge added

        res += K;
        a = lift(a, K);

        if (a == b) return res;

        // LCA(a, b)
        for (int k = n; k >= 1; k--) {
            if (lift(a, k) != lift(b, k)) {
                a = lift(a, k);
                b = lift(b, k);
                res += 2 * k;
            }
        }

        // 1 more lift
        return res + 2;
    }

    vi cycleLengthQueries(int n, vii& queries) {
        int m = (int)queries.size();
        vi ans(m, 0);
        REP(i, m) {
            int a = queries[i][0], b = queries[i][1];
            ans[i] = query(n, a, b);
        }
        return ans;
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