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

// 1146. Snapshot Array [Medium]
// Store only changes: each index keeps (snap_id, value) pairs in increasing snap_id,
// and get finds the last change made at or before snap_id with a binary search.
class SnapshotArray {
    int snap_id = 0;
    vector<vector<pii>> hist;
public:
    SnapshotArray(int length) : hist(length, vector<pii>{{-1, 0}}) {} // a sentinel: 0 before any snap

    void set(int index, int val) {
        auto& h = hist[index];
        if (h.back().fi == snap_id) h.back().se = val; // same snap: overwrite
        else h.pb({snap_id, val});
    }

    int snap() {
        return snap_id++;
    }

    int get(int index, int snap_id) {
        auto& h = hist[index];
        return prev(upper_bound(all(h), pii{snap_id, INT_MAX}))->se; // last pair with id <= snap_id
    }
};
