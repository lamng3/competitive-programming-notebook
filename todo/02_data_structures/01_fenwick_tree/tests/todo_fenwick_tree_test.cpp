#include "../fenwick_tree_2d_sum.h"
#include "../fenwick_tree_2d_sparse_sum.h"
#include "../fenwick_tree_3d_sum.h"
#include "../range_add_query_sum_solver.h"
#include "../range_add_query_sum_solver_2d.h"
#include "../range_xor_query_xor_solver_2d.h"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)
#define DONE() do { printf("\n%d checks, %d failed.\n", checks, fails); return fails ? 1 : 0; } while (0)

using ll = long long;

int main() {
    mt19937 rng(2);
    for (int it = 0; it < 30; it++) { // 2D and rect-add 2D and xor 2D against a grid
        int n = rng() % 8 + 1, m = rng() % 8 + 1;
        vector<vector<ll>> a(n + 2, vector<ll>(m + 2, 0)), xr = a;
        Fenwick2D<ll> f(n, m);
        RectAddRectSum<ll> r(n, m);
        RectXorRectXor x(n, m);
        for (int q = 0; q < 200; q++) {
            int x1 = rng() % n + 1, x2 = rng() % n + 1, y1 = rng() % m + 1, y2 = rng() % m + 1;
            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);
            ll v = (ll)(rng() % 21) - 10, w = rng() % 1024;
            int op = rng() % 4;
            if (op == 0) { f.add(x1, y1, v); r.add(x1, y1, x1, y1, v); a[x1][y1] += v; }
            else if (op == 1) {
                r.add(x1, y1, x2, y2, v);
                f = Fenwick2D<ll>(n, m);
                for (int i = x1; i <= x2; i++) for (int j = y1; j <= y2; j++) a[i][j] += v;
                for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if (a[i][j]) f.add(i, j, a[i][j]);
            } else if (op == 2) {
                x.update(x1, y1, x2, y2, w);
                for (int i = x1; i <= x2; i++) for (int j = y1; j <= y2; j++) xr[i][j] ^= w;
            } else {
                ll s = 0, sx = 0;
                for (int i = x1; i <= x2; i++) for (int j = y1; j <= y2; j++) s += a[i][j], sx ^= xr[i][j];
                CHECK(f.rect(x1, y1, x2, y2) == s);
                CHECK(r.sum(x1, y1, x2, y2) == s);
                CHECK(x.query(x1, y1, x2, y2) == sx);
            }
        }
    }
    for (int it = 0; it < 20; it++) { // sparse 2D on huge coordinates
        vector<pair<ll, ll>> pts;
        for (int i = 0; i < 40; i++) pts.push_back({(ll)(rng() % 1000) * 1000000, (ll)(rng() % 1000) - 500});
        Fenwick2DSparse<ll> f(pts);
        map<pair<ll, ll>, ll> val;
        for (int q = 0; q < 200; q++) {
            if (rng() % 2) {
                auto p = pts[rng() % pts.size()];
                ll v = (ll)(rng() % 21) - 10;
                f.add(p.first, p.second, v);
                val[p] += v;
            } else {
                ll x = (ll)(rng() % 1100) * 1000000 - 50000000, y = (ll)(rng() % 1100) - 550, s = 0;
                for (auto& [p, v] : val) if (p.first <= x && p.second <= y) s += v;
                CHECK(f.sum(x, y) == s);
            }
        }
    }
    { // 3D
        int n = 4, m = 5, k = 3;
        Fenwick3D<ll> f(n, m, k);
        ll a[5][6][4] = {};
        for (int q = 0; q < 500; q++) {
            int x = rng() % n + 1, y = rng() % m + 1, z = rng() % k + 1;
            if (rng() % 2) { ll v = rng() % 10; f.add(x, y, z, v); a[x][y][z] += v; }
            else {
                int x1 = rng() % x + 1, y1 = rng() % y + 1, z1 = rng() % z + 1;
                ll s = 0;
                for (int i = x1; i <= x; i++) for (int j = y1; j <= y; j++) for (int l = z1; l <= z; l++) s += a[i][j][l];
                CHECK(f.box(x1, y1, z1, x, y, z) == s);
            }
        }
    }
    { // 1D range add range sum
        int n = 50;
        RangeAddRangeSum<ll> f(n);
        vector<ll> a(n + 1, 0);
        for (int q = 0; q < 2000; q++) {
            int l = rng() % n + 1, r = rng() % n + 1;
            if (l > r) swap(l, r);
            if (rng() % 2) { ll v = (ll)(rng() % 21) - 10; f.add(l, r, v); for (int i = l; i <= r; i++) a[i] += v; }
            else CHECK(f.sum(l, r) == accumulate(a.begin() + l, a.begin() + r + 1, 0LL));
        }
    }
    DONE();
}
