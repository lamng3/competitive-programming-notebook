// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall srd_test.cpp -o /tmp/srdtest && /tmp/srdtest
#include "../SRD.h"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)

int main() {
    // random point sets and half-open sums against a plain array
    mt19937 rng(3);
    for (int it = 0; it < 200; it++) {
        int n = rng() % 40 + 1;
        int b = 1;
        while (b * b < n) b++;
        vector<long long> a(n);
        for (auto& x : a) x = (long long)(rng() % 101) - 50;
        SRD<long long> s(b, a);
        for (int q = 0; q < 60; q++) {
            if (rng() % 2) {
                int x = rng() % n;
                long long v = (long long)(rng() % 101) - 50;
                s.update(x, v);
                a[x] = v;
            } else {
                int l = rng() % (n + 1), r = l + rng() % (n - l + 1);
                CHECK(s.query(l, r) == accumulate(a.begin() + l, a.begin() + r, 0LL));
            }
        }
    }

    printf("\n%d checks, %d failed.\n", checks, fails);
    return fails ? 1 : 0;
}
