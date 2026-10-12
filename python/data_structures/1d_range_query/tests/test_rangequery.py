"""Tests for python/data_structures/1d_range_query: FenwickTree, IterativeSegmentTree, SegmentTree

Run from anywhere:
    cpunit rangequery --py
or from this folder:
    python3 -m unittest -v test_rangequery
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from FenwickTree import FenwickTree
from IterativeSegmentTree import IterativeSegmentTree
from SegmentTree import SegmentTree


class TestRangeQuery(unittest.TestCase):

    def test_fenwick_small(self):
        ft = FenwickTree([1, 2, 3, 4, 5])
        self.assertEqual(ft.sum(5), 15)
        self.assertEqual(ft.sum(2, 4), 9)
        self.assertEqual(ft.sum(4, 2), 0)
        ft.add(3, 10)
        self.assertEqual(ft.sum(3, 3), 13)
        empty = FenwickTree(4)
        empty.add(2, 7)
        self.assertEqual(empty.sum(1, 4), 7)

    def test_fenwick_random(self):
        rng = random.Random(1)
        for _ in range(100):
            a = [rng.randint(-50, 50) for _ in range(rng.randint(1, 40))]
            ft, n = FenwickTree(a), len(a)
            for _ in range(60):
                if rng.random() < 0.5:
                    i, u = rng.randint(1, n), rng.randint(-50, 50)
                    ft.add(i, u)
                    a[i - 1] += u
                else:
                    L, R = sorted((rng.randint(1, n), rng.randint(1, n)))
                    self.assertEqual(ft.sum(L, R), sum(a[L - 1:R]))

    def test_iterative_random(self):
        rng = random.Random(2)
        for _ in range(100):
            a = [rng.randint(-50, 50) for _ in range(rng.randint(1, 40))]
            st, n = IterativeSegmentTree(a), len(a)
            for _ in range(60):
                if rng.random() < 0.5:
                    p, v = rng.randrange(n), rng.randint(-50, 50)
                    st.update(p, v)
                    a[p] = v
                else:
                    l = rng.randint(0, n)
                    r = rng.randint(l, n)
                    self.assertEqual(st.query(l, r), sum(a[l:r]))

    def test_segment_tree_sum_and_min(self):
        rng = random.Random(3)
        for _ in range(100):
            a = [rng.randint(-50, 50) for _ in range(rng.randint(1, 40))]
            n = len(a)
            s = SegmentTree(a)
            m = SegmentTree(a, min, float("inf"))
            for _ in range(60):
                if rng.random() < 0.4:
                    p, v = rng.randrange(n), rng.randint(-50, 50)
                    s.update(p, v)
                    m.update(p, v)
                    a[p] = v
                else:
                    l, r = sorted((rng.randrange(n), rng.randrange(n)))
                    self.assertEqual(s.query(l, r), sum(a[l:r + 1]))
                    self.assertEqual(m.query(l, r), min(a[l:r + 1]))
            self.assertEqual(s.query(1, 0), 0)


if __name__ == "__main__":
    unittest.main()
