"""Tests for python/math/modular_arithmetic/ModInv.py

Run from anywhere:
    cpunit modinv --py
or from this folder:
    python3 -m unittest -v test_modinv
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from ModInv import MOD, binpow, modInverse


class TestModInv(unittest.TestCase):

    def test_against_builtin_pow(self):
        rng = random.Random(14)
        for _ in range(200):
            a, b = rng.randrange(1, MOD), rng.randrange(0, 10**18)
            self.assertEqual(binpow(a, b), pow(a, b, MOD))
            self.assertEqual(modInverse(a), pow(a, -1, MOD))


if __name__ == "__main__":
    unittest.main()
