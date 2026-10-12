"""Tests for python/data_structures/rurq/SparseSegmentTree.py

Run from anywhere:
    cpunit sparsesegmenttree --py
or from this folder:
    python3 -m unittest -v test_sparsesegmenttree
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from SparseSegmentTree import SparseST


class TestSparseST(unittest.TestCase):

    def test_huge_range(self):
        st = SparseST(10**9)
        st.update(10, 10**8, 2)
        st.update(50, 60, -1) # the C++ version cannot assign -1: it is its "no lazy" mark
        self.assertEqual(st.query(0, 10**9 - 1), 2 * (10**8 - 9) - 3 * 11)
        self.assertEqual(st.query(55, 55), -1)
        self.assertEqual(st.query(0, 9), 0)

    def test_random(self):
        rng = random.Random(11)
        for _ in range(150):
            n = rng.randint(1, 30)
            a = [0] * n
            st = SparseST(n)
            for _ in range(60):
                l, r = sorted((rng.randrange(n), rng.randrange(n)))
                if rng.random() < 0.5:
                    v = rng.randint(-5, 5)
                    st.update(l, r, v)
                    for i in range(l, r + 1): a[i] = v
                else:
                    self.assertEqual(st.query(l, r), sum(a[l:r + 1]))


if __name__ == "__main__":
    unittest.main()
