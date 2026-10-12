// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall design_hit_counter_test.cpp -o /tmp/design_hit_counter && /tmp/design_hit_counter
#include "../solution.cpp"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)

int main() {
    mt19937 rng(1);

    // 362: hits in the last 300 seconds, against a list of every hit
    {
        HitCounter hc;
        vector<int> hits;
        int t = 1;
        for (int it = 0; it < 2000; it++) {
            int steps[] = {0, 0, 1, 7, 150, 400};
            t += steps[rng() % 6];
            if (rng() % 10 < 6) { hc.hit(t); hits.push_back(t); }
            else CHECK(hc.getHits(t) == (int)count_if(hits.begin(), hits.end(), [&](int h) { return h > t - 300; }));
        }
    }

    printf("\n%d checks, %d failed.\n", checks, fails);
    return fails ? 1 : 0;
}
