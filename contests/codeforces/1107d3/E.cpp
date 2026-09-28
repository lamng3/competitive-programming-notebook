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

const int MAXN = 2e5+5;

int A[MAXN];
vi Adj[MAXN];
int sub[MAXN];
int parent[MAXN];

void preprocess() {
    
}

/*
    lca:
        p(u,v) = p(0,u) * p(0,v) / (p(0,lca(u,v))^2)

    p(u,v) * p(v,w) * p(w,u)
    =  (p(0,u) * p(0,v) * p(0,w) / p(0,lca(u,v)) * p(0,lca(v,w)) * p(0,lca(w,u))) ^ 2

    find u,v,w such that 
        S = p(0,u) * p(0,v) * p(0,w) 
        P = p(0,lca(u,v)) * p(0,lca(v,w)) * p(0,lca(w,u))
        S is divisible by P
    
    the relationship between lca(u,v); lca(v,w); lca(w,u);
        * Lemma 1: at least 2 out of 3 are equal

    supposed u,v,w meets at a point M
    then path (u,v), (v,w), (w,u) goes through M
        meaning each vertices is counted twice, but M is counted 3 times
    to form perfect squares, M has to be a perfect square vertex

    combinatoric:
        find K square vertices, cannot be leaf node
        for each square vertex u:
            sub[u]-1 = size of subtree rooted at u without u
            int r = 0
            r += (sub[u]-1) * (sub[u]-2) * (n-sub[u])
            r += (sub[u]-1) * (n-sub[u]) * (n-sub[u]-1)
*/

int dfs(int u, int p) {
    sub[u] = 1;
    parent[u] = p;
    for (int v : Adj[u]) {
        if (v == p) continue;
        sub[u] += dfs(v, u);
    }
    return sub[u];
}

void solve() {
    int n; cin >> n;

    REP(i,n) cin >> A[i];

    REP(i,n) Adj[i].clear();
    REP(i,n-1) {
        int u, v; cin >> u >> v;
        u--; v--;
        Adj[u].pb(v);
        Adj[v].pb(u);
    }

    dfs(0,-1);

    ll ans = 0;
    REP(u,n) {
        int x = sqrt(A[u]);
        if (x * x != A[u]) continue;
        // branches when u is removed from tree
        vector<ll> branches;
        for (int v : Adj[u]) {
            if (v == parent[u]) continue;
            branches.pb(sub[v]);
        }
        if (u != 0) branches.pb(n - sub[u]);
        // p2 = pairs; p3 = triplets;
        // if u is 1 of the triplets, we need to select pairs
        // prefix sum is a good technique to calculate possibilities
        ll pref = 0, p2 = 0, p3 = 0;
        for (auto& b : branches) {
            p3 += b * p2;
            p2 += b * pref;
            pref += b;
        }
        ans += p2 + p3;
    }
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