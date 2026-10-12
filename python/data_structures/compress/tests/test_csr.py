"""Tests for python/data_structures/compress/CSR.py

Run from anywhere:
    cpunit csr --py
or from this folder:
    python3 -m unittest -v test_csr
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from CSR import CSR


class TestCSR(unittest.TestCase):

    def test_matches_lists(self):
        rng = random.Random(13)
        for _ in range(100):
            n = rng.randint(1, 10)
            csr, want = CSR(n), [[] for _ in range(n)]
            for _ in range(rng.randint(0, 30)):
                i, x = rng.randrange(n), rng.randint(0, 99)
                csr.add(i, x)
                want[i].append(x)
            csr.build()
            self.assertEqual([csr[i] for i in range(n)], want) # stable: insertion order kept


if __name__ == "__main__":
    unittest.main()
