"""Tests for interviews/change_directory

Run from anywhere:
    cpunit change_directory --py
or from this folder:
    python3 -m unittest -v test_change_directory
"""
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from solution import cd


LINKS = {"/home/bugs/lola": "/home/lola", "/a": "/b", "/b": "/c", "/c": "/a", "/x/y": "/z", "/p": "/q", "/q": "/r/s"}


class TestChangeDirectory(unittest.TestCase):

    def test_plain_paths(self):
        self.assertEqual(cd("/home/bugs", "."), "/home/bugs")
        self.assertEqual(cd("/home/bugs", "bunny"), "/home/bugs/bunny")
        self.assertEqual(cd("/home/bugs", "../daffy"), "/home/daffy")
        self.assertEqual(cd("/home/bugs", "/etc//nginx/"), "/etc/nginx")
        self.assertEqual(cd("/", ".."), "/")
        self.assertEqual(cd("/", "../../x"), "/x")
        self.assertEqual(cd("/a/b", ""), "/a/b")

    def test_links(self):
        self.assertEqual(cd("/home/bugs", "lola/../basketball", LINKS), "/home/basketball")
        self.assertEqual(cd("/x", "y/file", LINKS), "/z/file")
        self.assertEqual(cd("/", "p/t", LINKS), "/r/s/t") # a chain of two links
        with self.assertRaises(ValueError): cd("/", "a", LINKS)


if __name__ == "__main__":
    unittest.main()
