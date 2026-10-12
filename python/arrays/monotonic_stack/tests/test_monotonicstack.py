"""Tests for python/arrays/monotonic_stack/MonotonicStack.py

Run from anywhere:
    cpunit monotonicstack --py
or from this folder:
    python3 -m unittest -v test_monotonicstack
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from operator import ge, gt, le, lt

from MonotonicStack import next_index, prev_index


class TestMonotonicStack(unittest.TestCase):

    def test_all_four_against_brute_force(self):
        rng = random.Random(4)
        for _ in range(200):
            a = [rng.randint(0, 5) for _ in range(rng.randint(0, 12))]
            n = len(a)
            for beats in (gt, lt, ge, le):
                nxt = [next((j for j in range(i + 1, n) if beats(a[j], a[i])), n) for i in range(n)]
                prv = [next((j for j in range(i - 1, -1, -1) if beats(a[j], a[i])), -1) for i in range(n)]
                self.assertEqual(next_index(a, beats), nxt)
                self.assertEqual(prev_index(a, beats), prv)


if __name__ == "__main__":
    unittest.main()
