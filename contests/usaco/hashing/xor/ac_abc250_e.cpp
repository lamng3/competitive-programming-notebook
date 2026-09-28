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
const int MOD = 998244353; // 1e9+7

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

template <typename T>
class XorHash {
private:
    inline static map<T, u64> tags;
    vector<u64> hash;
    set<T> seen;
public:
    XorHash() { hash.pb(0); }

    u64 tag(const T& x) {
        if (!tags.count(x)) tags[x] = rng();
        return tags[x];
    }

    void add(const T& x) {
        if (seen.count(x)) {
            hash.pb(hash.back());
            return;
        }
        seen.insert(x);
        hash.pb(hash.back() ^ tag(x));
    }

    u64 get_hash(int i) {
        assert(0 <= i && i < sz(hash));
        return hash[i];
    }
    u64 get_hash() { return hash.back(); }
};

void preprocess() {
    
}

void solve() {
    int N; cin >> N;
    vi A(N), B(N);
    REP(i, N) cin >> A[i];
    REP(i, N) cin >> B[i];
    XorHash<int> xA, xB;
    REP(i, N) {
        xA.add(A[i]);
        xB.add(B[i]);
    }
    int Q; cin >> Q;
    REP(i, Q) {
        int x, y; cin >> x >> y;
        if (xA.get_hash(x) == xB.get_hash(y)) {
            cout << "Yes" << '\n';
        }
        else cout << "No" << '\n';
    }
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