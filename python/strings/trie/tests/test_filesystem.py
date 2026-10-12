"""Tests for python/strings/trie/FileSystem.py

Run from anywhere:
    cpunit filesystem --py
or from this folder:
    python3 -m unittest -v test_filesystem

Interface (LeetCode 588, Design In-Memory File System):
    FileSystem()
    ls(path) -> list                    a file lists its own name, a directory its children, sorted
    mkdir(path)                         creates missing parents too
    addContentToFile(filePath, content) creates the file, or appends
    readContentFromFile(filePath) -> str
"""
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from FileSystem import FileSystem


class TestFileSystem(unittest.TestCase):

    def test_leetcode_example(self):
        fs = FileSystem()
        self.assertEqual(fs.ls("/"), [])
        fs.mkdir("/a/b/c")
        fs.addContentToFile("/a/b/c/d", "hello")
        self.assertEqual(fs.ls("/"), ["a"])
        self.assertEqual(fs.readContentFromFile("/a/b/c/d"), "hello")

    def test_ls_a_file_lists_its_name(self):
        fs = FileSystem()
        fs.addContentToFile("/a/b/notes.txt", "x")
        self.assertEqual(fs.ls("/a/b/notes.txt"), ["notes.txt"])
        self.assertEqual(fs.ls("/a/b"), ["notes.txt"])

    def test_append(self):
        fs = FileSystem()
        fs.addContentToFile("/f", "hello")
        fs.addContentToFile("/f", " world")
        self.assertEqual(fs.readContentFromFile("/f"), "hello world")

    def test_ls_is_sorted_and_mixes_files_and_dirs(self):
        fs = FileSystem()
        fs.mkdir("/zeta")
        fs.addContentToFile("/beta", "b")
        fs.mkdir("/alpha/inner")
        self.assertEqual(fs.ls("/"), ["alpha", "beta", "zeta"])
        self.assertEqual(fs.ls("/alpha"), ["inner"])

    def test_mkdir_is_idempotent(self):
        fs = FileSystem()
        fs.mkdir("/a/b")
        fs.mkdir("/a/b")
        fs.mkdir("/a")
        self.assertEqual(fs.ls("/a"), ["b"])
        self.assertEqual(fs.ls("/a/b"), [])

    def test_empty_file(self):
        fs = FileSystem()
        fs.addContentToFile("/empty", "")
        self.assertEqual(fs.readContentFromFile("/empty"), "")
        self.assertEqual(fs.ls("/empty"), ["empty"])


if __name__ == "__main__":
    unittest.main()
