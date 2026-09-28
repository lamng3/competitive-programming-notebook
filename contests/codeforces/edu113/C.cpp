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
// const int MOD = 1e9+7;
const int MOD = 998244353;

class Solution {
// LeetCode method function
// void solve() {}
public:

};

#if !defined(CPTEST) && (defined(LOCAL) || defined(ONLINE_JUDGE))
void preprocess() {
    
}

ll binpow(ll a, ll b) {
    a %= MOD;
    ll res = 1;
    while(b) {
        if (b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

ll modInverse(ll x) {
    return binpow(x, MOD-2);
}

// cout << Solution().solve() << '\n';
void solve() {
    int n; cin >> n;
    vi a(n); 
    REP(i, n) cin >> a[i];

    // pi go 3 times a row if pi >= max others + 2
    int mx1 = 0, mx2 = 0;
    REP(i, n) {
        vi cmx = {mx1, mx2, a[i]};
        sort(cmx.begin(), cmx.end());
        mx1 = cmx[2];
        mx2 = cmx[1];
    }

    // dbg(mx1, mx2);

    if (mx1 - mx2 >= 2) {
        cout << 0 << '\n';
        return;
    }

    ll res = 1;
    FOR(x, 1, n) res = (res * x) % MOD;

    if (mx1 == mx2) {
        cout << res << '\n';
        return;
    }

    // mx1 = mx2 + 1
    // this fails when mx1 comes after mx2, so when this happen?
    // mx1 chooses N-1 positions (1..N-1)
    // supposed mx1 chose i
    // mx2 has 0..i-1 = i positions to choose from
    // remaining is N-2!
    // (N * (N-1)/2) * (N-2)! = N! / 2
    // supposed there are K numbers = mx2
    // then mx2 has KCi options
    // KC1 + KC2 + ... + KC(N-1) = (K+1)CN
    // k! to arrange mx2 among themselves, (n-1-k)! to arrange the res
    // k! * (n-1-k)! * (k+1)Cn = (n! / ((n-k-1)! * (k+1)!)) * k! * (n-1-k)! = n! / (k+1)

    int count_mx2 = 0;
    REP(i, n) count_mx2 += (a[i] == mx2);

    ll invalid = (res * modInverse(count_mx2 + 1)) % MOD;
    res = (res - invalid + MOD) % MOD;
    cout << res << '\n';
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