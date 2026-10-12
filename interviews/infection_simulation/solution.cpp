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
// Grid: 'X' infected on day 0, '.' healthy, '#' immune. Each day an infected cell
// infects its 4 neighbors; D days after infection it recovers and becomes immune.
// Return the day the last infected cell recovers (0 if nothing is ever infected).
//
// Recovery never stops a spread: a cell infected on day t infects its neighbors on
// day t + 1, before it recovers on day t + D (D >= 1), and a recovered cell cannot be
// infected again. So every cell is infected exactly once, at its BFS distance from the
// nearest 'X', and the answer is that largest distance plus D: a multi-source BFS.
int lastRecoveryDay(const vector<string>& grid, int D) {
    const int dr[4] = {1, -1, 0, 0};
    const int dc[4] = {0, 0, 1, -1};
    int n = sz(grid), m = sz(grid[0]);
    auto inrange = [&](int r, int c) {
        return 0 <= r && r < n && 0 <= c && c < m;
    };
    vector<vi> day(n, vi(m, -1)); // infection day, -1 never
    queue<pii> q;
    REP(r, n) REP(c, m) if (grid[r][c] == 'X') {
        day[r][c] = 0;
        q.push({r, c});
    }
    if (q.empty()) return 0;
    int last = 0;
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        last = day[r][c];
        REP(i, 4) {
            int nr = r + dr[i], nc = c + dc[i];
            if (!inrange(nr, nc) || day[nr][nc] != -1 || grid[nr][nc] == '#') continue;
            day[nr][nc] = day[r][c] + 1;
            q.push({nr, nc});
        }
    }
    return last + D;
}
