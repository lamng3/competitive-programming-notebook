// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall insert_delete_getrandom_o1_test.cpp -o /tmp/insert_delete_getrandom_o1 && /tmp/insert_delete_getrandom_o1
#include "../solution.cpp"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)

int main() {
    mt19937 rng(1);

    // 380: against std::set
    {
        RandomizedSet rs;
        set<int> ref;
        for (int it = 0; it < 3000; it++) {
            int x = rng() % 31, op = rng() % 10;
            if (op < 4) { CHECK(rs.insert(x) == !ref.count(x)); ref.insert(x); }
            else if (op < 8) { CHECK(rs.remove(x) == (bool)ref.count(x)); ref.erase(x); }
            else if (!ref.empty()) CHECK(ref.count(rs.getRandom()));
        }
    }

    printf("\n%d checks, %d failed.\n", checks, fails);
    return fails ? 1 : 0;
}
