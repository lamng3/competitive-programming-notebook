// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall cuckoofilter_test.cpp -o /tmp/cftest && /tmp/cftest
#include "../cuckoofilter.h"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)

int main() {
    // 1) empty filter contains nothing, remove on it fails
    CuckooFilter empty(1024, 500);
    CHECK(empty.lookup("apple") == false);
    CHECK(empty.remove("apple") == false);

    // 2) inserted keys are found, light load never fails
    CuckooFilter cf(1024, 500);
    int ok = 0;
    for (int i = 0; i < 2000; ++i) ok += cf.insert("key" + to_string(i));
    CHECK(ok == 2000);
    for (int i = 0; i < 2000; ++i) CHECK(cf.lookup("key" + to_string(i)) == true);

    // 3) one bucket holds exactly 4 fingerprints, the 5th has nowhere to go
    CuckooFilter one(1, 500);
    for (int i = 0; i < 4; ++i) CHECK(one.insert("k" + to_string(i)) == true);
    CHECK(one.insert("k4") == false);

    // 4) remove frees a slot: the full bucket accepts a new key afterwards
    CHECK(one.remove("k0") == true);
    CHECK(one.insert("k4") == true);
    CHECK(one.lookup("k4") == true);

    // 5) remove makes lookup fail, other keys stay
    CuckooFilter rm(1024, 500);
    rm.insert("apple");
    rm.insert("banana");
    CHECK(rm.remove("apple") == true);
    CHECK(rm.lookup("apple") == false);
    CHECK(rm.lookup("banana") == true);
    CHECK(rm.remove("apple") == false);

    // 6) duplicates are stored separately: one remove drops only one copy
    CuckooFilter dup(1024, 500);
    dup.insert("apple");
    dup.insert("apple");
    CHECK(dup.remove("apple") == true);
    CHECK(dup.lookup("apple") == true);
    CHECK(dup.remove("apple") == true);
    CHECK(dup.lookup("apple") == false);

    // 7) one key fits in at most 2 buckets * 4 entries, so 9 copies must fail
    CuckooFilter many(1024, 500);
    int copies = 0;
    for (int i = 0; i < 9; ++i) copies += many.insert("apple");
    CHECK(copies <= 8);
    CHECK(copies >= 4);

    // 8) overfilled filter rejects inserts, and a failed insert loses nothing
    CuckooFilter small(64, 500);
    vector<string> stored;
    for (int i = 0; i < 1000; ++i) {
        string s = "item" + to_string(i);
        if (small.insert(s)) stored.push_back(s);
    }
    printf("stored %zu of 1000 in 64 buckets (capacity 256)\n", stored.size());
    CHECK(stored.size() <= 256);
    CHECK(stored.size() < 1000);
    for (auto& s : stored) CHECK(small.lookup(s) == true);

    // 9) high load: most inserts succeed, no false negatives despite failures
    CuckooFilter big(1024, 500);
    vector<string> in;
    for (int i = 0; i < 3500; ++i) {
        string s = "key" + to_string(i);
        if (big.insert(s)) in.push_back(s);
    }
    printf("stored %zu of 3500 in 1024 buckets (capacity 4096)\n", in.size());
    CHECK(in.size() > 3000);
    for (auto& s : in) CHECK(big.lookup(s) == true);

    // 10) removing half keeps the other half
    for (size_t i = 0; i < in.size(); i += 2) CHECK(big.remove(in[i]) == true);
    for (size_t i = 1; i < in.size(); i += 2) CHECK(big.lookup(in[i]) == true);

    // 11) fill rate counts used entries: 2000 of 4096 slots
    CHECK(empty.fill_rate() == 0.0);
    CHECK(fabs(cf.fill_rate() - 2000.0 / 4096) < 1e-9);
    cf.remove("key0");
    CHECK(fabs(cf.fill_rate() - 1999.0 / 4096) < 1e-9);
    cf.insert("key0");

    // 12) false-positive rate: estimate is 0 when empty, grows with fill,
    //     and the measured rate on never-added keys stays low
    CHECK(empty.false_positive_rate() == 0.0);
    CHECK(cf.false_positive_rate() > 0.0);
    CHECK(big.false_positive_rate() < cf.false_positive_rate());
    int fp = 0, trials = 20000;
    for (int i = 0; i < trials; ++i) {
        if (cf.lookup("other" + to_string(i))) ++fp;
    }
    double rate = (double)fp / trials;
    printf("fill %.3f, estimated fp %.4f, measured fp %.4f (%d/%d)\n",
           cf.fill_rate(), cf.false_positive_rate(), rate, fp, trials);
    CHECK(rate < 0.05);

    printf("\n%d checks, %d failed.\n", checks, fails);
    return fails ? 1 : 0;
}
