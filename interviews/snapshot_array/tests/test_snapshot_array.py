"""Tests for interviews/snapshot_array

Run from anywhere:
    cpunit snapshot_array --py
or from this folder:
    python3 -m unittest -v test_snapshot_array
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from solution import SnapshotArray


class TestSnapshotArray(unittest.TestCase):

    def test_1146_snapshot_array(self):
        rng = random.Random(7)
        for _ in range(50):
            n = rng.randint(1, 6)
            sa, cur, snaps = SnapshotArray(n), [0] * n, []
            for _ in range(100):
                op = rng.random()
                if op < 0.5:
                    i, v = rng.randrange(n), rng.randint(0, 9)
                    sa.set(i, v)
                    cur[i] = v
                elif op < 0.7:
                    self.assertEqual(sa.snap(), len(snaps))
                    snaps.append(cur[:])
                elif snaps:
                    s, i = rng.randrange(len(snaps)), rng.randrange(n)
                    self.assertEqual(sa.get(i, s), snaps[s][i])


if __name__ == "__main__":
    unittest.main()
