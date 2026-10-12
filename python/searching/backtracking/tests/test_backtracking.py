"""Tests for python/searching/backtracking/Backtracking.py

Run from anywhere:
    cpunit backtracking --py
or from this folder:
    python3 -m unittest -v test_backtracking
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from itertools import combinations, permutations as perms, product

from Backtracking import backtrack, permutations, subsets


class TestBacktracking(unittest.TestCase):

    def test_subsets_and_permutations(self):
        a = [1, 2, 3, 4]
        self.assertEqual(sorted(map(tuple, subsets(a))), sorted(c for k in range(5) for c in combinations(a, k)))
        self.assertEqual(sorted(map(tuple, permutations(a))), sorted(perms(a)))
        self.assertEqual(subsets([]), [[]])

    def test_general_backtrack(self):
        # all length-3 strings over "ab" with no two equal neighbors
        got = backtrack(3, lambda i: "ab", lambda path, x: not path or path[-1] != x)
        self.assertEqual(sorted("".join(p) for p in got), ["aba", "bab"])
        self.assertEqual(len(backtrack(3, lambda i: range(i + 1))), len(list(product(range(1), range(2), range(3)))))


if __name__ == "__main__":
    unittest.main()
