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
template<typename T>
ostream& operator<<(ostream& os, queue<T> q) {
    os << "[";
    bool first = true;
    while (!q.empty()) {
        if (!first) os << ", ";
        os << q.front();
        q.pop();
        first = false;
    }
    return os << "]";
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

const int INF = 1e9+7;
const ll LLINF = 2e18;

const int MOD = 1e9+7;
const int MOD_NTT = 998244353; // number theoretic transform (NTT)

class Solution {
// LeetCode method function
// void solve() {}
public:

};

#if !defined(CPTEST) && (defined(LOCAL) || defined(ONLINE_JUDGE))
void preprocess() {
    
}

// cout << Solution().solve() << '\n';
void solve() {
    int n; cin >> n;

    vi a(2*n);
    vi L(n, -1), R(n, -1);

    REP(i, 2*n) {
        cin >> a[i];
        if (L[a[i]] == -1) L[a[i]] = i;
        else R[a[i]] = i;
    }

    // L[0]..R[0]
    // [L[0],L[0]]
    // [R[0],R[0]]

    auto mex_expand = [&](int center) {
        vi f(n, 0);
        f[a[center]] = 1;
        REP(i, n+1) {
            int left = center - i, right = center + i;
            if (left < 0 || right >= 2*n) break;
            if (a[left] != a[right]) break;
            f[a[left]] = 1;
        }
        int mex = 0;
        REP(i, n) {
            if (f[i]) mex = i+1;
            else break;
        }
        return mex;
    };

    auto mex_expand_both = [&](int left, int right) {
        int cleft = left, cright = right;
        while (cleft <= cright) {
            if (a[cleft] != a[cright]) break;
            cleft++;
            cright--;
        }
        if (cleft < cright) return 1;
        while (left >= 0 && right < 2*n && a[left] == a[right]) {
            left--;
            right++;
        }
        vi f(n, 0);
        for (int i = left+1; i <= right-1; i++) f[a[i]] = 1;
        int mex = 0;
        REP(i, n) {
            if (f[i]) mex = i+1;
            else break;
        }
        return mex;
    };

    int ans = 0;
    ans = max(ans, mex_expand(L[0]));
    ans = max(ans, mex_expand(R[0]));
    ans = max(ans, mex_expand_both(L[0], R[0]));
    cout << ans << '\n';
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
#endif