// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall lazysegmenttree_test.cpp -o /tmp/lstest && /tmp/lstest
#include "../LazySegmentTree.h"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)

int main() {
    // 1) range add, range sum: the add counts once per element
    LazySegmentTree st(4, {1, 2, 3, 4});
    st.build(0, 0, 3);
    st.update(0, 0, 3, 1, 2, 10);
    CHECK(st.query(0, 0, 3, 0, 3) == 30);
    CHECK(st.query(0, 0, 3, 2, 3) == 17);
    CHECK(st.query(0, 0, 3, 1, 1) == 12);

    // 2) random against a plain array
    mt19937 rng(4);
    for (int it = 0; it < 200; it++) {
        int n = rng() % 30 + 1;
        vector<int> a(n);
        for (int& x : a) x = int(rng() % 41) - 20;
        LazySegmentTree t(n, a);
        t.build(0, 0, n-1);
        for (int q = 0; q < 80; q++) {
            int l = rng() % n, r = rng() % n;
            if (l > r) swap(l, r);
            if (rng() % 2) {
                int x = int(rng() % 41) - 20;
                t.update(0, 0, n-1, l, r, x);
                for (int i = l; i <= r; i++) a[i] += x;
            } else {
                CHECK(t.query(0, 0, n-1, l, r) == accumulate(a.begin() + l, a.begin() + r + 1, 0));
            }
        }
    }

    printf("\n%d checks, %d failed.\n", checks, fails);
    return fails ? 1 : 0;
}
