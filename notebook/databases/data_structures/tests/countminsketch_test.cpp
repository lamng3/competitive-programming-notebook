// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall countminsketch_test.cpp -o /tmp/cmstest && /tmp/cmstest
#include "../countminsketch.h"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)

// True when every row sends the demo keys to different columns,
// and the seed changes the bucket of keys[0].
bool separable(const vector<string>& keys, const vector<uint64_t>& seeds, int width) {
    int first = hashWithSeed(keys[0], seeds[0], width);
    bool seedMoves = false;
    for (int r = 0; r < (int)seeds.size(); r++) {
        if (hashWithSeed(keys[0], seeds[r], width) != first) seedMoves = true;
        set<int> cols;
        for (auto& k : keys) {
            int c = hashWithSeed(k, seeds[r], width);
            if (c < 0 || c >= width || !cols.insert(c).second) return false;
        }
    }
    return seedMoves;
}

int main() {
    const int W = 64, D = 4;
    vector<string> keys = {"apple", "banana", "cherry"};
    vector<int> freq = {5, 2, 1};
    vector<uint64_t> seeds;
    for (int attempt = 1; attempt <= 10000 && seeds.empty(); attempt++) {
        vector<uint64_t> cand(D);
        for (int r = 0; r < D; r++) cand[r] = (uint64_t)attempt * 1000003ULL + (uint64_t)r * 97ULL + 1;
        if (separable(keys, cand, W)) seeds = cand;
    }
    CHECK(!seeds.empty());

    CountMinSketch<string> cms(W, D, seeds);
    for (int i = 0; i < (int)keys.size(); i++)
        for (int t = 0; t < freq[i]; t++) cms.insert(keys[i]);

    printf("counts:");
    for (int i = 0; i < (int)keys.size(); i++) {
        int est = cms.count(keys[i]);
        printf(" %s=%d", keys[i].c_str(), est);
        CHECK(est == freq[i]);
    }
    printf("\n");
    CHECK(cms.count(string("missing")) == 0);

    CountMinSketch<string> other(W, D, seeds);
    for (int t = 0; t < 3; t++) other.insert(string("apple"));
    CountMinSketch<string>* merged = cms.merge(&other);
    CHECK(merged != nullptr);
    CHECK(merged->count(string("apple")) == 8);
    CHECK(merged->count(string("banana")) == 2);
    CHECK(merged->count(string("cherry")) == 1);
    printf("merged apple=%d banana=%d cherry=%d\n",
           merged->count(string("apple")), merged->count(string("banana")), merged->count(string("cherry")));

    vector<string> top = merged->topK(2, keys);
    printf("top2:");
    for (auto& s : top) printf(" %s", s.c_str());
    printf("\n");
    CHECK(top.size() == 2);
    CHECK(top[0] == "apple");
    CHECK(top[1] == "banana");

    CountMinSketch<string> different(W, D, {9, 8, 7, 6});
    CHECK(cms.merge(&different) == nullptr);

    cms.clear();
    CHECK(cms.count(string("apple")) == 0);
    cms.insert(string("apple"));
    CHECK(cms.count(string("apple")) == 1);

    // Tight table: counters collide, but an estimate never drops below the truth.
    CountMinSketch<int> tight(4, 3, {7, 11, 13});
    vector<int> truth(20, 0);
    for (int i = 0; i < 100; i++) {
        int x = i % 20;
        tight.insert(x);
        truth[x]++;
    }
    for (int x = 0; x < 20; x++) CHECK(tight.count(x) >= truth[x]);

    delete merged;
    printf("\n%d checks, %d failed.\n", checks, fails);
    return fails ? 1 : 0;
}
