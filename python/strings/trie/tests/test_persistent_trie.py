"""Tests for python/strings/trie/PersistentTrie.py

Run from anywhere:
    cpunit persistent_trie --py
or from this folder:
    python3 -m unittest -v test_persistent_trie

Interface:
    PersistentTrie()
    insert(word, version=None) -> int       builds on version (default latest), returns the new version
    erase(word, version=None) -> int|None   new version without word, None if word is not in that version
    search(word, version=None) -> bool
    starts_with(prefix, version=None) -> bool
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from PersistentTrie import PersistentTrie


class TestPersistentTrie(unittest.TestCase):

    def test_insert_keeps_old_versions(self):
        t = PersistentTrie()
        v1 = t.insert("apple")
        v2 = t.insert("app")
        self.assertFalse(t.search("apple", 0))
        self.assertTrue(t.search("apple", v1))
        self.assertFalse(t.search("app", v1))
        self.assertTrue(t.search("app", v2))

    def test_insert_branches_from_an_old_version(self):
        t = PersistentTrie()
        v1 = t.insert("a")
        t.insert("b")
        v3 = t.insert("c", v1)
        self.assertTrue(t.search("a", v3))
        self.assertTrue(t.search("c", v3))
        self.assertFalse(t.search("b", v3))

    def test_erase_creates_a_new_version(self):
        t = PersistentTrie()
        v1 = t.insert("apple")
        v2 = t.erase("apple")
        self.assertEqual(v2, v1 + 1)
        self.assertFalse(t.search("apple", v2))
        self.assertTrue(t.search("apple", v1))

    def test_erase_missing_word_returns_none(self):
        t = PersistentTrie()
        t.insert("apple")
        n = len(t.roots)
        self.assertIsNone(t.erase("app"))
        self.assertIsNone(t.erase("banana"))
        self.assertIsNone(t.erase("applesauce"))
        self.assertEqual(len(t.roots), n)

    def test_erase_prunes_dead_branch(self):
        t = PersistentTrie()
        t.insert("apple")
        v = t.erase("apple")
        self.assertFalse(t.starts_with("a", v))
        self.assertEqual(t.roots[v].children, {})

    def test_erase_keeps_shared_prefix(self):
        t = PersistentTrie()
        t.insert("app")
        t.insert("apple")
        v = t.erase("apple")
        self.assertTrue(t.search("app", v))
        self.assertFalse(t.search("apple", v))
        self.assertFalse(t.starts_with("appl", v))

    def test_erase_prefix_word_keeps_longer_word(self):
        t = PersistentTrie()
        t.insert("app")
        t.insert("apple")
        v = t.erase("app")
        self.assertFalse(t.search("app", v))
        self.assertTrue(t.search("apple", v))
        self.assertTrue(t.starts_with("app", v))

    def test_erase_from_an_old_version(self):
        t = PersistentTrie()
        v1 = t.insert("a")
        v2 = t.insert("b")
        v3 = t.erase("a", v1)
        self.assertFalse(t.search("a", v3))
        self.assertFalse(t.search("b", v3))
        self.assertTrue(t.search("a", v2) and t.search("b", v2))

    def test_erase_then_reinsert(self):
        t = PersistentTrie()
        t.insert("abc")
        t.erase("abc")
        v = t.insert("abc")
        self.assertTrue(t.search("abc", v))

    def test_random_against_set_per_version(self):
        rnd = random.Random(7)
        words = ["".join(rnd.choice("ab") for _ in range(rnd.randint(1, 4))) for _ in range(12)]
        t = PersistentTrie()
        sets = [set()]
        for _ in range(300):
            ver = rnd.randrange(len(sets))
            w = rnd.choice(words)
            if rnd.random() < 0.5:
                v = t.insert(w, ver)
                sets.append(sets[ver] | {w})
            else:
                v = t.erase(w, ver)
                if w in sets[ver]:
                    self.assertEqual(v, len(sets))
                    sets.append(sets[ver] - {w})
                else:
                    self.assertIsNone(v)
        for ver, s in enumerate(sets):
            for w in words:
                self.assertEqual(t.search(w, ver), w in s, (ver, w))
                self.assertEqual(t.starts_with(w, ver), any(x.startswith(w) for x in s), (ver, w))


if __name__ == "__main__":
    unittest.main()
