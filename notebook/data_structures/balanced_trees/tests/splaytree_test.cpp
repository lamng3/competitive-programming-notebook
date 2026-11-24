// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall splaytree_test.cpp -o /tmp/sttest && /tmp/sttest
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define REP(i, n) for (int i = 0; i < (n); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())
#define pb push_back
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
        vector<ll> a(rng() % 20);
        for (ll& x : a) x = ll(rng() % 21) - 10;
        SplayTree s(a);
        for (int q = 0; q < 200; q++) {
            int n = sz(a), op = rng() % 7;
            ll v = ll(rng() % 21) - 10;
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
                vector<ll> piece(a.begin() + L, a.begin() + R + 1);
                a.erase(a.begin() + L, a.begin() + R + 1);
                int i = rng() % (sz(a) + 1);
                a.insert(a.begin() + i, all(piece));
                s.paste(i, s.cut(L, R));
            }
            CHECK(s.size() == sz(a));
        }
        vector<ll> got;
        REP(i, sz(a)) got.pb(s.get(i));
        CHECK(got == a);
    }

    printf("\n%d checks, %d failed.\n", checks, fails);
    return fails ? 1 : 0;
}
