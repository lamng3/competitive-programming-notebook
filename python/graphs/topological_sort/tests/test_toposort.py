"""Tests for python/graphs/topological_sort/TopoSort.py

Run from anywhere:
    cpunit toposort --py
or from this folder:
    python3 -m unittest -v test_toposort
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from TopoSort import topo_sort


class TestTopoSort(unittest.TestCase):

    def test_random_dags_and_cycles(self):
        rng = random.Random(7)
        for _ in range(200):
            n = rng.randint(1, 8)
            perm = list(range(n))
            rng.shuffle(perm)
            g = [[] for _ in range(n)]
            edges = []
            for _ in range(rng.randint(0, 12)):
                i, j = sorted(rng.sample(range(n), 2)) if n > 1 else (0, 0)
                if i == j: continue
                g[perm[i]].append(perm[j])
                edges.append((perm[i], perm[j]))
            order = topo_sort(g)
            pos = {u: k for k, u in enumerate(order)}
            self.assertEqual(len(order), n)
            for u, v in edges: self.assertLess(pos[u], pos[v])
            if edges:
                u, v = edges[0]
                g[v].append(u) # close a cycle
                self.assertEqual(topo_sort(g), [])


if __name__ == "__main__":
    unittest.main()
