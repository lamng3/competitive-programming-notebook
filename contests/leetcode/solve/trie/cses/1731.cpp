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

const int MAX_W = 1e5+5;

int wcount = 0;
int trie[MAX_W][26];
int stop[MAX_W];

void add_word(string w) {
    int v = 0;
    for (char c : w) {
        if (trie[v][c-'a'] == -1) {
            trie[v][c-'a'] = ++wcount;
        }
        v = trie[v][c-'a'];
    }
    stop[v] = 1;
}

// cout << Solution().solve() << '\n';
void solve() {
    string s; cin >> s;
    int k; cin >> k;

    memset(trie, -1, sizeof trie);
    memset(stop, 0, sizeof stop);

    REP(i, k) {
        string w; cin >> w;
        add_word(w);
    }

    int n = s.size();

    vector<ll> dp(n+1, 0);
    dp[0] = 1;

    // dp[i] = # ways to construct s[0..i-1]
    REP(i, n) {
        if (dp[i] == 0) continue;
        int v = 0;
        FOR(j, i, n-1) {
            if (trie[v][s[j]-'a'] == -1) break;
            v = trie[v][s[j]-'a'];
            if (stop[v]) dp[j+1] = (dp[j+1] + dp[i]) % MOD;
        }
    }

    cout << dp[n] << '\n';
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