# Connect 4: players 1 and 2 take turns dropping a disc into a column; it falls
# to the lowest empty row. Whoever lines up k discs in a row, column, or diagonal wins.
#
# A win can only pass through the disc just dropped, so after each move check the
# 4 lines through it, counting matching discs both ways: O(k) per move, not a board scan.

dr = [0, 1, 1, 1] # right, down, down-right, down-left; each line is a direction and its opposite
dc = [1, 0, 1, -1]


class Connect4:

    def __init__(self, rows: int = 6, cols: int = 7, k: int = 4):
        self.rows, self.cols, self.k = rows, cols, k
        self.board = [[0] * cols for _ in range(rows)] # 0 empty, else the player
        self.height = [0] * cols # discs in each column
        self.turn = 1
        self.winner = 0
        self.moves = 0

    def inrange(self, r: int, c: int) -> bool:
        return 0 <= r and r < self.rows and 0 <= c and c < self.cols

    # drop the current player's disc in col; returns the winner (1 or 2), or 0 if none yet
    def drop(self, col: int) -> int:
        if self.winner: raise ValueError("game over")
        if not 0 <= col < self.cols: raise ValueError("no such column")
        if self.height[col] == self.rows: raise ValueError("column is full")
        r = self.rows - 1 - self.height[col] # row 0 is the top
        self.height[col] += 1
        self.board[r][col] = self.turn
        self.moves += 1
        if self._wins(r, col): self.winner = self.turn
        self.turn = 3 - self.turn
        return self.winner

    def full(self) -> bool:
        return self.moves == self.rows * self.cols

    def _wins(self, r: int, c: int) -> bool:
        p = self.board[r][c]
        for i in range(4):
            run = 1
            for s in (1, -1): # walk the line both ways from (r, c)
                nr, nc = r + s * dr[i], c + s * dc[i]
                while self.inrange(nr, nc) and self.board[nr][nc] == p:
                    run += 1
                    nr, nc = nr + s * dr[i], nc + s * dc[i]
            if run >= self.k: return True
        return False
