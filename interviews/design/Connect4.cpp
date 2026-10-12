#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;

#define REP(i, n) for (int i = 0; i < (n); i++)
#define FOR(i, a, b) for (int i = (a); i <= (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())
#define fi first
#define se second
#define pb push_back
// Connect 4: players 1 and 2 take turns dropping a disc into a column; it falls
// to the lowest empty row. Whoever lines up k discs in a row, column, or diagonal wins.
//
// A win can only pass through the disc just dropped, so after each move check the
// 4 lines through it, counting matching discs both ways: O(k) per move, not a board scan.
class Connect4 {
    const int dr[4] = {0, 1, 1, 1}; // right, down, down-right, down-left; each line is a direction and its opposite
    const int dc[4] = {1, 0, 1, -1};

    bool inrange(int r, int c) {
        return 0 <= r && r < rows && 0 <= c && c < cols;
    }

    bool wins(int r, int c) {
        int p = board[r][c];
        REP(i, 4) {
            int run = 1;
            for (int s : {1, -1}) { // walk the line both ways from (r, c)
                int nr = r + s * dr[i], nc = c + s * dc[i];
                while (inrange(nr, nc) && board[nr][nc] == p) {
                    run++;
                    nr += s * dr[i];
                    nc += s * dc[i];
                }
            }
            if (run >= k) return true;
        }
        return false;
    }
public:
    int rows, cols, k;
    vector<vi> board; // 0 empty, else the player; row 0 is the top
    vi height;        // discs in each column
    int turn = 1, winner = 0, moves = 0;

    Connect4(int rows = 6, int cols = 7, int k = 4)
        : rows(rows), cols(cols), k(k), board(rows, vi(cols, 0)), height(cols, 0) {}

    // drop the current player's disc in col; returns the winner (1 or 2), or 0 if none yet
    int drop(int col) {
        if (winner) throw runtime_error("game over");
        if (col < 0 || col >= cols) throw runtime_error("no such column");
        if (height[col] == rows) throw runtime_error("column is full");
        int r = rows - 1 - height[col]++;
        board[r][col] = turn;
        moves++;
        if (wins(r, col)) winner = turn;
        turn = 3 - turn;
        return winner;
    }

    bool full() {
        return moves == rows * cols;
    }
};
