"""Tests for interviews/design_hit_counter

Run from anywhere:
    cpunit design_hit_counter --py
or from this folder:
    python3 -m unittest -v test_design_hit_counter
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from solution import HitCounter


class TestDesignHitCounter(unittest.TestCase):

    def test_362_hit_counter(self):
        rng = random.Random(1)
        for _ in range(50):
            hc, hits, t = HitCounter(), [], 1
            for _ in range(200):
                t += rng.choice([0, 0, 1, 7, 150, 400])
                if rng.random() < 0.6:
                    hc.hit(t)
                    hits.append(t)
                else:
                    self.assertEqual(hc.getHits(t), sum(1 for h in hits if h > t - 300))


if __name__ == "__main__":
    unittest.main()
