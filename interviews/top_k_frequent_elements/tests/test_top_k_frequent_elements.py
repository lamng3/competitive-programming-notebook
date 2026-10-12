"""Tests for interviews/top_k_frequent_elements

Run from anywhere:
    cpunit top_k_frequent_elements --py
or from this folder:
    python3 -m unittest -v test_top_k_frequent_elements
"""
import os
import random
import sys
import unittest
from collections import Counter

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from solution import Solution as TopK


class TestTopKFrequentElements(unittest.TestCase):

    def test_347_top_k(self):
        rng = random.Random(5)
        for _ in range(200):
            nums = [rng.randint(0, 8) for _ in range(rng.randint(1, 30))]
            cnt = Counter(nums)
            k = rng.randint(1, len(cnt))
            got = TopK().topKFrequent(nums, k)
            self.assertEqual(len(set(got)), k)
            self.assertEqual(sorted((cnt[x] for x in got), reverse=True), sorted(cnt.values(), reverse=True)[:k])


if __name__ == "__main__":
    unittest.main()
