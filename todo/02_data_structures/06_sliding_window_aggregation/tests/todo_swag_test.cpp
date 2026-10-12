#include "../swag_queue.h"
#include "../swag_deque.h"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)
#define DONE() do { printf("\n%d checks, %d failed.\n", checks, fails); return fails ? 1 : 0; } while (0)

int main() {
    mt19937 rng(7);
    auto cat = [](const string& a, const string& b) { return a + b; }; // order matters
    auto mn = [](int a, int b) { return min(a, b); };
    for (int it = 0; it < 100; it++) {
        SWAGQueue<string, decltype(cat)> q(cat);
        SWAGDeque<string, decltype(cat)> d(cat);
        SWAGQueue<int, decltype(mn)> qm(mn);
        deque<string> ref, refd;
        deque<int> refm;
        for (int s = 0; s < 200; s++) {
            int op = rng() % 3;
            string x(1, 'a' + rng() % 26);
            if (op < 2 || ref.empty()) { q.push(x); ref.push_back(x); int v = rng() % 100; qm.push(v); refm.push_back(v); }
            else { q.pop(); ref.pop_front(); qm.pop(); refm.pop_front(); }
            if (!ref.empty()) {
                CHECK(q.query() == accumulate(ref.begin(), ref.end(), string()));
                CHECK(qm.query() == *min_element(refm.begin(), refm.end()));
            }
            int dop = rng() % 4;
            if (dop == 0) { d.push_front(x); refd.push_front(x); }
            else if (dop == 1 || refd.empty()) { d.push_back(x); refd.push_back(x); }
            else if (dop == 2) { d.pop_front(); refd.pop_front(); }
            else { d.pop_back(); refd.pop_back(); }
            CHECK(d.size() == refd.size());
            if (!refd.empty()) CHECK(d.query() == accumulate(refd.begin(), refd.end(), string()) && d.front() == refd.front() && d.back() == refd.back());
        }
    }
    DONE();
}
