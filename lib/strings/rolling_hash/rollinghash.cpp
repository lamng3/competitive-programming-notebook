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

class RollingHash {
private:
    ll base, mod;
    ll fwdhash, bwdhash;
    ll pow;
public:
    /*
        fwdhash = a0 * x^n + a1 * x^(n-1) + a2 * x^(n-2) + ... + an
        bwdhash = a0 + a1 * x + a2 * x^2 + ... + an * x^n
    */
    RollingHash() : base(313), mod(1e9+7), fwdhash(0), bwdhash(0), pow(1) {}
    RollingHash(ll base, ll mod) : base(base), fwdhash(0), bwdhash(0), pow(1) {}
    void push_back(ll c) {
        fwdhash = (fwdhash * base + c) % mod;
        bwdhash = (bwdhash + c * pow) % mod;
        pow = (pow * base) % mod;
    }
    void push_front(ll c) {
        fwdhash = (fwdhash + c * pow) % mod;
        bwdhash = (bwdhash * base + c) % mod;
        pow = (pow * base) % mod;
    }
    bool is_palindrome() {
        return fwdhash == bwdhash;
    }
    ll get_forward_hash() {
        return fwdhash;
    }
    ll get_backward_hash() {
        return bwdhash;
    }
    ll get_hash(int L, int R) {
        /*
            hash[R] 
                = s[0] * x^R + s[1] * x^(R-1) + .. + s[L-1] * x^(R-L+1) + s[L] * x^(R-L) + .. + s[R]
            hash[L] 
                = s[0] * x^L + s[1] * x^(L-1) + .. + s[L-1] * x^1 + s[L]
            hash[R+1] 
                = s[0] * x^(R+1) + s[1] * x^R + .. + s[L-1] * x^(R-L) + s[L] * x^(R-L+1) + .. + s[R] * x + s[R+1]
            hash[L] * x^(R-L+1)
                = s[0] * x^(R+1) + s[1] * x^R + .. + s[L-1] * x^(R-L) + s[L] * x^(R-L+1)
            hash(s[L..R]) = hash[R+1] - hash[L] * x^(R-L+1) 
                          = s[L+1] * x^(R-L) + .. + s[R] * x + s[R+1]

            note: hash[k] stores prefix hash length k of s[0..k-1]
        */
        return 0;
    }
};

void preprocess() {
    
}

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