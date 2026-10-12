"""Tests for python/patterns.py

Run from anywhere:
    cpunit patterns --py
or from this folder:
    python3 -m unittest -v test_patterns
"""
import os
import random
import sys
import unittest
from itertools import combinations

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import patterns as P


class TestPatterns(unittest.TestCase):

    def test_prefix_sums(self):
        a = [3, -1, 4, 1, 5]
        pre = P.prefix_sums(a)
        for l in range(len(a)):
            for r in range(l, len(a)):
                self.assertEqual(pre[r + 1] - pre[l], sum(a[l:r + 1]))
        g = [[random.Random(i * 7 + j).randint(-9, 9) for j in range(4)] for i in range(3)]
        Q = P.prefix_sums_2d(g)
        for r1 in range(3):
            for r2 in range(r1, 3):
                for c1 in range(4):
                    for c2 in range(c1, 4):
                        want = sum(g[r][c] for r in range(r1, r2 + 1) for c in range(c1, c2 + 1))
                        self.assertEqual(Q[r2 + 1][c2 + 1] - Q[r1][c2 + 1] - Q[r2 + 1][c1] + Q[r1][c1], want)

    def test_binary_search(self):
        for t in range(-2, 12):
            self.assertEqual(P.binary_search(0, 9, lambda x: x >= t), min(max(t, 0), 10))

    def test_bfs_grid(self):
        grid = [[0, 0, 0],
                [1, 1, 0],
                [0, 0, 0]]
        d = P.bfs_grid(grid, 0, 0)
        self.assertEqual(d[2][0], 6)
        self.assertEqual(d[1][0], -1)
        self.assertEqual(P.bfs_grid([[0, 1, 0]], 0, 0)[0][2], -1)

    def test_bfs_and_dijkstra_agree_on_unit_weights(self):
        rng = random.Random(9)
        for _ in range(50):
            n = rng.randint(1, 12)
            g = [[] for _ in range(n)]
            for u, v in combinations(range(n), 2):
                if rng.random() < 0.25:
                    g[u].append(v)
                    g[v].append(u)
            d1 = P.bfs(g, 0)
            d2 = P.dijkstra([[(v, 1) for v in g[u]] for u in range(n)], 0)
            self.assertEqual(d1, [-1 if x == float("inf") else x for x in d2])

    def test_dijkstra_weighted(self):
        g = [[(1, 4), (2, 1)], [(3, 1)], [(1, 2), (3, 5)], []]
        self.assertEqual(P.dijkstra(g, 0), [0, 3, 1, 4])

    def test_dfs(self):
        self.assertEqual(P.count_islands([[1, 1, 0], [0, 0, 1], [1, 0, 1]]), 3)
        self.assertEqual(P.subtree_sizes([[1, 2], [0, 3], [0], [1]]), [4, 2, 1, 1])

    def test_topo_sort(self):
        order = P.topo_sort(4, [(0, 1), (1, 2), (0, 3), (3, 2)])
        pos = {u: i for i, u in enumerate(order)}
        for u, v in [(0, 1), (1, 2), (0, 3), (3, 2)]:
            self.assertLess(pos[u], pos[v])
        self.assertEqual(P.topo_sort(2, [(0, 1), (1, 0)]), [])

    def test_window_and_stack(self):
        self.assertEqual(P.longest_k_distinct("eceba", 2), 3)
        self.assertEqual(P.longest_k_distinct("aa", 1), 2)
        self.assertEqual(P.longest_k_distinct("", 1), 0)
        rng = random.Random(3)
        for _ in range(100):
            a = [rng.randint(0, 5) for _ in range(rng.randint(0, 12))]
            n = len(a)
            want = [next((j for j in range(i + 1, n) if a[j] > a[i]), n) for i in range(n)]
            self.assertEqual(P.next_greater(a), want)

    def test_backtracking_and_dp(self):
        self.assertEqual(sorted(map(tuple, P.subsets([1, 2, 3]))),
                         sorted(c for k in range(4) for c in combinations([1, 2, 3], k)))
        self.assertEqual(P.lcs("abcde", "ace"), 3)
        self.assertEqual(P.compress([30, 10, 30, 20]), [2, 0, 2, 1])


if __name__ == "__main__":
    unittest.main()
