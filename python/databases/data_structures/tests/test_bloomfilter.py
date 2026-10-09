"""Tests for python/databases/data_structures/BloomFilter.py

Write the class there, then run from this folder:
    python3 -m unittest -v test_bloomfilter

Expected interface (same as notebook/databases/data_structures/bloomfilter.h):
    BloomFilter(m)        m = number of bits
    add(key)              key is a str
    contains(key) -> bool
    clear()
"""
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from BloomFilter import BloomFilter


class TestBloomFilter(unittest.TestCase):

    def test_empty_filter_contains_nothing(self):
        bf = BloomFilter(1000)
        self.assertFalse(bf.contains("apple"))

    def test_added_keys_are_found(self):
        bf = BloomFilter(1000)
        bf.add("apple")
        bf.add("banana")
        self.assertTrue(bf.contains("apple"))
        self.assertTrue(bf.contains("banana"))

    def test_adding_twice_is_fine(self):
        bf = BloomFilter(1000)
        bf.add("apple")
        bf.add("apple")
        self.assertTrue(bf.contains("apple"))

    def test_contains_does_not_change_the_filter(self):
        bf = BloomFilter(1000)
        self.assertFalse(bf.contains("apple"))
        self.assertFalse(bf.contains("apple"))
        bf.add("apple")
        self.assertTrue(bf.contains("apple"))
        self.assertTrue(bf.contains("apple"))

    def test_clear_wipes_everything(self):
        bf = BloomFilter(1000)
        bf.add("apple")
        bf.add("banana")
        bf.clear()
        self.assertFalse(bf.contains("apple"))
        self.assertFalse(bf.contains("banana"))

    def test_usable_after_clear(self):
        bf = BloomFilter(1000)
        bf.add("apple")
        bf.clear()
        bf.add("cherry")
        self.assertTrue(bf.contains("cherry"))

    def test_filters_do_not_share_state(self):
        a, b = BloomFilter(1000), BloomFilter(1000)
        a.add("apple")
        self.assertFalse(b.contains("apple"))

    def test_empty_string_key(self):
        bf = BloomFilter(1000)
        bf.add("")
        self.assertTrue(bf.contains(""))

    def test_tiny_filter_still_has_no_false_negatives(self):
        # with very few bits almost everything collides, but nothing may be lost
        bf = BloomFilter(8)
        keys = ["key" + str(i) for i in range(50)]
        for k in keys:
            bf.add(k)
        for k in keys:
            self.assertTrue(bf.contains(k), k)

    def test_no_false_negatives_over_many_keys(self):
        bf = BloomFilter(10000)
        keys = ["key" + str(i) for i in range(500)]
        for k in keys:
            bf.add(k)
        for k in keys:
            self.assertTrue(bf.contains(k), k)

    def test_false_positive_rate_stays_low(self):
        bf = BloomFilter(10000)
        for i in range(500):
            bf.add("key" + str(i))
        trials = 5000
        fp = sum(bf.contains("absent" + str(i)) for i in range(trials))
        rate = fp / trials
        print("false positive rate: %.4f (%d/%d)" % (rate, fp, trials))
        self.assertLess(rate, 0.05)

    def test_hash_cares_about_character_order(self):
        # a hash that only sums the characters cannot tell anagrams apart
        for a, b in [("listen", "silent"), ("abc", "cba"), ("ab", "ba")]:
            bf = BloomFilter(10000)
            bf.add(a)
            self.assertFalse(bf.contains(b), a + " vs " + b)

    def test_hash_spreads_similar_keys(self):
        # keys that differ in one character must not all land on the same bits:
        # after adding one of them, most of the others should be absent
        bf = BloomFilter(10000)
        bf.add("key0")
        hits = sum(bf.contains("key" + str(i)) for i in range(1, 200))
        self.assertLess(hits, 20)


if __name__ == "__main__":
    unittest.main()
