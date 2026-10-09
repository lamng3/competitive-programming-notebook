"""Tests for python/databases/data_structures/CuckooFilter.py

Run from anywhere:
    cpunit cuckoofilter --py
or from this folder:
    python3 -m unittest -v test_cuckoofilter

Expected interface (same as notebook/databases/data_structures/cuckoofilter.h):
    CuckooFilter(n, max_kicks)
        n: number of buckets, rounded UP to a power of two (so n = 1 is one bucket)
        every bucket holds 4 fingerprints
    insert(key) -> bool       False when the table is too full (after max_kicks kicks)
    lookup(key) -> bool
    remove(key) -> bool       removes ONE copy, False if the key is not stored
    fill_rate() -> float      used entries / (buckets * 4)
    false_positive_rate() -> float   estimate from the current fill

Keys are str.
"""
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from CuckooFilter import CuckooFilter


class TestCuckooFilter(unittest.TestCase):

    def test_empty_filter(self):
        cf = CuckooFilter(1024, 500)
        self.assertFalse(cf.lookup("apple"))
        self.assertFalse(cf.remove("apple"))

    def test_inserted_keys_are_found(self):
        cf = CuckooFilter(1024, 500)
        self.assertTrue(cf.insert("apple"))
        self.assertTrue(cf.insert("banana"))
        self.assertTrue(cf.lookup("apple"))
        self.assertTrue(cf.lookup("banana"))

    def test_light_load_never_fails(self):
        cf = CuckooFilter(1024, 500)
        keys = ["key" + str(i) for i in range(2000)]
        for k in keys:
            self.assertTrue(cf.insert(k), k)
        for k in keys:
            self.assertTrue(cf.lookup(k), k)

    def test_lookup_does_not_change_the_filter(self):
        cf = CuckooFilter(1024, 500)
        self.assertFalse(cf.lookup("apple"))
        self.assertFalse(cf.lookup("apple"))
        cf.insert("apple")
        self.assertTrue(cf.lookup("apple"))
        self.assertTrue(cf.lookup("apple"))

    def test_one_bucket_holds_exactly_four(self):
        cf = CuckooFilter(1, 500)
        for i in range(4):
            self.assertTrue(cf.insert("k" + str(i)))
        self.assertFalse(cf.insert("k4"))

    def test_remove_frees_a_slot(self):
        cf = CuckooFilter(1, 500)
        for i in range(4):
            cf.insert("k" + str(i))
        self.assertFalse(cf.insert("k4"))
        self.assertTrue(cf.remove("k0"))
        self.assertTrue(cf.insert("k4"))
        self.assertTrue(cf.lookup("k4"))

    def test_remove_makes_lookup_fail_and_keeps_others(self):
        cf = CuckooFilter(1024, 500)
        cf.insert("apple")
        cf.insert("banana")
        self.assertTrue(cf.remove("apple"))
        self.assertFalse(cf.lookup("apple"))
        self.assertTrue(cf.lookup("banana"))
        self.assertFalse(cf.remove("apple"))

    def test_duplicates_are_separate_copies(self):
        cf = CuckooFilter(1024, 500)
        cf.insert("apple")
        cf.insert("apple")
        self.assertTrue(cf.remove("apple"))
        self.assertTrue(cf.lookup("apple"))   # one copy is left
        self.assertTrue(cf.remove("apple"))
        self.assertFalse(cf.lookup("apple"))

    def test_one_key_fits_at_most_eight_times(self):
        # a key has only 2 candidate buckets of 4 entries each
        cf = CuckooFilter(1024, 500)
        stored = sum(cf.insert("apple") for _ in range(9))
        self.assertLessEqual(stored, 8)
        self.assertGreaterEqual(stored, 4)

    def test_overfilled_filter_rejects_inserts(self):
        cf = CuckooFilter(64, 500)               # room for 256 fingerprints
        stored = [k for k in ("item" + str(i) for i in range(1000)) if cf.insert(k)]
        print("stored %d of 1000 in 64 buckets (capacity 256)" % len(stored))
        self.assertLessEqual(len(stored), 256)
        self.assertLess(len(stored), 1000)

    def test_failed_insert_loses_nothing(self):
        # a failed insert may have kicked fingerprints around: they must all be put back
        cf = CuckooFilter(64, 500)
        stored = []
        for i in range(1000):
            k = "item" + str(i)
            if cf.insert(k):
                stored.append(k)
        for k in stored:
            self.assertTrue(cf.lookup(k), k)

    def test_high_load_keeps_no_false_negatives(self):
        cf = CuckooFilter(1024, 500)
        stored = [k for k in ("key" + str(i) for i in range(3500)) if cf.insert(k)]
        print("stored %d of 3500 in 1024 buckets (capacity 4096)" % len(stored))
        for k in stored:
            self.assertTrue(cf.lookup(k), k)

    def test_fills_most_of_the_table(self):
        # 3500 keys is 85% of 4096 slots. Fingerprints that all look alike
        # (a weak fingerprint function) make this fail long before the table is full.
        cf = CuckooFilter(1024, 500)
        stored = sum(cf.insert("key" + str(i)) for i in range(3500))
        self.assertGreaterEqual(stored, 3300)

    def test_removing_half_keeps_the_other_half(self):
        cf = CuckooFilter(1024, 500)
        stored = [k for k in ("key" + str(i) for i in range(3000)) if cf.insert(k)]
        for k in stored[::2]:
            self.assertTrue(cf.remove(k), k)
        for k in stored[1::2]:
            self.assertTrue(cf.lookup(k), k)


class TestCuckooFilterStatistics(unittest.TestCase):

    def test_fill_rate(self):
        cf = CuckooFilter(1024, 500)
        self.assertEqual(cf.fill_rate(), 0.0)
        for i in range(2000):
            cf.insert("key" + str(i))
        self.assertAlmostEqual(cf.fill_rate(), 2000 / 4096)
        cf.remove("key0")
        self.assertAlmostEqual(cf.fill_rate(), 1999 / 4096)

    def test_false_positive_estimate_grows_with_fill(self):
        empty = CuckooFilter(1024, 500)
        half, most = CuckooFilter(1024, 500), CuckooFilter(1024, 500)
        for i in range(2000):
            half.insert("key" + str(i))
        for i in range(3500):
            most.insert("key" + str(i))
        self.assertEqual(empty.false_positive_rate(), 0.0)
        self.assertGreater(half.false_positive_rate(), 0.0)
        self.assertGreater(most.false_positive_rate(), half.false_positive_rate())

    def test_measured_false_positive_rate_stays_low(self):
        cf = CuckooFilter(1024, 500)
        for i in range(2000):
            cf.insert("key" + str(i))
        trials = 20000
        fp = sum(cf.lookup("other" + str(i)) for i in range(trials))
        rate = fp / trials
        print("fill %.3f, estimated fp %.4f, measured fp %.4f (%d/%d)"
              % (cf.fill_rate(), cf.false_positive_rate(), rate, fp, trials))
        self.assertLess(rate, 0.05)


if __name__ == "__main__":
    unittest.main()
