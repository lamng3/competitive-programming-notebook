#include "../mo_2d.h"
#include "../mo_2d_hilbert_curve_ordering.h"
#include "../mo_2d_rectilinear_spanning_tree_ordering.h"
#include "../mo_2d_rollback.h"
#include "../mo_3d.h"
#include "../mo_sweepline.h"
#include "../sqrt_decomposition_heavy_point_update_light_range_query_commutative_group.h"
#include "../sqrt_decomposition_light_point_update_heavy_range_query_commutative_monoid.h"
#include "../sqrt_decomposition_light_range_update_heavy_point_query_commutative_group.h"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)
#define DONE() do { printf("\n%d checks, %d failed.\n", checks, fails); return fails ? 1 : 0; } while (0)

using ll = long long;

struct InvCounter { // rel(u, v) = u > v: counts inversions
    vector<int> cnt = vector<int>(64, 0);
    void clear() { fill(cnt.begin(), cnt.end(), 0); }
    void insert(int v) { cnt[v]++; }
    long long before(int v) { long long s = 0; for (int u = v + 1; u < 64; u++) s += cnt[u]; return s; }
    long long after(int v) { long long s = 0; for (int u = 0; u < v; u++) s += cnt[u]; return s; }
};
struct EqCounter { // rel(u, v) = u == v: counts equal pairs
    vector<int> cnt = vector<int>(64, 0);
    void clear() { fill(cnt.begin(), cnt.end(), 0); }
    void insert(int v) { cnt[v]++; }
    long long before(int v) { return cnt[v]; }
    long long after(int v) { return cnt[v]; }
};

