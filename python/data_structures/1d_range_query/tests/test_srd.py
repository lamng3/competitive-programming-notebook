"""Tests for python/data_structures/1d_range_query/SRD.py

Run from anywhere:
    cpunit srd --py
or from this folder:
    python3 -m unittest -v test_srd
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from math import isqrt

from SRD import SRD


class TestSRD(unittest.TestCase):

    def test_random(self):
        rng = random.Random(9)
        for _ in range(200):
            n = rng.randint(1, 40)
            a = [rng.randint(-50, 50) for _ in range(n)]
            b = isqrt(n - 1) + 1
            s = SRD(b, a)
            for _ in range(60):
                if rng.random() < 0.5:
                    x, v = rng.randrange(n), rng.randint(-50, 50)
                    s.update(x, v)
                    a[x] = v
                else:
                    l = rng.randint(0, n)
                    r = rng.randint(l, n)
                    self.assertEqual(s.query(l, r), sum(a[l:r]))
                    self.assertEqual(s.query(r), sum(a[:r]))


if __name__ == "__main__":
    unittest.main()
