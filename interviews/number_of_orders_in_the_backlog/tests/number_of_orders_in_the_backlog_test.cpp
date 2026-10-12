// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall number_of_orders_in_the_backlog_test.cpp -o /tmp/number_of_orders_in_the_backlog && /tmp/number_of_orders_in_the_backlog
#include "../solution.cpp"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)

int main() {
    // 1801: the LeetCode examples
    {
        vector<vector<int>> a = {{10, 5, 0}, {15, 2, 1}, {25, 1, 1}, {30, 4, 0}};
        CHECK(Solution().getNumberOfBacklogOrders(a) == 6);
        vector<vector<int>> b = {{7, 1000000000, 1}, {15, 3, 0}, {5, 999999995, 0}, {5, 1, 1}};
        CHECK(Solution().getNumberOfBacklogOrders(b) == 999999984);
    }

    printf("\n%d checks, %d failed.\n", checks, fails);
    return fails ? 1 : 0;
}
