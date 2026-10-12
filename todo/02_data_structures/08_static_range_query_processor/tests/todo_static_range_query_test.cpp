#include "../static_range_query_processor.h"
#include "../static_range_query_processor_2d.h"
#include "../static_range_query_processor_3d.h"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)
#define DONE() do { printf("\n%d checks, %d failed.\n", checks, fails); return fails ? 1 : 0; } while (0)

using ll = long long;
typedef array<int, 3> Perm; // a non-commutative group: permutations of 3 elements

int main() {
    mt19937 rng(8);
    auto add = [](ll a, ll b) { return a + b; };
    auto neg = [](ll a) { return -a; };
    auto xr = [](ll a, ll b) { return a ^ b; };
    auto same = [](ll a) { return a; };
    auto comp = [](Perm a, Perm b) { Perm r; for (int i = 0; i < 3; i++) r[i] = b[a[i]]; return r; }; // a then b
    auto pinv = [](Perm a) { Perm r; for (int i = 0; i < 3; i++) r[a[i]] = i; return r; };
    for (int it = 0; it < 50; it++) {
        int n = rng() % 30 + 1;
        vector<ll> a(n);
        vector<Perm> p(n);
        for (int i = 0; i < n; i++) {
            a[i] = (ll)(rng() % 100) - 50;
            p[i] = {0, 1, 2};
            shuffle(p[i].begin(), p[i].end(), rng);
        }
        StaticRangeQuery<ll, decltype(add), decltype(neg)> s(a, add, neg, 0);
        StaticRangeQuery<Perm, decltype(comp), decltype(pinv)> sp(p, comp, pinv, Perm{0, 1, 2});
        for (int l = 0; l <= n; l++) for (int r = l; r <= n; r++) {
            CHECK(s.query(l, r) == accumulate(a.begin() + l, a.begin() + r, 0LL));
            Perm want = {0, 1, 2};
            for (int i = l; i < r; i++) want = comp(want, p[i]);
            CHECK(sp.query(l, r) == want);
        }
    }
    for (int it = 0; it < 20; it++) {
        int n = rng() % 6 + 1, m = rng() % 6 + 1, k = rng() % 6 + 1;
        vector<vector<ll>> g(n, vector<ll>(m));
        vector<vector<vector<ll>>> b(n, vector<vector<ll>>(m, vector<ll>(k)));
        for (auto& row : g) for (ll& x : row) x = rng() % 1000;
        for (auto& pl : b) for (auto& row : pl) for (ll& x : row) x = rng() % 1000;
        StaticRangeQuery2D<ll, decltype(xr), decltype(same)> s2(g, xr, same, 0);
        StaticRangeQuery3D<ll, decltype(add), decltype(neg)> s3(b, add, neg, 0);
        for (int q = 0; q < 200; q++) {
            int r1 = rng() % (n + 1), r2 = r1 + rng() % (n - r1 + 1), c1 = rng() % (m + 1), c2 = c1 + rng() % (m - c1 + 1), z1 = rng() % (k + 1), z2 = z1 + rng() % (k - z1 + 1);
            ll x = 0, s = 0;
            for (int i = r1; i < r2; i++) for (int j = c1; j < c2; j++) x ^= g[i][j];
            for (int i = r1; i < r2; i++) for (int j = c1; j < c2; j++) for (int l = z1; l < z2; l++) s += b[i][j][l];
            CHECK(s2.query(r1, c1, r2, c2) == x);
            CHECK(s3.query(r1, c1, z1, r2, c2, z2) == s);
        }
    }
    DONE();
}
