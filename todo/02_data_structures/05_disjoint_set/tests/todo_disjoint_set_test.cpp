#include "../disjoint_set_2d.h"
#include "../persistent_disjoint_set.h"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)
#define DONE() do { printf("\n%d checks, %d failed.\n", checks, fails); return fails ? 1 : 0; } while (0)

int main() {
    mt19937 rng(6);
    for (int it = 0; it < 50; it++) { // regions of a random picture, against flood fill
        int n = rng() % 8 + 1, m = rng() % 8 + 1;
        vector<string> g(n, string(m, '.'));
        for (auto& row : g) for (char& c : row) c = "ab"[rng() % 2];
        DSU2D d(n, m);
        d.unite_neighbors([&](int r1, int c1, int r2, int c2) { return g[r1][c1] == g[r2][c2]; });
        vector<vector<int>> comp(n, vector<int>(m, -1));
        int k = 0;
        vector<int> area;
        for (int r = 0; r < n; r++) for (int c = 0; c < m; c++) if (comp[r][c] < 0) {
            vector<pair<int, int>> st = {{r, c}};
            comp[r][c] = k;
            int a = 0;
            while (!st.empty()) {
                auto [x, y] = st.back(); st.pop_back(); a++;
                int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
                for (int i = 0; i < 4; i++) {
                    int nx = x + dx[i], ny = y + dy[i];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m && comp[nx][ny] < 0 && g[nx][ny] == g[x][y]) comp[nx][ny] = k, st.push_back({nx, ny});
                }
            }
            area.push_back(a), k++;
        }
        CHECK(d.components() == k);
        for (int r = 0; r < n; r++) for (int c = 0; c < m; c++) CHECK(d.size(r, c) == area[comp[r][c]]);
    }
    for (int it = 0; it < 30; it++) { // persistent: every version against a replay
        int n = rng() % 12 + 1;
        PersistentDSU p(n);
        vector<vector<int>> labels = {vector<int>(n)}; // labels[v] = component labels in version v
        iota(labels[0].begin(), labels[0].end(), 0);
        for (int q = 0; q < 40; q++) {
            int v = rng() % p.versions(), a = rng() % n, b = rng() % n;
            int nv = p.unite(v, a, b);
            auto lab = labels[v];
            int la = lab[a], lb = lab[b];
            for (int& x : lab) if (x == lb) x = la;
            labels.push_back(lab);
            CHECK(nv == (int)labels.size() - 1);
        }
        for (int v = 0; v < p.versions(); v++)
            for (int a = 0; a < n; a++) {
                int b = rng() % n;
                CHECK(p.same(v, a, b) == (labels[v][a] == labels[v][b]));
                CHECK(p.size(v, a) == count(labels[v].begin(), labels[v].end(), labels[v][a]));
            }
    }
    DONE();
}
