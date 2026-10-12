// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall todo_searching_test.cpp -o /tmp/t && /tmp/t
#include "../binary_geometric_sum.h"
#include "../binary_geometric_sum_general.h"
#include "../binary_power_general.h"
#include "../binary_string.h"
#include "../continuous_binary_search.h"
#include "../counting_iterator.h"
#include "../discrete_golden_section_search.h"
#include "../discrete_ternary_search.h"
#include "../double_parallel_binary_search.h"
#include "../find_prefix_xor_order.h"
#include "../fractional_search.h"
#include "../golden_section_search.h"
#include "../parallel_binary_search.h"
#include "../solve_cubic_equation.h"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)

struct M2 { // 2x2 matrix mod 1e9+7, for the general geometric sum
    long long a[2][2];
    M2 operator*(const M2& o) const {
        M2 r{};
        for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) for (int k = 0; k < 2; k++)
            r.a[i][j] = (r.a[i][j] + a[i][k] * o.a[k][j]) % 1000000007;
        return r;
    }
    M2 operator+(const M2& o) const {
        M2 r{};
        for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) r.a[i][j] = (a[i][j] + o.a[i][j]) % 1000000007;
        return r;
    }
};

int main() {
    mt19937_64 rng(1);

    // geometric sums, against a loop, including composite moduli and a = 1
    for (int it = 0; it < 500; it++) {
        long long m = rng() % 1000 + 1, a = rng() % 2000, n = rng() % 60;
        long long want = 0, p = 1 % m;
        for (int i = 0; i < n; i++) want = (want + p) % m, p = p * (a % m) % m;
        CHECK(geo_sum(a, n, m) == want);
    }
    { // general: sum of the first n Fibonacci matrices
        M2 F{{{1, 1}, {1, 0}}}, Z{{{0, 0}, {0, 0}}}, I{{{1, 0}, {0, 1}}};
        vector<long long> fib = {0, 1};
        for (int i = 2; i < 60; i++) fib.push_back((fib[i - 1] + fib[i - 2]) % 1000000007);
        for (int n = 0; n < 50; n++) {
            long long want = 0;
            for (int i = 0; i < n; i++) want = (want + fib[i]) % 1000000007; // F^i[0][1] = fib(i)
            CHECK(geo_sum_general(F, n, Z, I).a[0][1] == want);
        }
    }
    { // power of a permutation by composition
        vector<int> perm = {2, 0, 3, 1, 4}, id = {0, 1, 2, 3, 4};
        auto comp = [](const vector<int>& x, const vector<int>& y) { vector<int> r(5); for (int i = 0; i < 5; i++) r[i] = x[y[i]]; return r; };
        vector<int> slow = id;
        for (int e = 0; e < 30; e++) {
            CHECK(power_general(perm, e, id, comp) == slow);
            slow = comp(slow, perm);
        }
    }
    { // binary strings and submasks
        CHECK(to_binary(5, 4) == "0101" && from_binary("0101") == 5 && from_binary(to_binary(1234567, 40)) == 1234567);
        int total = 0;
        for (int m = 0; m < (1 << 8); m++) for_each_submask(m, [&](int) { total++; });
        CHECK(total == 6561); // 3^8
    }
    CHECK(fabs(first_true_real(0, 10, [](double x) { return x * x >= 2; }) - sqrt(2.0)) < 1e-9);
    { // counting iterator with partition_point
        for (long long t = -5; t < 50; t++) {
            auto it = partition_point(counting_iterator(0), counting_iterator(40), [&](long long x) { return x * x < t; });
            long long want = 0;
            while (want < 40 && want * want < t) want++;
            CHECK(*it == want);
        }
    }
    // unimodal maxima, discrete: random peaks
    for (int it = 0; it < 2000; it++) {
        long long n = rng() % 200 + 1, peak = rng() % n;
        auto f = [&](long long x) { return -(x - peak) * (x - peak) * 3 + (long long)(x < peak ? x : 0); };
        long long brute = 0;
        for (long long x = 1; x < n; x++) if (f(x) > f(brute)) brute = x;
        CHECK(f(ternary_max_int(0, n - 1, f)) == f(brute));
        CHECK(f(golden_max_int(0, n - 1, f)) == f(brute));
        long long lo = rng() % 50;
        auto g = [&](long long x) { return -llabs(x - (lo + peak)); };
        CHECK(golden_max_int(lo, lo + n - 1, g) == lo + peak);
    }
    CHECK(fabs(golden_max(-5, 5, [](double x) { return -(x - 1.234) * (x - 1.234); }) - 1.234) < 1e-7);

    { // parallel binary search: points arrive over time; when does each query's count reach its target?
        int T = 200, Q = 100;
        vector<int> pts(T), qx(Q), need(Q);
        for (auto& p : pts) p = rng() % 50;
        for (int i = 0; i < Q; i++) qx[i] = rng() % 50, need[i] = rng() % 8;
        vector<int> cnt(50);
        auto ans = parallel_binary_search(Q, T, [&] { fill(cnt.begin(), cnt.end(), 0); },
                                          [&](int t) { cnt[pts[t]]++; },
                                          [&](int q) { return cnt[qx[q]] >= need[q]; });
        for (int q = 0; q < Q; q++) {
            int c = 0, want = need[q] == 0 ? 0 : T + 1;
            for (int t = 0; t < T && want == T + 1; t++) if (pts[t] == qx[q] && ++c >= need[q]) want = t + 1;
            CHECK(ans[q] == want);
        }
        // the real-valued version: the first time a linearly growing value reaches each target
        vector<double> target(Q);
        for (auto& x : target) x = (rng() % 100000) / 1000.0;
        double now = 0;
        auto res = parallel_binary_search_real(Q, 0, 100, 60, [&] { now = 0; }, [&](double t) { now = t; },
                                               [&](int q) { return 2 * now >= target[q]; });
        for (int q = 0; q < Q; q++) CHECK(fabs(res[q] - target[q] / 2) < 1e-9);
    }
    { // xor trie against sorting
        for (int it = 0; it < 50; it++) {
            XorTrie tr;
            vector<int> v(rng() % 60 + 1);
            for (auto& x : v) { x = rng() % 1000; tr.insert(x); }
            int x = rng() % 1000, bound = rng() % 1100;
            vector<int> w;
            for (int y : v) w.push_back(y ^ x);
            sort(w.begin(), w.end());
            for (int k = 0; k < (int)w.size(); k++) CHECK(tr.kth(x, k) == w[k]);
            CHECK(tr.count_less(x, bound) == lower_bound(w.begin(), w.end(), bound) - w.begin());
        }
    }
    // fractional search against brute force over all fractions with terms <= N
    for (int it = 0; it < 300; it++) {
        long long N = rng() % 40 + 1, a = rng() % 120, b = rng() % 40 + 1; // threshold a / b
        bool strict = rng() % 2;
        auto pred = [&](long long p, long long q) { return strict ? p * b > a * q : p * b >= a * q; };
        if (!pred(N, 1)) continue;
        long long bp = N, bq = 1;
        for (long long q = 1; q <= N; q++) for (long long p = 0; p <= N; p++)
            if (pred(p, q) && p * bq < bp * q) bp = p, bq = q;
        long long g = gcd(bp, bq);
        auto [p, q] = smallest_fraction(N, pred);
        CHECK(p == bp / g && q == bq / g);
    }
    // cubic roots: build from known roots
    for (int it = 0; it < 500; it++) {
        double r1 = (int)(rng() % 21) - 10, r2 = (int)(rng() % 21) - 10, r3 = (int)(rng() % 21) - 10, k = (int)(rng() % 5) + 1;
        auto xs = solve_cubic(k, -k * (r1 + r2 + r3), k * (r1 * r2 + r2 * r3 + r1 * r3), -k * r1 * r2 * r3);
        set<double> want = {r1, r2, r3};
        bool ok = xs.size() == want.size();
        int i = 0;
        for (double w : want) ok = ok && fabs(xs[i++] - w) < 1e-6;
        CHECK(ok);
    }
    { // one real root: x^3 + x + 1
        auto xs = solve_cubic(1, 0, 1, 1);
        CHECK(xs.size() == 1 && fabs(xs[0] * xs[0] * xs[0] + xs[0] + 1) < 1e-9);
    }

    printf("\n%d checks, %d failed.\n", checks, fails);
    return fails ? 1 : 0;
}
