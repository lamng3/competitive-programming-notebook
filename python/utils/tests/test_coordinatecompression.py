"""Tests for python/utils/CoordinateCompression.py

Run from anywhere:
    cpunit coordinatecompression --py
or from this folder:
    python3 -m unittest -v test_coordinatecompression
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from CoordinateCompression import CoordinateCompressor


class TestCoordinateCompression(unittest.TestCase):

    def test_example(self):
        a = [100, -5, 100, 7, 10**18]
        cc = CoordinateCompressor(a)
        self.assertEqual(a, [2, 0, 2, 1, 3])
        self.assertEqual(cc.size(), 4)
        self.assertEqual(cc.value_at(3), 10**18)
        self.assertEqual(cc.rank_of(7), 1)
        self.assertEqual(cc.rank_of(8), 2)   # not stored: where it would go
        self.assertEqual(cc.rank_of(-10), 0)

    def test_random_keeps_order(self):
        rng = random.Random(5)
        for _ in range(100):
            orig = [rng.randint(-10**9, 10**9) for _ in range(rng.randint(0, 30))]
            a = list(orig)
            cc = CoordinateCompressor(a)
            for i in range(len(a)):
                self.assertEqual(cc.value_at(a[i]), orig[i])
                for j in range(len(a)):
                    self.assertEqual(a[i] < a[j], orig[i] < orig[j])


if __name__ == "__main__":
    unittest.main()
