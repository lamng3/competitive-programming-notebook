// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall interviewleetcode_test.cpp -o /tmp/iltest && /tmp/iltest
// Each solution sits in its own namespace: several are all called Solution.
#include <bits/stdc++.h>
namespace p362 {
#include "../362.cpp"
}
namespace p380 {
#include "../380.cpp"
}
namespace p460 {
#include "../460.cpp"
}
namespace p68 {
#include "../68.cpp"
}
namespace p347 {
#include "../347.cpp"
}
namespace p1801 {
#include "../1801.cpp"
}
namespace p1146 {
#include "../1146.cpp"
}
using namespace std;

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
        p362::HitCounter hc;
        vector<int> hits;
        int t = 1;
        for (int it = 0; it < 2000; it++) {
            int steps[] = {0, 0, 1, 7, 150, 400};
            t += steps[rng() % 6];
            if (rng() % 10 < 6) { hc.hit(t); hits.push_back(t); }
            else CHECK(hc.getHits(t) == (int)count_if(hits.begin(), hits.end(), [&](int h) { return h > t - 300; }));
        }
    }

    // 380: against std::set
    {
        p380::RandomizedSet rs;
        set<int> ref;
        for (int it = 0; it < 3000; it++) {
            int x = rng() % 31, op = rng() % 10;
            if (op < 4) { CHECK(rs.insert(x) == !ref.count(x)); ref.insert(x); }
            else if (op < 8) { CHECK(rs.remove(x) == (bool)ref.count(x)); ref.erase(x); }
            else if (!ref.empty()) CHECK(ref.count(rs.getRandom()));
        }
    }

    // 460: against a brute-force LFU (value, freq, last use)
    for (int it = 0; it < 200; it++) {
        int cap = rng() % 5, clock = 0;
        p460::LFUCache lfu(cap);
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

    // 68: the LeetCode examples
    {
        vector<string> w1 = {"This", "is", "an", "example", "of", "text", "justification."};
        CHECK(p68::Solution().fullJustify(w1, 16) == vector<string>({"This    is    an", "example  of text", "justification.  "}));
        vector<string> w2 = {"What", "must", "be", "acknowledgment", "shall", "be"};
        CHECK(p68::Solution().fullJustify(w2, 16) == vector<string>({"What   must   be", "acknowledgment  ", "shall be        "}));
    }

    // 347: the frequencies returned are the k largest
    for (int it = 0; it < 200; it++) {
        int n = rng() % 30 + 1;
        vector<int> nums(n);
        map<int, int> cnt;
        for (int& x : nums) cnt[x = rng() % 9]++;
        int k = rng() % cnt.size() + 1;
        vector<int> got = p347::Solution().topKFrequent(nums, k), gf, all;
        for (int x : got) gf.push_back(cnt[x]);
        for (auto& [x, f] : cnt) all.push_back(f);
        sort(gf.rbegin(), gf.rend());
        sort(all.rbegin(), all.rend());
        all.resize(k);
        CHECK((int)set<int>(got.begin(), got.end()).size() == k && gf == all);
    }

    // 1801: the LeetCode examples
    {
        vector<vector<int>> a = {{10, 5, 0}, {15, 2, 1}, {25, 1, 1}, {30, 4, 0}};
        CHECK(p1801::Solution().getNumberOfBacklogOrders(a) == 6);
        vector<vector<int>> b = {{7, 1000000000, 1}, {15, 3, 0}, {5, 999999995, 0}, {5, 1, 1}};
        CHECK(p1801::Solution().getNumberOfBacklogOrders(b) == 999999984);
    }

    // 1146: against a full copy per snap
    for (int it = 0; it < 100; it++) {
        int n = rng() % 6 + 1;
        p1146::SnapshotArray sa(n);
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
