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

const int MAX_N = 1e5;

vi Adj[MAX_N+5];
int dam[MAX_N+5];
int cam[MAX_N+5];
int is_dam[MAX_N+5];
int ans;

void preprocess() {
    
}

int dfs1(int u, int p) {
    dam[u] = is_dam[u];
    for (int v : Adj[u]) {
        if (v == p) continue;
        dam[u] += dfs1(v, u);
    }
    return dam[u];
}

void dfs2(int u, int p) {
    int opt = 0;
    for (int v : Adj[u]) {
        if (v == p) continue;
        opt += (dam[v] > 0);
        dfs2(v, u);
    }
    int choices = is_dam[u] + opt;
    ans += max(choices-1, 0);
    int x = choices-1;
    for (int v : Adj[u]) {
        if (v == p) continue;
        if (x > 0 && dam[v] > 0) {
            cam[v] = 1;
            x--;
        }
    }
}

void solve() {
    int n; cin >> n;

    vi parent(n+1, -1);
    FOR(i,2,n) cin >> parent[i];

    FOR(i,1,n) is_dam[i] = cam[i] = 0;
    
    int m; cin >> m;
    vi a(m+1);
    FOR(i,1,m) {
        cin >> a[i];
        is_dam[a[i]] = 1;
    }

    // adj graph
    REP(i,n+1) Adj[i].clear();
    REP(i,n+1) if (parent[i]!=-1) Adj[parent[i]].pb(i);

    /* 
        each node u has k edges e1..ek and k children v1..vk
        dam[u] = #dams under subtree rooted at u
            if dam[u] = 0, no camera needed
        place cams where dam is possible
    */
    dfs1(1,-1);

    ans = 0;
    dfs2(1,-1);

    vi marked;
    FOR(i, 1, n) if (cam[i]) marked.pb(i);

    cout << ans;
    REP(i, sz(marked)) cout << ' ' << marked[i];
    cout << '\n';
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