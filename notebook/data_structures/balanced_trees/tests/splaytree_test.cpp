// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall splaytree_test.cpp -o /tmp/sttest && /tmp/sttest
#include "../SplayTree.h"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)

int main() {
    // 1) by hand
    SplayTree t({1, 2, 3, 4, 5});
    t.reverse(1, 3);              // 1 4 3 2 5
    CHECK(t.get(1) == 4 && t.get(3) == 2);
    CHECK(t.query(0, 2) == 8);
    t.insert(0, 10);              // 10 1 4 3 2 5
    t.erase(5);                   // 10 1 4 3 2
    CHECK(t.size() == 5 && t.query(0, 4) == 20);
    t.paste(0, t.cut(3, 4));      // 3 2 10 1 4
    CHECK(t.get(0) == 3 && t.get(1) == 2 && t.get(2) == 10);
    t.assign(4, -6);              // 3 2 10 1 -6
    CHECK(t.query(3, 4) == -5);

    // 2) random operations against a vector, starting from empty and nonempty sequences
    mt19937 rng(7);
    for (int it = 0; it < 300; it++) {
        vector<long long> a(rng() % 20);
        for (long long& x : a) x = (long long)(rng() % 21) - 10;
        SplayTree s(a);
        for (int q = 0; q < 200; q++) {
            int n = (int)a.size(), op = rng() % 7;
            long long v = (long long)(rng() % 21) - 10;
            if (op == 0) {
                int i = rng() % (n + 1);
                s.insert(i, v);
                a.insert(a.begin() + i, v);
                continue;
            }
            if (n == 0) continue;
            int L = rng() % n, R = rng() % n;
            if (L > R) swap(L, R);
            if (op == 1) {
                s.erase(L);
                a.erase(a.begin() + L);
            }
            else if (op == 2) {
                s.reverse(L, R);
                reverse(a.begin() + L, a.begin() + R + 1);
            }
            else if (op == 3) {
                CHECK(s.query(L, R) == accumulate(a.begin() + L, a.begin() + R + 1, 0LL));
            }
            else if (op == 4) {
                s.assign(L, v);
                a[L] = v;
            }
            else if (op == 5) {
                CHECK(s.get(L) == a[L]);
            }
            else {
                vector<long long> piece(a.begin() + L, a.begin() + R + 1);
                a.erase(a.begin() + L, a.begin() + R + 1);
                int i = rng() % (a.size() + 1);
                a.insert(a.begin() + i, piece.begin(), piece.end());
                s.paste(i, s.cut(L, R));
            }
            CHECK(s.size() == (int)a.size());
        }
        vector<long long> got;
        for (int i = 0; i < (int)a.size(); i++) got.push_back(s.get(i));
        CHECK(got == a);
    }

    printf("\n%d checks, %d failed.\n", checks, fails);
    return fails ? 1 : 0;
}