int main() {
    mt19937 rng(9);
    for (int it = 0; it < 60; it++) {
        int n = rng() % 60 + 1, q = rng() % 60 + 1;
        vector<int> a(n);
        for (int& x : a) x = rng() % 8;
        vector<pair<int, int>> qs(q);
        for (auto& [l, r] : qs) { l = rng() % n; r = l + rng() % (n - l); }
        vector<int> cnt(8, 0);
        int distinct = 0;
        auto add = [&](int i) { if (cnt[a[i]]++ == 0) distinct++; };
        auto rem = [&](int i) { if (--cnt[a[i]] == 0) distinct--; };
        vector<int> want(q), got1(q), got2(q), got3(q);
        for (int i = 0; i < q; i++) want[i] = set<int>(a.begin() + qs[i].first, a.begin() + qs[i].second + 1).size();
        mo_2d(n, qs, add, rem, [&](int id) { got1[id] = distinct; });
        fill(cnt.begin(), cnt.end(), 0), distinct = 0;
        mo_hilbert(qs, add, rem, [&](int id) { got2[id] = distinct; });
        fill(cnt.begin(), cnt.end(), 0), distinct = 0;
        mo_mst(qs, add, rem, [&](int id) { got3[id] = distinct; });
        CHECK(got1 == want && got2 == want && got3 == want);

        // rollback Mo: window max, add-only
        int mx = -1, saved = -1;
        vector<int> got4(q, -2);
        mo_rollback(n, qs, [&](int i) { mx = max(mx, a[i]); }, [&] { saved = mx; }, [&] { mx = saved; }, [&] { mx = -1; },
                    [&](int id) { got4[id] = mx; });
        bool ok = true;
        for (int i = 0; i < q; i++) ok = ok && got4[i] == *max_element(a.begin() + qs[i].first, a.begin() + qs[i].second + 1);
        CHECK(ok);

        // sweepline Mo: inversions and equal pairs
        InvCounter ic;
        EqCounter ec;
        auto inv = mo_sweepline(a, qs, ic), eq = mo_sweepline(a, qs, ec);
        for (int i = 0; i < q; i++) {
            ll wi = 0, we = 0;
            for (int x = qs[i].first; x <= qs[i].second; x++) for (int y = x + 1; y <= qs[i].second; y++) wi += a[x] > a[y], we += a[x] == a[y];
            CHECK(inv[i] == wi && eq[i] == we);
        }
    }
    for (int it = 0; it < 30; it++) { // the MST edges give a minimum spanning tree (Prim, O(q^2), to compare)
        int q = rng() % 40 + 1;
        vector<pair<ll, ll>> p(q);
        for (auto& [x, y] : p) x = rng() % 50, y = rng() % 50;
        auto e = manhattan_mst_edges(p);
        sort(e.begin(), e.end());
        vector<int> par(q);
        iota(par.begin(), par.end(), 0);
        function<int(int)> find = [&](int v) { return par[v] == v ? v : par[v] = find(par[v]); };
        ll w = 0;
        int used = 0;
        for (auto& [c, i, j] : e) if (find(i) != find(j)) par[find(i)] = find(j), w += c, used++;
        vector<ll> d(q, LLONG_MAX);
        vector<bool> in(q, false);
        d[0] = 0;
        ll prim = 0;
        for (int s = 0; s < q; s++) {
            int u = -1;
            for (int i = 0; i < q; i++) if (!in[i] && (u < 0 || d[i] < d[u])) u = i;
            in[u] = true, prim += d[u];
            for (int i = 0; i < q; i++) d[i] = min(d[i], llabs(p[u].first - p[i].first) + llabs(p[u].second - p[i].second));
        }
        CHECK(used == q - 1 && w == prim);
    }
    for (int it = 0; it < 40; it++) { // Mo with updates: distinct count after t updates
        int n = rng() % 30 + 1, U = rng() % 20, q = rng() % 30 + 1;
        vector<int> a(n);
        for (int& x : a) x = rng() % 6;
        vector<pair<int, int>> upd(U);
        for (auto& [p, v] : upd) p = rng() % n, v = rng() % 6;
        vector<array<int, 3>> qs(q);
        for (auto& x : qs) { x[0] = rng() % n; x[1] = x[0] + rng() % (n - x[0]); x[2] = rng() % (U + 1); }
        vector<int> cur = a, cnt(6, 0), got(q);
        auto upd2 = upd; // swap-style updates
        int distinct = 0;
        auto add = [&](int i) { if (cnt[cur[i]]++ == 0) distinct++; };
        auto rem = [&](int i) { if (--cnt[cur[i]] == 0) distinct--; };
        auto flip = [&](int k, int L, int R) {
            auto& [p, v] = upd2[k];
            bool inside = L <= p && p <= R;
            if (inside) rem(p);
            swap(cur[p], v);
            if (inside) add(p);
        };
        mo_3d(n, qs, add, rem, flip, flip, [&](int id) { got[id] = distinct; });
        for (int i = 0; i < q; i++) {
            vector<int> b = a;
            for (int k = 0; k < qs[i][2]; k++) b[upd[k].first] = upd[k].second;
            CHECK(got[i] == (int)set<int>(b.begin() + qs[i][0], b.begin() + qs[i][1] + 1).size());
        }
    }
    { // the three sqrt decompositions
        auto add = [](ll x, ll y) { return x + y; };
        auto neg = [](ll x) { return -x; };
        auto mn = [](ll x, ll y) { return min(x, y); };
        for (int it = 0; it < 30; it++) {
            int n = rng() % 50 + 1;
            vector<ll> a(n);
            for (ll& x : a) x = rng() % 100;
            SqrtUpdateHeavy<ll, decltype(add), decltype(neg)> s1(a, add, neg, 0);
            SqrtQueryHeavy<ll, decltype(mn)> s2(a, mn, LLONG_MAX);
            SqrtRangeUpdate<ll, decltype(add), decltype(neg)> s3(n, add, neg, 0);
            vector<ll> b(n, 0);
            for (int q = 0; q < 300; q++) {
                int l = rng() % n, r = l + 1 + rng() % (n - l);
                ll v = rng() % 100;
                switch (rng() % 4) {
                    case 0: s1.set(l, v), s2.set(l, v), a[l] = v; break;
                    case 1: CHECK(s1.query(l, r) == accumulate(a.begin() + l, a.begin() + r, 0LL)); CHECK(s2.query(l, r) == *min_element(a.begin() + l, a.begin() + r)); break;
                    case 2: s3.update(l, r, v); for (int i = l; i < r; i++) b[i] += v; break;
                    case 3: CHECK(s3.get(l) == b[l]); break;
                }
            }
        }
    }
    DONE();
}
