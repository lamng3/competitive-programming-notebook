// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall interviewpractical_test.cpp -o /tmp/iptest && /tmp/iptest
#include "../ChangeDirectory.cpp"
#include "../IPv4Iterator.cpp"
#include "../InfectionSimulation.cpp"
#include "../TreeMessages.cpp"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)

vector<string> walk(IPv4Iterator it) {
    vector<string> out;
    while (it.hasNext()) out.pb(it.next());
    return out;
}

int main() {
    // cd
    unordered_map<string, string> links = {{"/home/bugs/lola", "/home/lola"}, {"/a", "/b"}, {"/b", "/c"}, {"/c", "/a"},
                                           {"/x/y", "/z"}, {"/p", "/q"}, {"/q", "/r/s"}};
    CHECK(ChangeDirectory::cd("/home/bugs", ".") == "/home/bugs");
    CHECK(ChangeDirectory::cd("/home/bugs", "../daffy") == "/home/daffy");
    CHECK(ChangeDirectory::cd("/", "../../x") == "/x");
    CHECK(ChangeDirectory::cd("/a/b", "") == "/a/b");
    CHECK(ChangeDirectory::cd("/home/bugs", "lola/../basketball", links) == "/home/basketball");
    CHECK(ChangeDirectory::cd("/x", "y/file", links) == "/z/file");
    CHECK(ChangeDirectory::cd("/", "p/t", links) == "/r/s/t");
    bool loop = false;
    try { ChangeDirectory::cd("/", "a", links); } catch (const exception&) { loop = true; }
    CHECK(loop);

    // IPv4
    CHECK(walk(IPv4Iterator("255.255.14.254", "255.255.15.1")) == vector<string>({"255.255.14.254", "255.255.14.255", "255.255.15.0", "255.255.15.1"}));
    CHECK(walk(IPv4Iterator("0.0.1.1", "0.0.0.255")) == vector<string>({"0.0.1.1", "0.0.1.0", "0.0.0.255"}));
    CHECK(walk(IPv4Iterator("255.255.255.255", "255.255.255.255")) == vector<string>({"255.255.255.255"}));
    CHECK(walk(IPv4Iterator::fromCidr("192.168.1.0/30")) == vector<string>({"192.168.1.0", "192.168.1.1", "192.168.1.2", "192.168.1.3"}));
    CHECK(walk(IPv4Iterator::fromCidr("192.168.1.2/31", false)) == vector<string>({"192.168.1.3", "192.168.1.2"}));
    CHECK(IPv4Iterator::cidrRange("1.2.3.4/0") == make_pair(0LL, (1LL << 32) - 1));
    for (string bad : {"1.2.3", "1.2.3.256", "a.b.c.d", "1.2.3.4.5", "1..2.3"}) {
        bool threw = false;
        try { IPv4Iterator::toInt(bad); } catch (const exception&) { threw = true; }
        CHECK(threw);
    }

    // infection
    CHECK(lastRecoveryDay({"X..", "...", "..."}, 2) == 6);
    CHECK(lastRecoveryDay({"X#.", ".#.", "..#"}, 3) == 6);
    CHECK(lastRecoveryDay({"...", ".#."}, 5) == 0);

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
