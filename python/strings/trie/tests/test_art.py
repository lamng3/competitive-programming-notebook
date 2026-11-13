"""Tests for python/strings/trie/ART.py

Run from anywhere:
    cpunit art --py
or from this folder:
    python3 -m unittest -v test_art

Interface (follows the pseudo code of the ART paper):
    ART()
    insert(word)
    search(word) -> bool
    startsWith(prefix) -> bool
    findChild(node, c) -> node or None      c is one character
Keys are the word plus a "\0" terminator, so words cannot contain "\0".
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from ART import ART, SIZES


def check_shape(t):
    # every inner node branches, and its size class fits its children
    def dfs(node):
        if node.end: return
        assert node.size in SIZES
        lo = SIZES[SIZES.index(node.size) - 1] + 1 if node.size > 4 else 2
        assert lo <= len(node.children) <= node.size
        assert node.keys == sorted(node.children) # keys stay sorted, range scans rely on it
        for child in node.children.values():
            dfs(child)
    if t.root is not None: dfs(t.root)


def shape_of(node):
    if node is None: return None
    if node.end: return node.content
    return (node.content, node.size, sorted((c, shape_of(ch)) for c, ch in node.children.items()))


class TestART(unittest.TestCase):

    def test_leetcode_208(self):
        t = ART()
        t.insert("apple")
        self.assertTrue(t.search("apple"))
        self.assertFalse(t.search("app"))
        self.assertTrue(t.startsWith("app"))
        t.insert("app")
        self.assertTrue(t.search("app"))

    def test_empty_word_and_empty_trie(self):
        t = ART()
        self.assertFalse(t.search(""))
        self.assertTrue(t.startsWith(""))
        t.insert("")
        self.assertTrue(t.search(""))

    def test_lazy_expansion(self):
        t = ART()
        t.insert("romane")
        self.assertTrue(t.isLeaf(t.root))  # one leaf holds the whole key, no chain of nodes
        self.assertEqual(t.root.content, "romane\0")

    def test_leaf_expands_into_node4_with_prefix(self):
        t = ART()
        t.insert("romane")
        t.insert("romanus")
        self.assertEqual((t.root.size, t.root.content, len(t.root.children)), (4, "roman", 2))
        self.assertTrue(t.isLeaf(t.findChild(t.root, "e")))
        self.assertTrue(t.isLeaf(t.findChild(t.root, "u")))

    def test_split(self):
        t = ART()
        for w in ["romane", "romanus", "romulus", "rubens", "ruber", "rubicon", "rubicundus"]:
            t.insert(w)
        self.assertEqual(t.root.content, "r")  # r branches into o and u
        self.assertEqual(t.findChild(t.root, "o").content, "m")  # o is the branch char, m is left over
        self.assertTrue(t.search("romane") and t.search("romanus") and t.search("rubicundus"))
        self.assertFalse(t.search("roman"))
        self.assertFalse(t.search("rubic"))
        self.assertTrue(t.startsWith("rubic"))
        self.assertTrue(t.startsWith("rom"))
        self.assertFalse(t.startsWith("rox"))
        check_shape(t)

    def test_word_that_is_a_prefix_of_another(self):
        t = ART()
        t.insert("abcdef")
        t.insert("abc")
        self.assertTrue(t.search("abc") and t.search("abcdef"))
        self.assertFalse(t.search("abcd"))
        t.insert("abcd")
        self.assertTrue(t.search("abcd"))
        check_shape(t)

    def test_duplicate_insert_changes_nothing(self):
        t = ART()
        for w in ["car", "cat", "cat"]:
            t.insert(w)
        self.assertEqual(len(t.root.children), 2)
        check_shape(t)

    def test_startswith_inside_compressed_path(self):
        t = ART()
        t.insert("abcdef")
        t.insert("abcxyz")
        for p in ["", "a", "abc", "abcd", "abcdef", "abcxy"]:
            self.assertTrue(t.startsWith(p), p)
        for p in ["b", "abx", "abcdefg", "abcxyzz"]:
            self.assertFalse(t.startsWith(p), p)

    def test_growth_through_size_classes(self):
        t = ART()
        sizes = {}
        for i, ch in enumerate("abcdefghijklmnopqrstuvwxyz", 1):
            t.insert("x" + ch)
            sizes[i] = t.root.size if i > 1 else 4  # the root holds the shared "x"
        self.assertEqual((sizes[2], sizes[4], sizes[5]), (4, 4, 16))
        self.assertEqual((sizes[16], sizes[17], sizes[26]), (16, 48, 48))
        self.assertTrue(all(t.search("x" + c) for c in "abcdefghijklmnopqrstuvwxyz"))
        check_shape(t)

    def test_node256(self):
        t = ART()
        for i in range(60):
            t.insert("k" + chr(i + 33))
        self.assertEqual(t.root.size, 256)
        self.assertTrue(all(t.search("k" + chr(i + 33)) for i in range(60)))
        self.assertFalse(t.search("k" + chr(33 + 60)))
        check_shape(t)

    def test_failed_search_changes_nothing(self):
        t = ART()
        t.insert("cat")
        t.insert("car")
        before = shape_of(t.root)
        t.search("dog")
        t.search("ca")
        t.startsWith("cow")
        t.findChild(t.root, "z")
        self.assertEqual(shape_of(t.root), before)

    def test_latin1(self):
        t = ART()
        for w in ["café", "cafe", "cafés", "naïve"]:
            t.insert(w)
        self.assertTrue(t.search("café") and t.search("naïve"))
        self.assertTrue(t.startsWith("caf"))
        self.assertFalse(t.search("caf"))

    def test_random_against_brute_force(self):
        rng = random.Random(7)
        for _ in range(100):
            t, stored = ART(), set()
            for _ in range(rng.randint(0, 60)):
                w = "".join(rng.choice("abc") for _ in range(rng.randint(0, 6)))
                t.insert(w)
                stored.add(w)
                check_shape(t)
            for _ in range(60):
                q = "".join(rng.choice("abc") for _ in range(rng.randint(0, 7)))
                self.assertEqual(t.search(q), q in stored, q)
                self.assertEqual(t.startsWith(q), not q or any(w.startswith(q) for w in stored), q)

    def test_random_wide_alphabet(self):
        rng = random.Random(3)
        t, stored = ART(), set()
        for _ in range(3000):
            w = "".join(chr(rng.randint(97, 140)) for _ in range(rng.randint(1, 3)))
            t.insert(w)
            stored.add(w)
        check_shape(t)
        for w in stored:
            self.assertTrue(t.search(w))
        self.assertFalse(t.search("zzzz"))


if __name__ == "__main__":
    unittest.main()
