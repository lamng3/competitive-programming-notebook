"""Tests for python/data_structures/rurq/LazySegmentTree.py

Run from anywhere:
    cpunit lazysegmenttree --py
or from this folder:
    python3 -m unittest -v test_lazysegmenttree

Interface:
    LazySegmentTree(a)
    update(ql, qr, x)   add x to a[ql..qr], inclusive
    query(ql, qr)       sum of a[ql..qr], inclusive
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from LazySegmentTree import LazySegmentTree


class TestLazySegmentTree(unittest.TestCase):

    def test_small(self):
        st = LazySegmentTree([1, 2, 3, 4])
        st.update(1, 2, 10)
        self.assertEqual(st.query(0, 3), 30)
        self.assertEqual(st.query(2, 3), 17)
        self.assertEqual(st.query(1, 1), 12)

    def test_random(self):
        rng = random.Random(4)
        for _ in range(150):
            a = [rng.randint(-20, 20) for _ in range(rng.randint(1, 30))]
            st, n = LazySegmentTree(a), len(a)
            for _ in range(80):
                l, r = sorted((rng.randrange(n), rng.randrange(n)))
                if rng.random() < 0.5:
                    x = rng.randint(-20, 20)
                    st.update(l, r, x)
                    for i in range(l, r + 1): a[i] += x
                else:
                    self.assertEqual(st.query(l, r), sum(a[l:r + 1]))


if __name__ == "__main__":
    unittest.main()
