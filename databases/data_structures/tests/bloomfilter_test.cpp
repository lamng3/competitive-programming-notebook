// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall bloomfilter_test.cpp -o /tmp/bftest && /tmp/bftest
#include "../bloomfilter.h"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)

int main() {
    // 1) empty filter contains nothing
    BloomFilter bf(1000);
    CHECK(bf.contains("apple") == false);

    // 2) added keys are always found (no false negatives)
    bf.add("apple");
    bf.add("banana");
    CHECK(bf.contains("apple")  == true);
    CHECK(bf.contains("banana") == true);

    // 3) clear wipes everything
    bf.clear();
    CHECK(bf.contains("apple")  == false);
    CHECK(bf.contains("banana") == false);

    // 4) no false negatives over many keys
    BloomFilter bf2(10000);
    vector<string> added;
    for (int i = 0; i < 500; ++i) {
        string s = "key" + to_string(i);
        bf2.add(s);
        added.push_back(s);
    }
    for (auto& s : added) CHECK(bf2.contains(s) == true);

    // 5) false-positive rate stays low for never-added keys
    int fp = 0, trials = 5000;
    for (int i = 0; i < trials; ++i) {
        string s = "absent" + to_string(i);
        if (bf2.contains(s)) ++fp;
    }
    double rate = (double)fp / trials;
    printf("false positive rate: %.4f (%d/%d)\n", rate, fp, trials);
    CHECK(rate < 0.05);

    printf("\n%d checks, %d failed.\n", checks, fails);
    return fails ? 1 : 0;
}
