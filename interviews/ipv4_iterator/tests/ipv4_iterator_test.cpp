// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall ipv4_iterator_test.cpp -o /tmp/ipv4_iterator && /tmp/ipv4_iterator
#include "../solution.cpp"

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

    printf("\n%d checks, %d failed.\n", checks, fails);
    return fails ? 1 : 0;
}
