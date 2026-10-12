"""Tests for python/searching/binary_search/BinarySearch.py

Run from anywhere:
    cpunit binarysearch --py
or from this folder:
    python3 -m unittest -v test_binarysearch
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from BinarySearch import first_true, first_true_real, last_true


class TestBinarySearch(unittest.TestCase):

    def test_integer(self):
        for t in range(-2, 13):
            self.assertEqual(first_true(0, 10, lambda x: x >= t), min(max(t, 0), 11))
            self.assertEqual(last_true(0, 10, lambda x: x <= t), max(min(t, 10), -1))

    def test_real(self):
        self.assertAlmostEqual(first_true_real(0, 2, lambda x: x * x >= 2), 2 ** 0.5, places=9)


if __name__ == "__main__":
    unittest.main()
