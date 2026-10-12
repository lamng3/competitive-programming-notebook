// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall tree_messages_test.cpp -o /tmp/tree_messages && /tmp/tree_messages
#include "../solution.cpp"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)

int main() {
    // tree messages over a lossy network that also duplicates
    mt19937 rng(11);
    REP(it, 100) {
        int n = rng() % 40 + 1;
        vi par(n, -1);
        vector<vi> kids(n);
        for (int v = 1; v < n; v++) kids[par[v] = rng() % v].pb(v);
        deque<tuple<int, int, string>> q;
        auto send = [&](int to, int from, const string& msg) {
            int r = rng() % 10;
            if (r < 3) throw runtime_error("dropped");
            q.push_back({to, from, msg});
            if (r < 5) throw runtime_error("delivered, but the ack was lost");
        };
        vector<Node> nodes;
        REP(v, n) nodes.emplace_back(v, par[v], kids[v], send, [](double) {}, 50);
        nodes[0].start();
        while (!q.empty()) {
            swap(q.front(), q[rng() % sz(q)]); // deliver in any order
            auto [to, from, msg] = q.front();
            q.pop_front();
            nodes[to].receive(from, msg);
        }
        CHECK(nodes[0].result == n);
    }
    {
        int calls = 0;
        vector<double> waits;
        Node node(1, 0, {}, [&](int, int, const string&) { if (++calls < 3) throw runtime_error("x"); },
                  [&](double s) { waits.pb(s); }, 5, 1);
        CHECK(node.sendWithRetry(0, "1"));
        CHECK(calls == 3 && waits == vector<double>({1, 2})); // stop at the first success
    }

    printf("\n%d checks, %d failed.\n", checks, fails);
    return fails ? 1 : 0;
}
