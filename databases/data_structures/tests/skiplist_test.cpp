// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall skiplist_test.cpp -o /tmp/sltest && /tmp/sltest
#include "../skiplist.h"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)

int main() {
    // 1) basic insert + find
    SkipList sl;
    for (int i = 0; i < 50; ++i) sl.insert(i * 3, i * 100);   // keys 0,3,6,...,147
    CHECK(sl.find(0)   == 0);
    CHECK(sl.find(3)   == 100);
    CHECK(sl.find(147) == 4900);
    CHECK(sl.find(4)   == -1);    // absent key
    CHECK(sl.find(148) == -1);    // past the end

    // 2) update existing key keeps the SAME key, replaces the value
    sl.insert(3, 999);
    CHECK(sl.find(3) == 999);

    // 3) remove
    CHECK(sl.remove(3) == 1);
    CHECK(sl.find(3)   == -1);
    CHECK(sl.remove(3) == 0);     // already gone
    CHECK(sl.remove(4) == 0);     // never existed

    // 4) reverse / random insertion order, then verify all survive
    SkipList s2;
    vector<int> keys(200);
    iota(keys.begin(), keys.end(), 0);
    mt19937 rng(12345);                       // fixed seed => reproducible
    shuffle(keys.begin(), keys.end(), rng);
    for (int k : keys) s2.insert(k, k * 7);
    for (int k = 0; k < 200; ++k) CHECK(s2.find(k) == k * 7);

    // 5) remove half, confirm the rest are intact
    for (int k = 0; k < 200; k += 2) s2.remove(k);
    for (int k = 0; k < 200; ++k)
        CHECK(s2.find(k) == ((k % 2) ? k * 7 : -1));

    // 6) cross-check against std::map as ground truth (fuzz)
    SkipList s3;
    map<int,int> ref;
    for (int op = 0; op < 5000; ++op) {
        int key = rng() % 100;
        int kind = rng() % 3;
        if (kind == 0) { s3.insert(key, op); ref[key] = op; }
        else if (kind == 1) { s3.remove(key); ref.erase(key); }
        else {
            int got = s3.find(key);
            int want = ref.count(key) ? ref[key] : -1;
            CHECK(got == want);
        }
    }

    printf("\n%d checks, %d failed.\n", checks, fails);
    return fails ? 1 : 0;
}
