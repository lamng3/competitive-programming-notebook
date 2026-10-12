"""Tests for interviews/number_of_orders_in_the_backlog

Run from anywhere:
    cpunit number_of_orders_in_the_backlog --py
or from this folder:
    python3 -m unittest -v test_number_of_orders_in_the_backlog
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from solution import Solution as Backlog


class TestNumberOfOrdersInTheBacklog(unittest.TestCase):

    def test_1801_backlog(self):
        self.assertEqual(Backlog().getNumberOfBacklogOrders([[10, 5, 0], [15, 2, 1], [25, 1, 1], [30, 4, 0]]), 6)
        self.assertEqual(Backlog().getNumberOfBacklogOrders([[7, 1000000000, 1], [15, 3, 0], [5, 999999995, 0], [5, 1, 1]]), 999999984)
        rng = random.Random(6)
        for _ in range(200):
            orders = [[rng.randint(1, 6), rng.randint(1, 5), rng.randint(0, 1)] for _ in range(rng.randint(1, 15))]
            buy, sell = [], [] # brute force: lists of [price, amount]
            for p, a, t in orders:
                while a:
                    book = sell if t == 0 else buy
                    ok = [o for o in book if (o[0] <= p if t == 0 else o[0] >= p)]
                    if not ok: break
                    best = min(ok) if t == 0 else max(ok)
                    x = min(a, best[1])
                    a -= x
                    best[1] -= x
                    if best[1] == 0: book.remove(best)
                if a: (buy if t == 0 else sell).append([p, a])
            self.assertEqual(Backlog().getNumberOfBacklogOrders(orders), sum(o[1] for o in buy + sell))


if __name__ == "__main__":
    unittest.main()
