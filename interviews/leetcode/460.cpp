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

// 460. LFU Cache [Hard]
// freq -> keys in recency order (a list, front = least recent), plus each key's
// iterator into its list for O(1) unlinking. Evict the front of the smallest frequency.
// The smallest frequency only changes in two ways: a touch can raise it by one,
// and a new key resets it to 1.
class LFUCache {
    int cap, minf = 0;
    unordered_map<int, pii> kv; // key -> (value, freq)
    unordered_map<int, list<int>> keys; // freq -> keys, least recent first
    unordered_map<int, list<int>::iterator> where;

    void touch(int key) {
        int f = kv[key].se;
        keys[f].erase(where[key]);
        if (keys[f].empty()) {
            keys.erase(f);
            if (minf == f) minf++;
        }
        kv[key].se = f + 1;
        keys[f + 1].pb(key);
        where[key] = prev(keys[f + 1].end());
    }
public:
    LFUCache(int capacity) : cap(capacity) {}

    int get(int key) {
        if (!kv.count(key)) return -1;
        touch(key);
        return kv[key].fi;
    }

    void put(int key, int value) {
        if (cap == 0) return;
        if (kv.count(key)) {
            kv[key].fi = value;
            touch(key);
            return;
        }
        if (sz(kv) == cap) {
            int old = keys[minf].front(); // least recent at min freq
            keys[minf].pop_front();
            if (keys[minf].empty()) keys.erase(minf);
            kv.erase(old);
            where.erase(old);
        }
        kv[key] = {value, 1};
        keys[1].pb(key);
        where[key] = prev(keys[1].end());
        minf = 1;
    }
};
