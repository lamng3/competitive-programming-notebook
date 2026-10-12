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

// 380. Insert Delete GetRandom O(1) [Medium]
// A vector for O(1) random access, a map for O(1) lookup of where each value sits.
// Delete moves the last element into the hole, so the vector never has gaps.
class RandomizedSet {
    vi vals;
    unordered_map<int, int> pos; // value -> index in vals
    mt19937 rng{random_device{}()};
public:
    bool insert(int val) {
        if (pos.count(val)) return false;
        pos[val] = sz(vals);
        vals.pb(val);
        return true;
    }

    bool remove(int val) {
        if (!pos.count(val)) return false;
        int i = pos[val], last = vals.back();
        vals[i] = last; // last fills the hole (a no-op when val is last)
        pos[last] = i;
        vals.pop_back();
        pos.erase(val);
        return true;
    }

    int getRandom() {
        return vals[rng() % sz(vals)];
    }
};
