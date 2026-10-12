"""Tests for python/math/modular_arithmetic/ModFact.py

Run from anywhere:
    cpunit modfact --py
or from this folder:
    python3 -m unittest -v test_modfact
"""
import math
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from ModFact import MOD, ModFact, modInverse


class TestModFact(unittest.TestCase):

    def test_nck_matches_math_comb(self):
        mf = ModFact(200)
        for n in range(0, 201, 7):
            for k in range(-1, n + 2):
                want = math.comb(n, k) % MOD if 0 <= k <= n else 0
                self.assertEqual(mf.nCk(n, k), want, (n, k))

    def test_inverse(self):
        for a in [1, 2, 3, 12345, MOD - 1]:
            self.assertEqual(a * modInverse(a) % MOD, 1)
            self.assertEqual(modInverse(a), pow(a, -1, MOD))


if __name__ == "__main__":
    unittest.main()
