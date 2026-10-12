// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall infection_simulation_test.cpp -o /tmp/infection_simulation && /tmp/infection_simulation
#include "../solution.cpp"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)

int main() {
    // infection
    CHECK(lastRecoveryDay({"X..", "...", "..."}, 2) == 6);
    CHECK(lastRecoveryDay({"X#.", ".#.", "..#"}, 3) == 6);
    CHECK(lastRecoveryDay({"...", ".#."}, 5) == 0);

    printf("\n%d checks, %d failed.\n", checks, fails);
    return fails ? 1 : 0;
}
