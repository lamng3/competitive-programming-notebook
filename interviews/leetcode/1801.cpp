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

// 1801. Number of Orders in the Backlog [Medium]
// An order book: buys in a max-heap, sells in a min-heap. A new order trades
// against the best opposite price while prices cross, one heap entry at a time;
// whatever is left joins its own side.
class Solution {
public:
    int getNumberOfBacklogOrders(vector<vi>& orders) {
        const int MOD = 1e9+7;
        priority_queue<pii> buy; // (price, amount), highest price on top
        priority_queue<pii, vector<pii>, greater<pii>> sell; // lowest price on top
        for (auto& o : orders) {
            int price = o[0], amount = o[1], type = o[2];
            if (type == 0) { // buy: match the cheapest sell <= price
                while (amount && !sell.empty() && sell.top().fi <= price) {
                    auto [p, a] = sell.top();
                    sell.pop();
                    int t = min(amount, a);
                    amount -= t;
                    if (a - t) sell.push({p, a - t});
                }
                if (amount) buy.push({price, amount});
            } else {         // sell: match the highest buy >= price
                while (amount && !buy.empty() && buy.top().fi >= price) {
                    auto [p, a] = buy.top();
                    buy.pop();
                    int t = min(amount, a);
                    amount -= t;
                    if (a - t) buy.push({p, a - t});
                }
                if (amount) sell.push({price, amount});
            }
        }
        ll total = 0;
        for (; !buy.empty(); buy.pop()) total += buy.top().se;
        for (; !sell.empty(); sell.pop()) total += sell.top().se;
        return total % MOD;
    }
};
