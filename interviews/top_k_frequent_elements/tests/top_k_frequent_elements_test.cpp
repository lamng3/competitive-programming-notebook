// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall top_k_frequent_elements_test.cpp -o /tmp/top_k_frequent_elements && /tmp/top_k_frequent_elements
#include "../solution.cpp"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)

int main() {
    mt19937 rng(1);

    // 347: the frequencies returned are the k largest
    for (int it = 0; it < 200; it++) {
        int n = rng() % 30 + 1;
        vector<int> nums(n);
        map<int, int> cnt;
        for (int& x : nums) cnt[x = rng() % 9]++;
        int k = rng() % cnt.size() + 1;
        vector<int> got = Solution().topKFrequent(nums, k), gf, all;
        for (int x : got) gf.push_back(cnt[x]);
        for (auto& [x, f] : cnt) all.push_back(f);
        sort(gf.rbegin(), gf.rend());
        sort(all.rbegin(), all.rend());
        all.resize(k);
        CHECK((int)set<int>(got.begin(), got.end()).size() == k && gf == all);
    }

    printf("\n%d checks, %d failed.\n", checks, fails);
    return fails ? 1 : 0;
}
