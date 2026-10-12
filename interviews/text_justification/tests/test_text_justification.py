"""Tests for interviews/text_justification

Run from anywhere:
    cpunit text_justification --py
or from this folder:
    python3 -m unittest -v test_text_justification
"""
import os
import random
import re
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from solution import Solution as Justify


class TestTextJustification(unittest.TestCase):

    def test_68_text_justification(self):
        self.assertEqual(Justify().fullJustify(["This", "is", "an", "example", "of", "text", "justification."], 16),
                         ["This    is    an", "example  of text", "justification.  "])
        self.assertEqual(Justify().fullJustify(["What", "must", "be", "acknowledgment", "shall", "be"], 16),
                         ["What   must   be", "acknowledgment  ", "shall be        "])
        rng = random.Random(4)
        for _ in range(200):
            W = rng.randint(5, 20)
            words = ["".join(rng.choice("ab") for _ in range(rng.randint(1, W))) for _ in range(rng.randint(1, 12))]
            lines = Justify().fullJustify(words, W)
            self.assertTrue(all(len(l) == W for l in lines))
            self.assertEqual(" ".join(" ".join(lines).split()), " ".join(words)) # same words, same order
            for l in lines[:-1]:
                inner = [len(x) for x in re.findall(r"(?<=\S) +(?=\S)", l)]
                if inner: self.assertLessEqual(max(inner) - min(inner), 1)
                if inner: self.assertEqual(inner, sorted(inner, reverse=True))


if __name__ == "__main__":
    unittest.main()
