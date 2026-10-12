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

// 362. Design Hit Counter [Medium]
// One (timestamp, count) bucket per second, not one entry per hit:
// a burst of a million hits in one second is still one deque entry.
class HitCounter {
    deque<pii> q; // (timestamp, hits), timestamps increasing
    int total = 0;
public:
    void hit(int timestamp) {
        if (!q.empty() && q.back().fi == timestamp) q.back().se++;
        else q.push_back({timestamp, 1});
        total++;
    }

    // hits in (timestamp - 300, timestamp]
    int getHits(int timestamp) {
        while (!q.empty() && q.front().fi <= timestamp - 300) {
            total -= q.front().se;
            q.pop_front();
        }
        return total;
    }
};
