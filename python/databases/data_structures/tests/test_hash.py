"""Tests for python/databases/data_structures/utils/hash.py

Run from anywhere:
    cpunit hash
"""
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from utils.hash import MASK, polynomial, djb2, fnv1a, splitmix64, generate_hashes, hash_with_seed, random_seeds

HASHES = [polynomial, djb2, fnv1a]


class TestHash(unittest.TestCase):

    def test_known_values(self):
        self.assertEqual(polynomial("a"), 97)
        self.assertEqual(polynomial("ab"), 97 * 31 + 98)
        self.assertEqual(djb2(""), 5381)
        self.assertEqual(djb2("a"), 5381 * 33 + 97)
        self.assertEqual(fnv1a("a"), 0xaf63dc4c8601ec8c)        # published FNV-1a 64 test vectors
        self.assertEqual(fnv1a("foobar"), 0x85944171f73967e8)
        self.assertEqual(splitmix64(0), 0xe220a8397b1dcdaf)

    def test_same_key_same_hash(self):
        for h in HASHES:
            self.assertEqual(h("apple"), h("apple"))

    def test_fits_in_64_bits_on_long_keys(self):
        for h in HASHES:
            self.assertLessEqual(h("x" * 1000), MASK)
            self.assertGreaterEqual(h("x" * 1000), 0)

    def test_character_order_matters(self):
        for h in HASHES:
            self.assertNotEqual(h("listen"), h("silent"), h.__name__)

    def test_different_keys_differ(self):
        for h in HASHES:
            values = {h("key" + str(i)) for i in range(1000)}
            self.assertEqual(len(values), 1000, h.__name__)

    def test_seed_changes_the_hash(self):
        self.assertNotEqual(djb2("apple", 1), djb2("apple", 2))
        self.assertNotEqual(fnv1a("apple", 1), fnv1a("apple", 2))

    def test_spreads_over_buckets(self):
        # 1000 similar keys into 100 buckets: no bucket should hold a big share
        for h in HASHES:
            counts = [0] * 100
            for i in range(1000):
                counts[h("key" + str(i)) % 100] += 1
            self.assertLess(max(counts), 40, h.__name__)

    def test_hash_with_seed_is_repeatable(self):
        self.assertEqual(hash_with_seed("apple", 7), hash_with_seed("apple", 7))
        self.assertEqual(hash_with_seed(42, 7), hash_with_seed(42, 7))
        self.assertLessEqual(hash_with_seed("apple", 7), MASK)

    def test_hash_with_seed_changes_with_the_seed(self):
        values = {hash_with_seed("apple", s) for s in range(100)}
        self.assertEqual(len(values), 100)

    def test_hash_with_seed_takes_str_and_int_keys(self):
        self.assertNotEqual(hash_with_seed(1, 5), hash_with_seed(2, 5))
        self.assertNotEqual(hash_with_seed("a", 5), hash_with_seed("b", 5))

    def test_two_seeds_pick_different_columns(self):
        # rows must be independent: two seeds rarely send the same key to the same column
        width = 100
        same = sum(hash_with_seed("key" + str(i), 1) % width == hash_with_seed("key" + str(i), 2) % width
                   for i in range(1000))
        self.assertLess(same, 50)       # about 10 expected, 1000 would mean the seed does nothing

    def test_seeded_hash_spreads_over_columns(self):
        counts = [0] * 100
        for i in range(1000):
            counts[hash_with_seed(i, 3) % 100] += 1
        self.assertLess(max(counts), 40)

    def test_random_seeds(self):
        seeds = random_seeds(5)
        self.assertEqual(len(seeds), 5)
        self.assertEqual(len(set(seeds)), 5)
        for s in seeds:
            self.assertTrue(0 <= s <= MASK)
        self.assertNotEqual(seeds, random_seeds(5))
        self.assertEqual(random_seeds(0), [])

    def test_generate_hashes(self):
        hs = generate_hashes(4)
        self.assertEqual(len(hs), 4)
        values = [h("apple") for h in hs]
        self.assertEqual(len(set(values)), 4)
        self.assertEqual(values, [h("apple") for h in hs])
        for v in values:
            self.assertLessEqual(v, MASK)


if __name__ == "__main__":
    unittest.main()
