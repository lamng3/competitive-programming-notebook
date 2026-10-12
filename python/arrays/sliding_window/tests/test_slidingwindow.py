"""Tests for python/arrays/sliding_window/SlidingWindow.py

Run from anywhere:
    cpunit slidingwindow --py
or from this folder:
    python3 -m unittest -v test_slidingwindow
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from collections import Counter

from SlidingWindow import longest_window, shortest_window


class TestSlidingWindow(unittest.TestCase):

    def test_k_distinct_against_brute_force(self):
        rng = random.Random(2)
        for _ in range(200):
            s = "".join(rng.choice("abc") for _ in range(rng.randint(0, 12)))
            k = rng.randint(1, 3)
            cnt = Counter()

            def add(i): cnt[s[i]] += 1

            def remove(i):
                cnt[s[i]] -= 1
                if cnt[s[i]] == 0: del cnt[s[i]]

            got = longest_window(len(s), add, remove, lambda: len(cnt) > k)
            want = max([j - i for i in range(len(s) + 1) for j in range(i, len(s) + 1) if len(set(s[i:j])) <= k])
            self.assertEqual(got, want, (s, k))

    def test_min_subarray_sum_at_least_target(self):
        rng = random.Random(3)
        for _ in range(200):
            a = [rng.randint(1, 9) for _ in range(rng.randint(0, 12))]
            t = rng.randint(1, 40)
            cur = [0]

            def add(i): cur[0] += a[i]

            def remove(i): cur[0] -= a[i]

            got = shortest_window(len(a), add, remove, lambda: cur[0] >= t)
            lens = [j - i for i in range(len(a)) for j in range(i + 1, len(a) + 1) if sum(a[i:j]) >= t]
            self.assertEqual(got, min(lens) if lens else 0)


if __name__ == "__main__":
    unittest.main()
