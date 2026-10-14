"""Tests for python/databases/data_structures/QuadTree.py

Run from anywhere:
    cpunit quadtree --py
or from this folder:
    python3 -m unittest -v test_quadtree

Expected interface:
    QuadTree(grid)                 grid is a non-empty list of equal-length rows of numbers
    update(r, c, v)                set cell (r, c) to v
    query(r0, c0, r1, c1) -> sum   sum of the inclusive rectangle [r0..r1] x [c0..c1]
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from QuadTree import QuadTree


def brute(g, r0, c0, r1, c1):
    return sum(g[r][c] for r in range(r0, r1 + 1) for c in range(c0, c1 + 1))


class TestQuadTree(unittest.TestCase):

    def test_single_cell(self):
        qt = QuadTree([[7]])
        self.assertEqual(qt.query(0, 0, 0, 0), 7)
        qt.update(0, 0, -3)
        self.assertEqual(qt.query(0, 0, 0, 0), -3)

    def test_small_grid(self):
        g = [[1, 2, 3],
             [4, 5, 6]]
        qt = QuadTree(g)
        self.assertEqual(qt.query(0, 0, 1, 2), 21)
        self.assertEqual(qt.query(0, 1, 1, 2), 16)
        self.assertEqual(qt.query(1, 0, 1, 0), 4)
        qt.update(1, 1, 0)
        self.assertEqual(qt.query(0, 0, 1, 2), 16)

    def test_single_row_and_single_column(self):
        row = QuadTree([[1, 2, 3, 4, 5]])
        self.assertEqual(row.query(0, 1, 0, 3), 9)
        col = QuadTree([[1], [2], [3], [4], [5]])
        self.assertEqual(col.query(1, 0, 3, 0), 9)

    def test_update_with_zero_and_query_outside(self):
        qt = QuadTree([[1, 1], [1, 1]])
        qt.update(0, 0, 0)
        self.assertEqual(qt.query(0, 0, 0, 0), 0)
        self.assertEqual(qt.query(0, 0, 1, 1), 3)
        qt.update(5, 5, 100)  # outside the grid: ignored
        self.assertEqual(qt.query(0, 0, 1, 1), 3)

    def test_random_against_brute_force(self):
        rng = random.Random(2026)
        for _ in range(50):
            n, m = rng.randint(1, 9), rng.randint(1, 9)
            g = [[rng.randint(-10, 10) for _ in range(m)] for _ in range(n)]
            qt = QuadTree([row[:] for row in g])
            for _ in range(100):
                if rng.random() < 0.4:
                    r, c, v = rng.randrange(n), rng.randrange(m), rng.randint(-10, 10)
                    g[r][c] = v
                    qt.update(r, c, v)
                else:
                    r0, r1 = sorted(rng.randrange(n) for _ in range(2))
                    c0, c1 = sorted(rng.randrange(m) for _ in range(2))
                    self.assertEqual(qt.query(r0, c0, r1, c1), brute(g, r0, c0, r1, c1))


if __name__ == "__main__":
    unittest.main()
