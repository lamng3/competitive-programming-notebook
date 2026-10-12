// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall lfu_cache_test.cpp -o /tmp/lfu_cache && /tmp/lfu_cache
#include "../solution.cpp"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)

int main() {
    mt19937 rng(1);

    // 460: against a brute-force LFU (value, freq, last use)
    for (int it = 0; it < 200; it++) {
        int cap = rng() % 5, clock = 0;
        LFUCache lfu(cap);
        map<int, array<int, 3>> ref;
        for (int q = 0; q < 80; q++) {
            clock++;
            int k = rng() % 7;
            if (rng() % 2) {
                int want = -1;
                if (ref.count(k)) { ref[k][1]++; ref[k][2] = clock; want = ref[k][0]; }
                CHECK(lfu.get(k) == want);
            } else {
                int v = rng() % 100;
                lfu.put(k, v);
                if (cap == 0) continue;
                if (ref.count(k)) ref[k] = {v, ref[k][1] + 1, clock};
                else {
                    if ((int)ref.size() == cap) {
                        auto victim = min_element(ref.begin(), ref.end(), [](auto& a, auto& b) {
                            return make_pair(a.second[1], a.second[2]) < make_pair(b.second[1], b.second[2]);
                        });
                        ref.erase(victim);
                    }
                    ref[k] = {v, 1, clock};
                }
            }
        }
    }

    printf("\n%d checks, %d failed.\n", checks, fails);
    return fails ? 1 : 0;
}
