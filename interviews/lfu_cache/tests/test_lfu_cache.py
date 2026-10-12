"""Tests for interviews/lfu_cache

Run from anywhere:
    cpunit lfu_cache --py
or from this folder:
    python3 -m unittest -v test_lfu_cache
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from solution import LFUCache


class TestLfuCache(unittest.TestCase):

    def test_460_lfu_against_brute_force(self):
        rng = random.Random(3)
        for _ in range(100):
            cap = rng.randint(0, 4)
            lfu, ref, clock = LFUCache(cap), {}, 0 # ref: key -> [value, freq, last use]
            for _ in range(80):
                clock += 1
                k = rng.randint(0, 6)
                if rng.random() < 0.5:
                    want = -1
                    if k in ref:
                        ref[k][1] += 1
                        ref[k][2] = clock
                        want = ref[k][0]
                    self.assertEqual(lfu.get(k), want)
                else:
                    v = rng.randint(0, 99)
                    lfu.put(k, v)
                    if cap == 0: continue
                    if k in ref:
                        ref[k] = [v, ref[k][1] + 1, clock]
                    else:
                        if len(ref) == cap:
                            del ref[min(ref, key=lambda x: (ref[x][1], ref[x][2]))]
                        ref[k] = [v, 1, clock]


if __name__ == "__main__":
    unittest.main()
