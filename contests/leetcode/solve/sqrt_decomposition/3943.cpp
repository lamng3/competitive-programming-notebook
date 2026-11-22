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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

/*
Square Root Decomposition: range add, count the elements equal to x
*/
struct SqrtDecomposition {
    int BLOCK_SIZE;
    vector<ll> A;
    vector<ll> lazy;                      // added to every element of its block
    vector<unordered_map<ll, int>> freq;  // per block: value -> count, without lazy

    SqrtDecomposition(int block_size, const vi& a) : BLOCK_SIZE(block_size), A(a.begin(), a.end()) {
        int num_blocks = ((int)A.size() + BLOCK_SIZE - 1) / BLOCK_SIZE;
        lazy.assign(num_blocks, 0);
        freq.resize(num_blocks);
        for (auto& f : freq) f.reserve(2 * BLOCK_SIZE);
        REP(i, (int)A.size()) freq[i / BLOCK_SIZE][A[i]]++;
    }

    /* O(1): add v to A[i] */
    void add(int i, ll v) {
        auto& f = freq[i / BLOCK_SIZE];
        if (--f[A[i]] == 0) f.erase(A[i]);
        A[i] += v;
        f[A[i]]++;
    }

    /* O(BLOCK_SIZE + n / BLOCK_SIZE): add v to A[L..R] */
    void add(int L, int R, ll v) {
        int bL = L / BLOCK_SIZE, bR = R / BLOCK_SIZE;
        if (bL == bR) {
            FOR(i, L, R) add(i, v);
            return;
        }
        FOR(i, L, (bL + 1) * BLOCK_SIZE - 1) add(i, v);
        FOR(b, bL + 1, bR - 1) lazy[b] += v;
        FOR(i, bR * BLOCK_SIZE, R) add(i, v);
    }

    /* O(n / BLOCK_SIZE): how many elements equal x */
    int count(ll x) {
        int res = 0;
        REP(b, (int)freq.size()) {
            auto it = freq[b].find(x - lazy[b]);
            if (it != freq[b].end()) res += it->se;
        }
        return res;
    }
};

// 3943. Number of Pairs After Increment [Hard]
class Solution {
public:
    vi numberOfPairs(vi& nums1, vi& nums2, vii& queries) {
        int n = (int)nums2.size();

        // nums1 has at most 5 values: keep each distinct value with its count
        map<int, int> cnt1;
        for (int x : nums1) cnt1[x]++;

        // an update rewrites up to 2 * block_size elements, 3 hash operations each, and a count
        // looks once in each block for each value of nums1: this block size balances the two
        int block_size = max(1, (int)sqrt(n * (int)cnt1.size() / 6));
        SqrtDecomposition blocks(block_size, nums2);

        vi ans;
        for (auto& q : queries) {
            if (q[0] == 1) {
                blocks.add(q[1], q[2], q[3]);
            }
            else {
                int pairs = 0;
                for (auto& [x, c] : cnt1) pairs += c * blocks.count(q[1] - x);
                ans.pb(pairs);
            }
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