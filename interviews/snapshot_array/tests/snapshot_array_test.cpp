// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall snapshot_array_test.cpp -o /tmp/snapshot_array && /tmp/snapshot_array
#include "../solution.cpp"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)

int main() {
    mt19937 rng(1);

    // 1146: against a full copy per snap
    for (int it = 0; it < 100; it++) {
        int n = rng() % 6 + 1;
        SnapshotArray sa(n);
        vector<int> cur(n, 0);
        vector<vector<int>> snaps;
        for (int q = 0; q < 100; q++) {
            int op = rng() % 10;
            if (op < 5) { int i = rng() % n, v = rng() % 10; sa.set(i, v); cur[i] = v; }
            else if (op < 7) { CHECK(sa.snap() == (int)snaps.size()); snaps.push_back(cur); }
            else if (!snaps.empty()) { int s = rng() % snaps.size(), i = rng() % n; CHECK(sa.get(i, s) == snaps[s][i]); }
        }
    }

    printf("\n%d checks, %d failed.\n", checks, fails);
    return fails ? 1 : 0;
}
