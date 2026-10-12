"""Tests for interviews/insert_delete_getrandom_o1

Run from anywhere:
    cpunit insert_delete_getrandom_o1 --py
or from this folder:
    python3 -m unittest -v test_insert_delete_getrandom_o1
"""
import os
import random
import sys
import unittest
from collections import Counter

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from solution import RandomizedSet


class TestInsertDeleteGetrandomO1(unittest.TestCase):

    def test_380_randomized_set(self):
        rng = random.Random(2)
        rs, ref = RandomizedSet(), set()
        for _ in range(3000):
            x, op = rng.randint(0, 30), rng.random()
            if op < 0.45: self.assertEqual(rs.insert(x), x not in ref); ref.add(x)
            elif op < 0.9: self.assertEqual(rs.remove(x), x in ref); ref.discard(x)
            elif ref: self.assertIn(rs.getRandom(), ref)
        rs = RandomizedSet()
        for x in range(4): rs.insert(x)
        seen = Counter(rs.getRandom() for _ in range(4000))
        self.assertTrue(all(800 < seen[x] < 1200 for x in range(4)), seen)


if __name__ == "__main__":
    unittest.main()
