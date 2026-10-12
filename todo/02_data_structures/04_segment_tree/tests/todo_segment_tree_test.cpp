#include "../mergesort_tree.h"
#include "../mergesort_tree_point_update.h"
#include "../segment_tree_2d.h"
#include "../segment_tree_2d_sparse.h"
#include "../segment_tree_3d.h"
#include "../segment_tree_wide.h"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)
#define DONE() do { printf("\n%d checks, %d failed.\n", checks, fails); return fails ? 1 : 0; } while (0)

using ll = long long;

int main() {
    mt19937 rng(5);
    for (int it = 0; it < 60; it++) { // merge sort trees
        int n = rng() % 30 + 1;
        vector<int> a(n);
        for (int& x : a) x = rng() % 20;
        MergeSortTree<int> mt(a);
        vector<pair<int, int>> future;
        for (int q = 0; q < 50; q++) future.push_back({(int)(rng() % n), (int)(rng() % 20)});
        MergeSortTreeUpdatable<int> mu(a, future);
        vector<int> b = a;
        for (int l = 0; l < n; l++) for (int r = l + 1; r <= n; r++) {
            int k = rng() % 22;
            int want = count_if(a.begin() + l, a.begin() + r, [&](int x) { return x < k; });
            CHECK(mt.count_less(l, r, k) == want);
            vector<int> s(a.begin() + l, a.begin() + r);
            sort(s.begin(), s.end());
            int j = rng() % s.size();
            CHECK(mt.kth(l, r, j) == s[j]);
        }
        for (auto [i, v] : future) {
            mu.assign(i, v), b[i] = v;
            int l = rng() % n, r = l + 1 + rng() % (n - l), k = rng() % 22;
            CHECK(mu.count_less(l, r, k) == count_if(b.begin() + l, b.begin() + r, [&](int x) { return x < k; }));
        }
    }
    auto add = [](ll x, ll y) { return x + y; };
    auto mx = [](ll x, ll y) { return max(x, y); };
    for (int it = 0; it < 20; it++) { // 2D dense
        int n = rng() % 7 + 1, m = rng() % 7 + 1;
        SegTree2D<ll, decltype(add)> s(n, m, add, 0);
        SegTree2D<ll, decltype(mx)> x(n, m, mx, LLONG_MIN);
        vector<vector<ll>> g(n, vector<ll>(m, 0)), h(n, vector<ll>(m, LLONG_MIN));
        for (int q = 0; q < 300; q++) {
            int r = rng() % n, c = rng() % m;
            if (rng() % 2) { ll v = rng() % 100; s.set(r, c, v); x.set(r, c, v); g[r][c] = v; h[r][c] = v; }
            else {
                int r2 = r + 1 + rng() % (n - r), c2 = c + 1 + rng() % (m - c);
                ll sum = 0, best = LLONG_MIN;
                for (int i = r; i < r2; i++) for (int j = c; j < c2; j++) sum += g[i][j], best = max(best, h[i][j]);
                CHECK(s.query(r, c, r2, c2) == sum && x.query(r, c, r2, c2) == best);
            }
        }
    }
    for (int it = 0; it < 20; it++) { // 2D sparse
        vector<pair<ll, ll>> pts;
        for (int i = 0; i < 40; i++) pts.push_back({(ll)(rng() % 30) * 1000003, (ll)(rng() % 30) - 15});
        SegTree2DSparse<ll, decltype(mx)> s(pts, mx, LLONG_MIN);
        map<pair<ll, ll>, ll> val;
        for (int q = 0; q < 300; q++) {
            if (rng() % 2) { auto p = pts[rng() % pts.size()]; ll v = rng() % 1000; s.set(p.first, p.second, v); val[p] = v; }
            else {
                ll x1 = (ll)(rng() % 32) * 1000003 - 1000003, x2 = x1 + (ll)(rng() % 32) * 1000003, y1 = (ll)(rng() % 34) - 17, y2 = y1 + rng() % 34;
                ll want = LLONG_MIN;
                for (auto& [p, v] : val) if (p.first >= x1 && p.first < x2 && p.second >= y1 && p.second < y2) want = max(want, v);
                CHECK(s.query(x1, y1, x2, y2) == want);
            }
        }
    }
    { // 3D
        int n = 3, m = 4, k = 5;
        SegTree3D<ll, decltype(add)> s(n, m, k, add, 0);
        ll a[3][4][5] = {};
        for (int q = 0; q < 1000; q++) {
            int x = rng() % n, y = rng() % m, z = rng() % k;
            if (rng() % 2) { ll v = rng() % 50; s.set(x, y, z, v); a[x][y][z] = v; }
            else {
                int x2 = x + 1 + rng() % (n - x), y2 = y + 1 + rng() % (m - y), z2 = z + 1 + rng() % (k - z);
                ll want = 0;
                for (int i = x; i < x2; i++) for (int j = y; j < y2; j++) for (int l = z; l < z2; l++) want += a[i][j][l];
                CHECK(s.query(x, y, z, x2, y2, z2) == want);
            }
        }
    }
    for (int n : {1, 5, 16, 17, 255, 256, 1000}) { // wide
        WideSegTree<ll> w(n);
        vector<ll> a(n, 0);
        for (int q = 0; q < 500; q++) {
            int i = rng() % n;
            if (rng() % 2) { ll v = (ll)(rng() % 21) - 10; w.add(i, v); a[i] += v; }
            else { int j = i + rng() % (n - i + 1); CHECK(w.sum(i, j) == accumulate(a.begin() + i, a.begin() + j, 0LL)); }
        }
    }
    DONE();
}
