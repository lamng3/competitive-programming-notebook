"""Tests for python/databases/data_structures/CountMinSketch.py

Run from anywhere:
    cpunit countminsketch --py
or from this folder:
    python3 -m unittest -v test_countminsketch

Expected interface (same as notebook/databases/data_structures/countminsketch.h):
    CountMinSketch(width, depth, seeds=None)
        seeds: optional list with one seed per row; random seeds when None
    insert(x)                 x is a str or an int
    count(x) -> int           estimate, never below the true count
    clear()
    merge(other) -> CountMinSketch or None
        a NEW sketch holding both counts, or None when width, depth or seeds differ
    top_k(k, candidates) -> list
        the k candidates with the largest estimates, most frequent first
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from CountMinSketch import CountMinSketch

W, D = 10000, 4
SEEDS = [11, 22, 33, 44]


def filled(width=W, depth=D, seeds=SEEDS):
    cms = CountMinSketch(width, depth, seeds)
    for key, times in [("apple", 5), ("banana", 2), ("cherry", 1)]:
        for _ in range(times):
            cms.insert(key)
    return cms


class TestCountMinSketch(unittest.TestCase):

    def test_empty_sketch_counts_zero(self):
        cms = CountMinSketch(W, D, SEEDS)
        self.assertEqual(cms.count("apple"), 0)

    def test_counts_match_with_few_keys_in_a_wide_table(self):
        cms = filled()
        self.assertEqual(cms.count("apple"), 5)
        self.assertEqual(cms.count("banana"), 2)
        self.assertEqual(cms.count("cherry"), 1)

    def test_unseen_key_counts_zero_in_a_wide_table(self):
        self.assertEqual(filled().count("missing"), 0)

    def test_int_keys(self):
        cms = CountMinSketch(W, D, SEEDS)
        for _ in range(3):
            cms.insert(42)
        cms.insert(7)
        self.assertEqual(cms.count(42), 3)
        self.assertEqual(cms.count(7), 1)

    def test_count_does_not_change_the_sketch(self):
        cms = filled()
        for _ in range(3):
            self.assertEqual(cms.count("apple"), 5)

    def test_random_seeds_work(self):
        cms = CountMinSketch(W, D)
        cms.insert("apple")
        cms.insert("apple")
        self.assertEqual(cms.count("apple"), 2)

    def test_same_seeds_behave_the_same(self):
        a, b = filled(), filled()
        for key in ["apple", "banana", "cherry", "missing"]:
            self.assertEqual(a.count(key), b.count(key))

    def test_never_undercounts_even_in_a_tiny_table(self):
        # 20 keys share 4 columns, so counters collide, but the estimate
        # is the minimum over rows and can only be too high, never too low
        cms = CountMinSketch(4, 3, [7, 11, 13])
        truth = {}
        for i in range(100):
            x = i % 20
            cms.insert(x)
            truth[x] = truth.get(x, 0) + 1
        for x, t in truth.items():
            self.assertGreaterEqual(cms.count(x), t, x)

    def test_estimate_is_at_most_the_total_inserted(self):
        cms = CountMinSketch(4, 3, [7, 11, 13])
        for i in range(100):
            cms.insert(i % 20)
        for x in range(20):
            self.assertLessEqual(cms.count(x), 100)

    def test_error_stays_small_on_a_realistic_stream(self):
        # width 2000 -> expected extra count about n/width = 0.5 per key
        rng = random.Random(1)
        cms = CountMinSketch(2000, 5)
        truth = {}
        for _ in range(1000):
            x = "key" + str(rng.randint(0, 299))
            cms.insert(x)
            truth[x] = truth.get(x, 0) + 1
        worst = 0
        for x, t in truth.items():
            est = cms.count(x)
            self.assertGreaterEqual(est, t, x)
            worst = max(worst, est - t)
        print("worst overcount: %d" % worst)
        self.assertLessEqual(worst, 10)

    def test_clear_resets_everything(self):
        cms = filled()
        cms.clear()
        self.assertEqual(cms.count("apple"), 0)
        self.assertEqual(cms.count("banana"), 0)

    def test_usable_after_clear(self):
        cms = filled()
        cms.clear()
        cms.insert("apple")
        self.assertEqual(cms.count("apple"), 1)

    def test_merge_adds_counts(self):
        a = filled()
        b = CountMinSketch(W, D, SEEDS)
        for _ in range(3):
            b.insert("apple")
        merged = a.merge(b)
        self.assertIsNotNone(merged)
        self.assertEqual(merged.count("apple"), 8)
        self.assertEqual(merged.count("banana"), 2)
        self.assertEqual(merged.count("cherry"), 1)

    def test_merge_leaves_the_inputs_alone(self):
        a = filled()
        b = CountMinSketch(W, D, SEEDS)
        b.insert("apple")
        a.merge(b)
        self.assertEqual(a.count("apple"), 5)
        self.assertEqual(b.count("apple"), 1)

    def test_merge_needs_matching_seeds(self):
        self.assertIsNone(filled().merge(CountMinSketch(W, D, [9, 8, 7, 6])))

    def test_merge_needs_matching_size(self):
        self.assertIsNone(filled().merge(CountMinSketch(W + 1, D, SEEDS)))
        self.assertIsNone(filled().merge(CountMinSketch(W, D - 1, SEEDS[:-1])))

    def test_top_k_orders_by_frequency(self):
        cms = filled()
        self.assertEqual(cms.top_k(2, ["cherry", "banana", "apple"]), ["apple", "banana"])

    def test_top_k_larger_than_candidates(self):
        cms = filled()
        self.assertEqual(cms.top_k(10, ["banana", "apple"]), ["apple", "banana"])

    def test_top_k_zero_and_empty(self):
        cms = filled()
        self.assertEqual(cms.top_k(0, ["apple"]), [])
        self.assertEqual(cms.top_k(3, []), [])


if __name__ == "__main__":
    unittest.main()
