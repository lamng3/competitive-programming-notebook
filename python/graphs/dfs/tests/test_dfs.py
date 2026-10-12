"""Tests for python/graphs/dfs/DFS.py

Run from anywhere:
    cpunit dfs --py
or from this folder:
    python3 -m unittest -v test_dfs
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from DFS import components, flood_fill, tree_dfs


class TestDFS(unittest.TestCase):

    def test_components(self):
        comp, k = components([[1], [0], [], [4], [3]])
        self.assertEqual(k, 3)
        self.assertEqual(comp[0], comp[1])
        self.assertEqual(comp[3], comp[4])
        self.assertNotEqual(comp[0], comp[2])

    def test_flood_fill_counts_islands(self):
        grid = ["110",
                "001",
                "101"]
        seen, islands = set(), 0
        for r in range(3):
            for c in range(3):
                if grid[r][c] == "1" and (r, c) not in seen:
                    flood_fill(3, 3, r, c, lambda a, b: grid[a][b] == "1", seen)
                    islands += 1
        self.assertEqual(islands, 3)

    def test_tree_dfs_deep_path(self):
        n = 100000 # far past the recursion limit
        g = [[] for _ in range(n)]
        for i in range(n - 1):
            g[i].append(i + 1)
            g[i + 1].append(i)
        par, depth, sz, order = tree_dfs(g)
        self.assertEqual(sz[0], n)
        self.assertEqual(depth[n - 1], n - 1)
        self.assertEqual(par[5], 4)
        par, depth, sz, order = tree_dfs([[1, 2], [0, 3], [0], [1]])
        self.assertEqual(sz, [4, 2, 1, 1])
        self.assertEqual(order[0], 0)


if __name__ == "__main__":
    unittest.main()
