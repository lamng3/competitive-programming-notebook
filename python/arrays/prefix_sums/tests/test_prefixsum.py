"""Tests for python/arrays/prefix_sums/PrefixSum.py

Run from anywhere:
    cpunit prefixsum --py
or from this folder:
    python3 -m unittest -v test_prefixsum
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from PrefixSum import PrefixSum, PrefixSum2D


class TestPrefixSum(unittest.TestCase):

    def test_random(self):
        rng = random.Random(1)
        for _ in range(50):
            a = [rng.randint(-9, 9) for _ in range(rng.randint(1, 15))]
            p = PrefixSum(a)
            for l in range(len(a)):
                for r in range(l, len(a)):
                    self.assertEqual(p.query(l, r), sum(a[l:r + 1]))
            n, m = rng.randint(1, 5), rng.randint(1, 5)
            g = [[rng.randint(-9, 9) for _ in range(m)] for _ in range(n)]
            q = PrefixSum2D(g)
            for r1 in range(n):
                for r2 in range(r1, n):
                    for c1 in range(m):
                        for c2 in range(c1, m):
                            want = sum(g[r][c] for r in range(r1, r2 + 1) for c in range(c1, c2 + 1))
                            self.assertEqual(q.query(r1, c1, r2, c2), want)


if __name__ == "__main__":
    unittest.main()
