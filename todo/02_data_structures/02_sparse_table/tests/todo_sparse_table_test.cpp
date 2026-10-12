#include "../sparse_table.h"
#include "../range_minmax_query_solver.h"
#include "../sparse_table_2d.h"
#include "../sparse_table_2d_square.h"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)
#define DONE() do { printf("\n%d checks, %d failed.\n", checks, fails); return fails ? 1 : 0; } while (0)

int main() {
    mt19937 rng(3);
    auto mn = [](int a, int b) { return min(a, b); };
    for (int it = 0; it < 100; it++) {
        int n = rng() % 40 + 1;
        vector<int> a(n);
        for (int& x : a) x = rng() % 10;
        SparseTable<int, decltype(mn)> st(a, mn);
        RangeMinMax<int> mm(a);
        auto g = [](int x, int y) { return gcd(x, y); };
        SparseTable<int, decltype(g)> sg(a, g);
        for (int l = 0; l < n; l++) for (int r = l + 1; r <= n; r++) {
            int lo = *min_element(a.begin() + l, a.begin() + r), hi = *max_element(a.begin() + l, a.begin() + r);
            int al = min_element(a.begin() + l, a.begin() + r) - a.begin(), ah = max_element(a.begin() + l, a.begin() + r) - a.begin();
            int gg = 0;
            for (int i = l; i < r; i++) gg = gcd(gg, a[i]);
            CHECK(st.query(l, r) == lo && sg.query(l, r) == gg);
            CHECK(mm.min(l, r) == lo && mm.max(l, r) == hi && mm.argmin(l, r) == al && mm.argmax(l, r) == ah);
        }
    }
    for (int it = 0; it < 30; it++) {
        int n = rng() % 9 + 1, m = rng() % 9 + 1;
        vector<vector<int>> g(n, vector<int>(m));
        for (auto& row : g) for (int& x : row) x = rng() % 100;
        SparseTable2D<int, decltype(mn)> st(g, mn);
        SparseTable2DSquare<int, decltype(mn)> sq(g, mn);
        for (int r1 = 0; r1 < n; r1++) for (int r2 = r1 + 1; r2 <= n; r2++)
            for (int c1 = 0; c1 < m; c1++) for (int c2 = c1 + 1; c2 <= m; c2++) {
                int want = INT_MAX;
                for (int i = r1; i < r2; i++) for (int j = c1; j < c2; j++) want = min(want, g[i][j]);
                CHECK(st.query(r1, c1, r2, c2) == want);
                if (r2 - r1 == c2 - c1) CHECK(sq.query(r1, c1, r2 - r1) == want);
            }
    }
    DONE();
}
