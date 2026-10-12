"""Tests for python/trees/euler_tour/EulerTour.py

Run from anywhere:
    cpunit eulertour --py
or from this folder:
    python3 -m unittest -v test_eulertour
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from EulerTour import EulerTour


class TestEulerTour(unittest.TestCase):

    def test_subtree_is_a_time_range(self):
        rng = random.Random(15)
        for _ in range(100):
            n = rng.randint(1, 30)
            g = [[] for _ in range(n)]
            par = [-1] * n
            for v in range(1, n):
                p = rng.randrange(v)
                par[v] = p
                g[p].append(v)
                g[v].append(p)
            et = EulerTour(n, g)

            def subtree(u):
                out, st = [], [u]
                while st:
                    x = st.pop()
                    out.append(x)
                    st.extend(c for c in range(n) if par[c] == x)
                return out

            for u in range(n):
                sub = subtree(u)
                self.assertEqual(et.E[u] - et.S[u], len(sub))
                self.assertEqual(sorted(et.order[et.S[u]:et.E[u]]), sorted(sub))
                self.assertEqual(et.sz[et.S[u]], len(sub))

    def test_deep_path(self):
        n = 100000
        g = [[] for _ in range(n)]
        for i in range(n - 1):
            g[i].append(i + 1)
            g[i + 1].append(i)
        et = EulerTour(n, g)
        self.assertEqual(et.E[0] - et.S[0], n)


if __name__ == "__main__":
    unittest.main()
