"""Tests for python/data_structures/rurq/PersistentSegmentTree.py

Run from anywhere:
    cpunit persistentsegmenttree --py
or from this folder:
    python3 -m unittest -v test_persistentsegmenttree
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from PersistentSegmentTree import PersistentSparseST


class TestPersistentST(unittest.TestCase):

    def test_every_version_survives(self):
        rng = random.Random(12)
        for _ in range(100):
            n = rng.randint(1, 20)
            st = PersistentSparseST(n)
            roots, arrays = [0], [[0] * n]
            for _ in range(30):
                k = rng.randrange(len(roots)) # branch off any old version
                pos, val = rng.randrange(n), rng.randint(-9, 9)
                roots.append(st.update(roots[k], pos, val))
                arr = arrays[k][:]
                arr[pos] = val
                arrays.append(arr)
            for root, arr in zip(roots, arrays):
                for _ in range(5):
                    l, r = sorted((rng.randrange(n), rng.randrange(n)))
                    self.assertEqual(st.query(root, l, r), sum(arr[l:r + 1]))


if __name__ == "__main__":
    unittest.main()
