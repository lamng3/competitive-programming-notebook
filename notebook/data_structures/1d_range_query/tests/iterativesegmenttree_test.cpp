// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall iterativesegmenttree_test.cpp -o /tmp/isttest && /tmp/isttest
#include "../IterativeSegmentTree.h"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)

int main() {
    // random point updates and half-open sums against a plain array
    mt19937 rng(2);
    for (int it = 0; it < 200; it++) {
        int n = rng() % 40 + 1;
        vector<int> a(n);
        IterativeSegmentTree<int> st;
        st.n = n;
        for (int i = 0; i < n; i++) tree[n + i] = a[i] = int(rng() % 101) - 50;
        st.build();
        for (int q = 0; q < 60; q++) {
            if (rng() % 2) {
                int p = rng() % n, v = int(rng() % 101) - 50;
                st.update(p, v);
                a[p] = v;
            } else {
                int l = rng() % (n + 1), r = l + rng() % (n - l + 1);
                CHECK(st.query(l, r) == accumulate(a.begin() + l, a.begin() + r, 0));
            }
        }
    }

    printf("\n%d checks, %d failed.\n", checks, fails);
    return fails ? 1 : 0;
}
