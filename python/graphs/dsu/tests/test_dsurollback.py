"""Tests for python/graphs/dsu/DSURollback.py

Run from anywhere:
    cpunit dsurollback --py
or from this folder:
    python3 -m unittest -v test_dsurollback
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from DSURollback import DSURollback


class TestDSURollback(unittest.TestCase):

    def test_rollback_restores_state(self):
        rng = random.Random(8)
        for _ in range(100):
            n = rng.randint(1, 10)
            d = DSURollback(n)
            snapshots = []
            for _ in range(30):
                if rng.random() < 0.6 or not snapshots:
                    before = (d.par[:], d.sz[:])
                    if d.unite(rng.randrange(n), rng.randrange(n)): snapshots.append(before)
                else:
                    d.rollback()
                    self.assertEqual((d.par, d.sz), snapshots.pop())
        d = DSURollback(3)
        self.assertTrue(d.unite(0, 1))
        self.assertFalse(d.unite(1, 0))
        d.rollback()
        self.assertNotEqual(d.find(0), d.find(1))
        d.rollback() # empty history: no-op


if __name__ == "__main__":
    unittest.main()
