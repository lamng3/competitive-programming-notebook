"""Tests for python/databases/data_structures/Skiplist.py

Run from anywhere:
    cpunit skiplist --py
or from this folder:
    python3 -m unittest -v test_skiplist

Interface (LeetCode 1206, Design Skiplist):
    Skiplist()
    search(target) -> bool
    add(num)                  duplicates are allowed
    erase(num) -> bool        removes ONE copy, False if there is none
"""
import os
import random
import sys
import time
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from Skiplist import Skiplist


class TestSkiplist(unittest.TestCase):

    def test_leetcode_example(self):
        s = Skiplist()
        s.add(1)
        s.add(2)
        s.add(3)
        self.assertFalse(s.search(0))
        s.add(4)
        self.assertTrue(s.search(1))
        self.assertFalse(s.erase(0))
        self.assertTrue(s.erase(1))
        self.assertFalse(s.search(1))

    def test_empty_list(self):
        s = Skiplist()
        self.assertFalse(s.search(5))
        self.assertFalse(s.erase(5))

    def test_added_values_are_found(self):
        s = Skiplist()
        for x in [5, 1, 9, 3]:
            s.add(x)
        for x in [5, 1, 9, 3]:
            self.assertTrue(s.search(x), x)

    def test_missing_values_are_not_found(self):
        s = Skiplist()
        for x in [10, 20, 30]:
            s.add(x)
        self.assertFalse(s.search(5))    # below the smallest
        self.assertFalse(s.search(15))   # between two values
        self.assertFalse(s.search(99))   # above the largest

    def test_zero_and_negative_values(self):
        # the sentinel head must never be mistaken for a real value
        s = Skiplist()
        for x in [0, -1, -5, 7]:
            s.add(x)
        for x in [0, -1, -5, 7]:
            self.assertTrue(s.search(x), x)
        self.assertTrue(s.erase(-1))
        self.assertFalse(s.search(-1))

    def test_erase_removes_only_that_value(self):
        s = Skiplist()
        for x in [1, 2, 3]:
            s.add(x)
        self.assertTrue(s.erase(2))
        self.assertTrue(s.search(1))
        self.assertFalse(s.search(2))
        self.assertTrue(s.search(3))

    def test_erase_twice_fails_the_second_time(self):
        s = Skiplist()
        s.add(4)
        self.assertTrue(s.erase(4))
        self.assertFalse(s.erase(4))

    def test_duplicates_are_separate_copies(self):
        s = Skiplist()
        s.add(1)
        s.add(1)
        self.assertTrue(s.erase(1))
        self.assertTrue(s.search(1))     # one copy is left
        self.assertTrue(s.erase(1))
        self.assertFalse(s.search(1))
        self.assertFalse(s.erase(1))

    def test_many_duplicates(self):
        s = Skiplist()
        for _ in range(50):
            s.add(7)
        for _ in range(50):
            self.assertTrue(s.erase(7))
        self.assertFalse(s.search(7))
        self.assertFalse(s.erase(7))

    def test_add_after_erase(self):
        s = Skiplist()
        s.add(3)
        s.erase(3)
        s.add(3)
        self.assertTrue(s.search(3))

    def test_ascending_and_descending_inserts(self):
        for order in (range(2000), range(1999, -1, -1)):
            s = Skiplist()
            for x in order:
                s.add(x)
            for x in range(2000):
                self.assertTrue(s.search(x), x)
            self.assertFalse(s.search(2000))
            for x in range(2000):
                self.assertTrue(s.erase(x), x)
            for x in range(2000):
                self.assertFalse(s.search(x), x)

    def test_random_operations_match_a_plain_list(self):
        # the plain list is slow but obviously correct: compare against it
        for seed in range(30):
            rng = random.Random(seed)
            s, ref = Skiplist(), []
            for _ in range(400):
                op, v = rng.choice("ase"), rng.randint(0, 15)
                if op == "a":
                    s.add(v)
                    ref.append(v)
                elif op == "s":
                    self.assertEqual(s.search(v), v in ref, (seed, op, v))
                else:
                    had = v in ref
                    if had:
                        ref.remove(v)
                    self.assertEqual(s.erase(v), had, (seed, op, v))

    def test_is_fast_enough(self):
        # a plain sorted linked list needs O(n) per operation and is far too slow here
        n = 20000
        values = list(range(n))
        random.Random(1).shuffle(values)
        start = time.time()
        s = Skiplist()
        for x in values:
            s.add(x)
        for x in values:
            self.assertTrue(s.search(x))
        for x in values:
            self.assertTrue(s.erase(x))
        self.assertLess(time.time() - start, 8.0)


if __name__ == "__main__":
    unittest.main()
