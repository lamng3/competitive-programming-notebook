"""Tests for python/data_structures/1d_range_query/Mo.py

Run from anywhere:
    cpunit mo --py
or from this folder:
    python3 -m unittest -v test_mo
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from collections import Counter

from Mo import Mo


class TestMo(unittest.TestCase):

    def test_distinct_in_range(self):
        rng = random.Random(10)
        for _ in range(100):
            a = [rng.randint(0, 5) for _ in range(rng.randint(1, 30))]
            n = len(a)
            mo = Mo(a)
            qs = []
            for id in range(rng.randint(1, 20)):
                L, R = sorted((rng.randrange(n), rng.randrange(n)))
                mo.add_query(L, R, id)
                qs.append((L, R))
            cnt = Counter()

            def add(i): cnt[a[i]] += 1

            def remove(i):
                cnt[a[i]] -= 1
                if cnt[a[i]] == 0: del cnt[a[i]]

            ans = mo.process_queries(add, remove, lambda: len(cnt))
            self.assertEqual(ans, [len(set(a[L:R + 1])) for L, R in qs])


if __name__ == "__main__":
    unittest.main()
