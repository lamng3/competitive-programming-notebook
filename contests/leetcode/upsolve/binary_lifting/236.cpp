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

const int INF = 1e9;
const ll LLINF = 2e18;

const int MOD = 1e9+7;
const int MOD_NTT = 998244353; // number theoretic transform (NTT)

// 236. Lowest Common Ancestor of a Binary Tree [Medium]
#ifdef LOCAL
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
#endif

const int MAXNODES = 1e5+5;
const int MAXSTEPS = 25;

map<TreeNode*, map<int, TreeNode*>> lift;
vector<TreeNode*> euler;

map<TreeNode*, TreeNode*> parent;
map<TreeNode*, int> depth;

class Solution {
public:
    void flatten(TreeNode* node, int d) {
        if (!node) return;
        depth[node] = d;
        euler.pb(node);
        if (node->left) {
            parent[node->left] = node;
            flatten(node->left, d+1);
        }
        if (node->right) {
            parent[node->right] = node;
            flatten(node->right, d+1);
        }
    }

    void buildLift() {
        int n = (int)euler.size();

        REP(i, n) {
            REP(j, MAXSTEPS) {
                lift[euler[i]][j] = nullptr;
            }
        }

        REP(i, n) lift[euler[i]][0] = parent[euler[i]];

        FOR(j, 1, MAXSTEPS) {
            REP(i, n) {
                if (lift[euler[i]][j-1] != nullptr) {
                    lift[euler[i]][j] = lift[lift[euler[i]][j-1]][j-1];
                }
            }
        }
    }

    TreeNode* liftK(TreeNode* node, int k) {
        if (!node) return node;
        REP(j, MAXSTEPS) {
            if (k & (1 << j)) {
                node = lift[node][j];
                if (node == nullptr) break;                
            }
        }
        return node;
    }

    TreeNode* findLCA(TreeNode* p, TreeNode* q) {
        if (depth[p] < depth[q]) swap(p, q);
        // p is deeper than q
        int K = depth[p] - depth[q];
        p = liftK(p, K);
        if (p == q) return p;
        RFOR(j, MAXSTEPS) {
            if (lift[p][j] != lift[q][j]) {
                p = lift[p][j];
                q = lift[q][j];
            }
        }
        return lift[p][0];
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        parent[root] = nullptr;
        flatten(root, 0);
        buildLift();
        TreeNode* ans = findLCA(p, q);
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