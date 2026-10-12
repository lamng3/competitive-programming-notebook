"""Tests for interviews/connect_four

Run from anywhere:
    cpunit connect_four --py
or from this folder:
    python3 -m unittest -v test_connect_four
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from solution import Connect4


def brute_winner(board, k):
    R, C = len(board), len(board[0])
    for r in range(R):
        for c in range(C):
            p = board[r][c]
            if not p: continue
            for dr, dc in ((0, 1), (1, 0), (1, 1), (1, -1)):
                cells = [(r + i * dr, c + i * dc) for i in range(k)]
                if all(0 <= a < R and 0 <= b < C and board[a][b] == p for a, b in cells): return p
    return 0


class TestConnect4(unittest.TestCase):

    def play(self, cols, **kw):
        g = Connect4(**kw)
        for c in cols: w = g.drop(c)
        return g, w

    def test_lines(self):
        self.assertEqual(self.play([0, 0, 1, 1, 2, 2, 3])[1], 1)              # row
        self.assertEqual(self.play([0, 1, 0, 1, 0, 1, 0])[1], 1)              # column
        self.assertEqual(self.play([0, 1, 1, 2, 2, 3, 2, 3, 3, 6, 3])[1], 1)  # diagonal, rising
        self.assertEqual(self.play([6, 5, 5, 4, 4, 3, 4, 3, 3, 0, 3])[1], 1)  # diagonal, falling
        self.assertEqual(self.play([0, 6, 1, 6, 2, 5, 6, 5, 6, 4, 6, 3])[1], 2) # player 2, middle disc last

    def test_errors(self):
        g, _ = self.play([0, 0, 0, 0, 0, 0])
        with self.assertRaises(ValueError): g.drop(0) # full column
        with self.assertRaises(ValueError): g.drop(7)
        g, _ = self.play([0, 1, 0, 1, 0, 1, 0])
        with self.assertRaises(ValueError): g.drop(2) # game over

    def test_random_games_against_board_scan(self):
        rng = random.Random(8)
        for _ in range(300):
            R, C, k = rng.randint(3, 7), rng.randint(3, 8), rng.randint(3, 5)
            g = Connect4(R, C, k)
            while not g.winner and not g.full():
                col = rng.choice([c for c in range(C) if g.height[c] < R])
                w = g.drop(col)
                self.assertEqual(w, brute_winner(g.board, k))


if __name__ == "__main__":
    unittest.main()
