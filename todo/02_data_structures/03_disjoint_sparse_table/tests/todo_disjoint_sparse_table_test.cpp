#include "../disjoint_sparse_table.h"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)
#define DONE() do { printf("\n%d checks, %d failed.\n", checks, fails); return fails ? 1 : 0; } while (0)

int main() {
    mt19937 rng(4);
    auto cat = [](const string& x, const string& y) { return x + y; }; // associative, not commutative
    auto add = [](long long x, long long y) { return x + y; };
    for (int it = 0; it < 100; it++) {
        int n = rng() % 40 + 1;
        vector<string> a(n);
        vector<long long> b(n);
        for (int i = 0; i < n; i++) a[i] = string(1, 'a' + rng() % 26), b[i] = (long long)(rng() % 100) - 50;
        DisjointSparseTable<string, decltype(cat)> ds(a, cat);
        DisjointSparseTable<long long, decltype(add)> db(b, add);
        for (int l = 0; l < n; l++) for (int r = l; r < n; r++) {
            string want;
            long long s = 0;
            for (int i = l; i <= r; i++) want += a[i], s += b[i];
            CHECK(ds.query(l, r) == want && db.query(l, r) == s);
        }
    }
    DONE();
}
