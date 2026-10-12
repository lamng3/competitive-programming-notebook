#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;

#define REP(i, n) for (int i = 0; i < (n); i++)
#define FOR(i, a, b) for (int i = (a); i <= (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())
#define fi first
#define se second
#define pb push_back

// 347. Top K Frequent Elements [Medium]
// Bucket sort by frequency: a frequency is at most n, so bucket[f] lists the
// values seen f times, and reading buckets from n down is O(n), no heap.
class Solution {
public:
    vi topKFrequent(vi& nums, int k) {
        int n = sz(nums);
        unordered_map<int, int> cnt;
        for (int x : nums) cnt[x]++;
        vector<vi> bucket(n + 1);
        for (auto& [x, f] : cnt) bucket[f].pb(x);
        vi ans;
        for (int f = n; f >= 1; f--) {
            for (int x : bucket[f]) {
                ans.pb(x);
                if (sz(ans) == k) return ans;
            }
        }
        return ans;
    }
};
