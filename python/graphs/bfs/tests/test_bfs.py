"""Tests for python/graphs/bfs/BFS.py

Run from anywhere:
    cpunit bfs --py
or from this folder:
    python3 -m unittest -v test_bfs
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from BFS import bfs, bfs01, bfs_grid


class TestBFS(unittest.TestCase):

    def test_grid_multi_source(self):
        grid = ["..#",
                ".##",
                "..."]
        d = bfs_grid(3, 3, [(0, 0)], lambda r, c: grid[r][c] == ".")
        self.assertEqual(d[2][2], 4)
        self.assertEqual(d[0][2], -1)
        d2 = bfs_grid(3, 3, [(0, 0), (2, 2)], lambda r, c: grid[r][c] == ".")
        self.assertEqual(d2[2][1], 1)

    def test_graph_and_01_against_floyd(self):
        rng = random.Random(5)
        for _ in range(100):
            n = rng.randint(1, 9)
            g, w = [[] for _ in range(n)], [[] for _ in range(n)]
            INF = float("inf")
            D1 = [[0 if i == j else INF for j in range(n)] for i in range(n)]
            D01 = [row[:] for row in D1]
            for _ in range(rng.randint(0, 15)):
                u, v, c = rng.randrange(n), rng.randrange(n), rng.randint(0, 1)
                g[u].append(v)
                w[u].append((v, c))
                D1[u][v] = min(D1[u][v], 1)
                D01[u][v] = min(D01[u][v], c)
            for k in range(n):
                for i in range(n):
                    for j in range(n):
                        D1[i][j] = min(D1[i][j], D1[i][k] + D1[k][j])
                        D01[i][j] = min(D01[i][j], D01[i][k] + D01[k][j])
            self.assertEqual(bfs(g, [0]), [-1 if x == INF else x for x in D1[0]])
            self.assertEqual(bfs01(w, 0), D01[0])


if __name__ == "__main__":
    unittest.main()
