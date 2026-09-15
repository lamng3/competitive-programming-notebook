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

#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())

#define fi first
#define se second
#define pb push_back

const int INF = 1e9+7;
const int MOD = 1e9+7;

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
    /* 
        dp[0][0] = a[0]
        dp[1][0] = a[1]
        dp[1][1] = dp[0][0]

        dp[i][0/1] = min skip points to beat boss [0..i] if boss i beaten by 0/1
        at boss i
        if 0 turn:
            1) i-1 beaten by 0 then i-2 beaten by 1 
                dp[i][0] = min(a[i] + a[i-1] + dp[i-2][1])
            2) i-1 beaten by 1
                dp[i][0] = min(a[i] + dp[i-1][1])
        if 1 turn:
            dp[i][1] = min(dp[i-2][0], dp[i-1][0])
    */
    int n; cin >> n;
    vi a(n);
    REP(i, n) cin >> a[i];
    if (n == 1) {
        cout << a[0] << '\n';
        return;
    }
    vii dp(n, vi(2, INF));
    dp[0][0] = dp[1][1] = a[0];
    dp[1][0] = a[0] + a[1];
    FOR(i, 2, n-1) {
        if (dp[i-2][1] != INF) dp[i][0] = min(dp[i][0], a[i] + a[i-1] + dp[i-2][1]);
        if (dp[i-1][1] != INF) dp[i][0] = min(dp[i][0], a[i] + dp[i-1][1]);
        dp[i][1] = min({dp[i][1], dp[i-1][0], dp[i-2][0]});
    }
    int ans = min(dp[n-1][0], dp[n-1][1]);
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