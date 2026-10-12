// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall interviewdesign_test.cpp -o /tmp/idtest && /tmp/idtest
#include "../Connect4.cpp"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)

int brute(const vector<vi>& b, int k) {
    int R = sz(b), C = sz(b[0]);
    int d[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
    REP(r, R) REP(c, C) if (b[r][c]) REP(i, 4) {
        bool ok = true;
        REP(s, k) {
            int a = r + s * d[i][0], e = c + s * d[i][1];
            if (a < 0 || a >= R || e < 0 || e >= C || b[a][e] != b[r][c]) { ok = false; break; }
        }
        if (ok) return b[r][c];
    }
    return 0;
}

int play(const vi& cols) {
    Connect4 g;
    int w = 0;
    for (int c : cols) w = g.drop(c);
    return w;
}

int main() {
    CHECK(play({0, 0, 1, 1, 2, 2, 3}) == 1);                // row
    CHECK(play({0, 1, 0, 1, 0, 1, 0}) == 1);                // column
    CHECK(play({0, 1, 1, 2, 2, 3, 2, 3, 3, 6, 3}) == 1);    // diagonal, rising
    CHECK(play({6, 5, 5, 4, 4, 3, 4, 3, 3, 0, 3}) == 1);    // diagonal, falling
    CHECK(play({0, 6, 1, 6, 2, 5, 6, 5, 6, 4, 6, 3}) == 2); // player 2, middle disc last

    Connect4 g;
    REP(i, 6) g.drop(0);
    bool threw = false;
    try { g.drop(0); } catch (const exception&) { threw = true; }
    CHECK(threw); // full column

    mt19937 rng(8);
    REP(it, 300) {
        int R = rng() % 5 + 3, C = rng() % 6 + 3, k = rng() % 3 + 3;
        Connect4 h(R, C, k);
        while (!h.winner && !h.full()) {
            vi open;
            REP(c, C) if (h.height[c] < R) open.pb(c);
            int w = h.drop(open[rng() % sz(open)]);
            CHECK(w == brute(h.board, k));
        }
    }

    printf("\n%d checks, %d failed.\n", checks, fails);
    return fails ? 1 : 0;
}
