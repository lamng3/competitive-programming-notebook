"""Tests for python/graphs/shortest_path/Dijkstra.py

Run from anywhere:
    cpunit dijkstra --py
or from this folder:
    python3 -m unittest -v test_dijkstra
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from Dijkstra import dijkstra, path


class TestDijkstra(unittest.TestCase):

    def test_small(self):
        g = [[(1, 4), (2, 1)], [(3, 1)], [(1, 2), (3, 5)], []]
        dist, par = dijkstra(g, 0)
        self.assertEqual(dist, [0, 3, 1, 4])
        self.assertEqual(path(par, 0, 3), [0, 2, 1, 3])
        self.assertEqual(path(par, 0, 0), [0])
        dist, par = dijkstra([[], []], 0)
        self.assertEqual(path(par, 0, 1), [])

    def test_random_against_floyd(self):
        rng = random.Random(6)
        for _ in range(100):
            n = rng.randint(1, 8)
            g = [[] for _ in range(n)]
            INF = float("inf")
            D = [[0 if i == j else INF for j in range(n)] for i in range(n)]
            for _ in range(rng.randint(0, 20)):
                u, v, w = rng.randrange(n), rng.randrange(n), rng.randint(0, 9)
                g[u].append((v, w))
                D[u][v] = min(D[u][v], w)
            for k in range(n):
                for i in range(n):
                    for j in range(n):
                        D[i][j] = min(D[i][j], D[i][k] + D[k][j])
            dist, par = dijkstra(g, 0)
            self.assertEqual(dist, D[0])
            for t in range(n):
                p = path(par, 0, t)
                if dist[t] == INF:
                    self.assertEqual(p, [])
                else:
                    cost = sum(min(w for v, w in g[a] if v == b) for a, b in zip(p, p[1:]))
                    self.assertEqual(cost, dist[t])


if __name__ == "__main__":
    unittest.main()
