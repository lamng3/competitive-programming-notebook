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

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;

int n, m;
vector<string> ban;

namespace Sub1 {
    bool istask() {
        return m == 0;
    }
    void execute() {
        ll ans = 1;
        while (n--) ans = (ans * 26) % MOD;
        cout << ans << '\n';
    }
}

namespace Sub2 {
    bool istask() {
        return n <= 3 && m <= 10;
    }

    vector<string> candidates;

    void backtrack(string& s) {
        if (sz(s) == n) {
            string r = s;
            candidates.pb(r);
            return;
        }
        REP(i, 26) {
            char c = (char)('a'+i);
            s += c;
            backtrack(s);
            s.pop_back();
        }
    }

    void execute() {
        candidates.clear();

        string s = "";
        backtrack(s);

        auto check = [&](string& s1, string& s2) {
            if (sz(s1) < sz(s2)) return 1;
            REP(i,sz(s1)-sz(s2)+1) {
                string run = "";
                REP(j,sz(s2)) run += s1[i+j];
                if (run == s2) return 0;
            }            
            return 1;
        };
        
        int ans = 0;
        for (auto& cand : candidates) {
            int ok = 1;
            REP(i, m) {
                if (!check(cand, ban[i])) {
                    ok = 0;
                    break;
                }
            }
            ans += ok;
        }
        cout << ans << '\n';
    }
}

namespace Sub3 {
    bool istask() {
        return m == 1;
    }

    void execute() {
        
    }
}

namespace Full {
    void run() {
        
    }
}

void preprocess() {
    
}

void solve() {
    cin >> n >> m;
    ban.resize(m);
    REP(i,m) cin >> ban[i];

    if (Sub1::istask()) { Sub1::execute(); return; }
    if (Sub2::istask()) { Sub2::execute(); return; }
    if (Sub3::istask()) { Sub3::execute(); return; }
    Full::run();
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