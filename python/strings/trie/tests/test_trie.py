"""Tests for python/strings/trie/Trie.py

Run from anywhere:
    cpunit trie --py
or from this folder:
    python3 -m unittest -v test_trie

Interface (LeetCode 208, Implement Trie, and 211, Add and Search Word):
    Trie()
    insert(word)
    search(word) -> bool        "." matches any one letter
    startsWith(prefix) -> bool  "." works here too
    words(prefix="") -> list    every stored word with that prefix, sorted
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from Trie import Trie


class TestTrie(unittest.TestCase):

    def test_leetcode_208(self):
        t = Trie()
        t.insert("apple")
        self.assertTrue(t.search("apple"))
        self.assertFalse(t.search("app"))
        self.assertTrue(t.startsWith("app"))
        t.insert("app")
        self.assertTrue(t.search("app"))

    def test_leetcode_211(self):
        t = Trie()
        for w in ["bad", "dad", "mad"]:
            t.insert(w)
        self.assertFalse(t.search("pad"))
        self.assertTrue(t.search("bad"))
        self.assertTrue(t.search(".ad"))
        self.assertTrue(t.search("b.."))
        self.assertFalse(t.search("b..."))
        self.assertFalse(t.search(".."))

    def test_empty_word_and_empty_trie(self):
        t = Trie()
        self.assertFalse(t.search(""))
        self.assertTrue(t.startsWith(""))
        self.assertEqual(t.words(), [])
        t.insert("")
        self.assertTrue(t.search(""))
        self.assertEqual(t.words(), [""])

    def test_failed_search_adds_no_nodes(self):
        t = Trie()
        t.insert("cat")
        t.search("dog")
        t.startsWith("cow")
        t.search("c.x")
        t.words("zebra")
        self.assertEqual(list(t.root.children), ["c"])
        self.assertEqual(list(t.root.children["c"].children), ["a"])

    def test_words_sorted_with_prefix(self):
        t = Trie()
        for w in ["banana", "app", "apple", "apply", "ape", "b"]:
            t.insert(w)
        self.assertEqual(t.words("ap"), ["ape", "app", "apple", "apply"])
        self.assertEqual(t.words("app"), ["app", "apple", "apply"])
        self.assertEqual(t.words(), sorted(["banana", "app", "apple", "apply", "ape", "b"]))
        self.assertEqual(t.words("c"), [])

    def test_lexicographical_numbers(self):
        # LeetCode 386
        t = Trie()
        for i in range(1, 14):
            t.insert(str(i))
        self.assertEqual([int(w) for w in t.words()], [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9])

    def test_random_against_brute_force(self):
        rng = random.Random(7)
        for _ in range(50):
            t, stored = Trie(), set()
            for _ in range(rng.randint(0, 30)):
                w = "".join(rng.choice("abc") for _ in range(rng.randint(0, 5)))
                t.insert(w)
                stored.add(w)
            for _ in range(60):
                q = "".join(rng.choice("abc.") for _ in range(rng.randint(0, 5)))
                match = lambda w, n: len(w) >= n and all(p == "." or p == c for p, c in zip(q, w))
                self.assertEqual(t.search(q), any(len(w) == len(q) and match(w, len(q)) for w in stored), q)
                self.assertEqual(t.startsWith(q), not q or any(match(w, len(q)) for w in stored), q)  # "" is a prefix of everything
            p = "".join(rng.choice("abc") for _ in range(rng.randint(0, 2)))
            self.assertEqual(t.words(p), sorted(w for w in stored if w.startswith(p)))


if __name__ == "__main__":
    unittest.main()
