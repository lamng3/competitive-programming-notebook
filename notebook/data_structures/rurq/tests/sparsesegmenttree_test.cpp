// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall sparsesegmenttree_test.cpp -o /tmp/ssttest && /tmp/ssttest
#include "../SparseSegmentTree.h"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)

int main() {
    // 1) a huge range, partial updates from the start
    SparseST big(1000000000);
    big.update(10, 100, 2);
    CHECK(big.query(0, 999999999) == 2 * 91);
    CHECK(big.query(0, 9) == 0);

    // 2) random range assign (values >= 0: -1 marks "no lazy") against a plain array
    mt19937 rng(11);
    for (int it = 0; it < 200; it++) {
        int n = rng() % 30 + 1;
        vector<int> a(n, 0);
        SparseST st(n);
        for (int q = 0; q < 60; q++) {
            int l = rng() % n, r = rng() % n;
            if (l > r) swap(l, r);
            if (rng() % 2) {
                int v = rng() % 6;
                st.update(l, r, v);
                for (int i = l; i <= r; i++) a[i] = v;
            } else {
                CHECK(st.query(l, r) == accumulate(a.begin() + l, a.begin() + r + 1, 0));
            }
        }
    }

    printf("\n%d checks, %d failed.\n", checks, fails);
    return fails ? 1 : 0;
}
