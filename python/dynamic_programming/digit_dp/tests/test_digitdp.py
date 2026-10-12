"""Tests for python/dynamic_programming/digit_dp/DigitDP.py

Run from anywhere:
    cpunit digitdp --py
or from this folder:
    python3 -m unittest -v test_digitdp
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from DigitDP import count_up_to


class TestDigitDP(unittest.TestCase):

    def test_digit_sum_divisible(self):
        for k in (1, 3, 7):
            for N in (0, 1, 9, 10, 99, 100, 1234, 5000):
                want = sum(1 for x in range(1, N + 1) if sum(map(int, str(x))) % k == 0)
                self.assertEqual(count_up_to(N, 0, lambda s, d: (s + d) % k, lambda s: s == 0), want, (N, k))

    def test_distinct_digits_reject(self):
        step = lambda used, d: None if used >> d & 1 else used | 1 << d
        for N in (5, 10, 11, 100, 987, 2026):
            want = sum(1 for x in range(1, N + 1) if len(set(str(x))) == len(str(x)))
            self.assertEqual(count_up_to(N, 0, step, lambda s: True), want, N)


if __name__ == "__main__":
    unittest.main()
