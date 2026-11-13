"""Tests for python/strings/trie/PersistentART.py

Run from anywhere:
    cpunit persistent_art --py
or from this folder:
    python3 -m unittest -v test_persistent_art

Interface:
    PersistentART()
    insert(word, version=None) -> int       builds on version (default latest), returns the new version
    erase(word, version=None) -> int|None   new version without word, None if word is not in that version
    search(word, version=None) -> bool
    startsWith(prefix, version=None) -> bool
    findChild(node, c) -> node or None
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from PersistentART import PersistentART, SIZES


def check_shape(root):
    # every node is needed: it ends a word or branches, and size fits its children
    def dfs(node, is_root):
        assert len(node.children) <= node.size and node.size in SIZES
        if not is_root:
            assert node.end or len(node.children) >= 2
        for child in node.children.values():
            dfs(child, False)
    dfs(root, True)


def snapshot_of(node):
    # the whole tree as plain data, to compare a version before and after later changes
    return (node.content, node.end, node.size, {c: snapshot_of(ch) for c, ch in node.children.items()})


class TestPersistentART(unittest.TestCase):

    def test_insert_keeps_old_versions(self):
        t = PersistentART()
        v1 = t.insert("apple")
        v2 = t.insert("app")
        self.assertFalse(t.search("apple", 0))
        self.assertTrue(t.search("apple", v1))
        self.assertFalse(t.search("app", v1))
        self.assertTrue(t.search("app", v2))

    def test_insert_branches_from_an_old_version(self):
        t = PersistentART()
        v1 = t.insert("a")
        t.insert("b")
        v3 = t.insert("c", v1)
        self.assertTrue(t.search("a", v3))
        self.assertTrue(t.search("c", v3))
        self.assertFalse(t.search("b", v3))

    def test_split_does_not_change_old_version(self):
        t = PersistentART()
        v1 = t.insert("romane")
        before = snapshot_of(t.roots[v1])
        t.insert("romanus")
        t.insert("rubens")
        self.assertEqual(snapshot_of(t.roots[v1]), before)
        self.assertEqual(t.findChild(t.roots[v1], "r").content, "omane")
        self.assertFalse(t.search("romanus", v1))

    def test_untouched_subtrees_are_shared(self):
        t = PersistentART()
        for w in ["apple", "banana", "cherry"]:
            t.insert(w)
        v = t.insert("avocado")
        old, new = t.roots[v - 1], t.roots[v]
        self.assertIs(t.findChild(old, "b"), t.findChild(new, "b"))
        self.assertIs(t.findChild(old, "c"), t.findChild(new, "c"))
        self.assertIsNot(t.findChild(old, "a"), t.findChild(new, "a"))

    def test_erase_creates_a_new_version(self):
        t = PersistentART()
        v1 = t.insert("apple")
        v2 = t.erase("apple")
        self.assertEqual(v2, v1 + 1)
        self.assertFalse(t.search("apple", v2))
        self.assertTrue(t.search("apple", v1))
        self.assertEqual(t.roots[v2].children, {})

    def test_erase_missing_word_returns_none(self):
        t = PersistentART()
        t.insert("apple")
        n = len(t.roots)
        self.assertIsNone(t.erase("app"))
        self.assertIsNone(t.erase("banana"))
        self.assertIsNone(t.erase("applesauce"))
        self.assertEqual(len(t.roots), n)

    def test_erase_collapse_does_not_change_old_version(self):
        t = PersistentART()
        t.insert("car")
        v = t.insert("cat")
        before = snapshot_of(t.roots[v])
        v3 = t.erase("cat")
        self.assertEqual(snapshot_of(t.roots[v]), before)
        node = t.findChild(t.roots[v3], "c")
        self.assertEqual((node.content, node.children), ("ar", {}))
        check_shape(t.roots[v3])

    def test_erase_prefix_word_keeps_longer_word(self):
        t = PersistentART()
        t.insert("app")
        t.insert("apple")
        v = t.erase("app")
        self.assertFalse(t.search("app", v))
        self.assertTrue(t.search("apple", v))
        self.assertTrue(t.search("app", v - 1))
        check_shape(t.roots[v])

    def test_erase_from_an_old_version(self):
        t = PersistentART()
        v1 = t.insert("a")
        v2 = t.insert("b")
        v3 = t.erase("a", v1)
        self.assertFalse(t.search("a", v3))
        self.assertFalse(t.search("b", v3))
        self.assertTrue(t.search("a", v2) and t.search("b", v2))

    def test_startswith_per_version(self):
        t = PersistentART()
        v1 = t.insert("abcdef")
        v2 = t.erase("abcdef")
        self.assertTrue(t.startsWith("abc", v1))
        self.assertFalse(t.startsWith("abc", v2))
        self.assertTrue(t.startsWith("", v2))

    def test_random_against_set_per_version(self):
        rnd = random.Random(7)
        for _ in range(30):
            words = ["".join(rnd.choice("abc") for _ in range(rnd.randint(0, 5))) for _ in range(12)]
            t = PersistentART()
            sets = [set()]
            for _ in range(80):
                ver = rnd.randrange(len(sets))
                w = rnd.choice(words)
                if rnd.random() < 0.55:
                    v = t.insert(w, ver)
                    sets.append(sets[ver] | {w})
                else:
                    v = t.erase(w, ver)
                    if w in sets[ver]:
                        self.assertEqual(v, len(sets))
                        sets.append(sets[ver] - {w})
                    else:
                        self.assertIsNone(v)
                if v is not None:
                    check_shape(t.roots[v])
            for ver, s in enumerate(sets):
                check_shape(t.roots[ver])
                for q in words:
                    self.assertEqual(t.search(q, ver), q in s, (ver, q))
                    self.assertEqual(t.startsWith(q, ver), not q or any(x.startswith(q) for x in s), (ver, q))


if __name__ == "__main__":
    unittest.main()
