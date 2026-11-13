"""Tests for python/strings/trie/ARTIterator.py

Run from anywhere:
    cpunit art_iterator --py
or from this folder:
    python3 -m unittest -v test_art_iterator

Interface:
    ARTIterator(art, word, after=False)   starts at the first word >= word (> word if after)
    RangeIter(art, lo, hi)
    hasNext() -> bool                     both classes
    next() -> str                         next stored word in sorted order (RangeIter: only lo <= s <= hi)
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from ART import ART
from ARTIterator import ARTIterator, RangeIter


def build(words):
    t = ART()
    for w in words: t.insert(w)
    return t


def scan(t, lo, hi):
    it = RangeIter(t, lo, hi)
    res = []
    while it.hasNext(): res.append(it.next())
    return res


def walk(t, word, after=False):
    it = ARTIterator(t, word, after)
    res = []
    while it.hasNext(): res.append(it.next())
    return res


def brute(words, lo, hi):
    return sorted(w for w in set(words) if lo <= w <= hi)


class TestARTIterator(unittest.TestCase):
    def test_lower_bound(self):
        t = build(["a", "ab", "b", "d"])
        self.assertEqual(walk(t, "ab"), ["ab", "b", "d"])
        self.assertEqual(walk(t, "c"), ["d"])
        self.assertEqual(walk(t, "e"), [])

    def test_after(self):
        t = build(["a", "ab", "b", "d"])
        self.assertEqual(walk(t, "ab", True), ["b", "d"])
        self.assertEqual(walk(t, "c", True), ["d"])
        self.assertEqual(walk(t, "d", True), [])

    def test_random(self):
        rng = random.Random(2)
        for _ in range(200):
            words = ["".join(rng.choice("abc") for _ in range(rng.randint(0, 6))) for _ in range(rng.randint(0, 30))]
            t = build(words)
            for _ in range(20):
                w = "".join(rng.choice("abcd") for _ in range(rng.randint(0, 7)))
                self.assertEqual(walk(t, w), sorted(x for x in set(words) if x >= w))
                self.assertEqual(walk(t, w, True), sorted(x for x in set(words) if x > w))


class TestRangeIter(unittest.TestCase):
    def test_empty_tree(self):
        self.assertEqual(scan(ART(), "a", "z"), [])

    def test_single_word(self):
        t = build(["abc"])
        self.assertEqual(scan(t, "a", "b"), ["abc"])
        self.assertEqual(scan(t, "abc", "abc"), ["abc"])
        self.assertEqual(scan(t, "abd", "z"), [])
        self.assertEqual(scan(t, "", "abb"), [])

    def test_prefix_words(self):
        words = ["a", "ab", "abc", "abd", "b"]
        t = build(words)
        self.assertEqual(scan(t, "ab", "abc"), ["ab", "abc"])
        self.assertEqual(scan(t, "", "zzz"), words)

    def test_lo_gt_hi(self):
        t = build(["a", "b", "c"])
        self.assertEqual(scan(t, "c", "a"), [])

    def test_bounds_not_stored(self):
        t = build(["apple", "apply", "banana", "band", "bandana", "cat"])
        self.assertEqual(scan(t, "appm", "bana"), [])
        self.assertEqual(scan(t, "applz", "bandz"), ["banana", "band", "bandana"])

    def test_random(self):
        rng = random.Random(1)
        for _ in range(300):
            words = ["".join(rng.choice("abc") for _ in range(rng.randint(0, 6))) for _ in range(rng.randint(0, 30))]
            t = build(words)
            for _ in range(20):
                lo = "".join(rng.choice("abcd") for _ in range(rng.randint(0, 7)))
                hi = "".join(rng.choice("abcd") for _ in range(rng.randint(0, 7)))
                self.assertEqual(scan(t, lo, hi), brute(words, lo, hi), (words, lo, hi))


if __name__ == "__main__":
    unittest.main()
