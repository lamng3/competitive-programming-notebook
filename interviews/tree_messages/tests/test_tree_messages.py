"""Tests for interviews/tree_messages

Run from anywhere:
    cpunit tree_messages --py
or from this folder:
    python3 -m unittest -v test_tree_messages
"""
import os
import random
import sys
import unittest
from collections import deque

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from solution import Node


class TestTreeMessages(unittest.TestCase):

    def run_tree(self, n, rng, fail=0.0, dup=0.0):
        par = [-1] + [rng.randrange(v) for v in range(1, n)]
        kids = [[] for _ in range(n)]
        for v in range(1, n): kids[par[v]].append(v)
        q, waits = deque(), []

        def send(to, frm, msg):
            r = rng.random()
            if r < fail: raise ConnectionError("dropped")
            q.append((to, frm, msg))
            if r < fail + dup: raise ConnectionError("delivered, but the ack was lost") # a duplicate on retry

        nodes = [Node(v, par[v], kids[v], send, sleep=waits.append, retries=50) for v in range(n)]
        nodes[0].start()
        while q:
            i = rng.randrange(len(q)) # deliver in any order
            q.rotate(-i)
            to, frm, msg = q.popleft()
            nodes[to].receive(frm, msg)
        return nodes[0].result, waits

    def test_counts_the_tree(self):
        rng = random.Random(10)
        for n in [1, 2, 5, 40]:
            self.assertEqual(self.run_tree(n, rng)[0], n)

    def test_failures_and_duplicates(self):
        rng = random.Random(11)
        for _ in range(50):
            n = rng.randint(1, 40)
            self.assertEqual(self.run_tree(n, rng, fail=0.3, dup=0.2)[0], n)

    def test_backoff_doubles_and_stops_on_success(self):
        calls, waits = [], []

        def send(to, frm, msg):
            calls.append(msg)
            if len(calls) < 3: raise ConnectionError()

        node = Node(1, 0, [], send, sleep=waits.append, retries=5, delay=1)
        self.assertTrue(node.send_with_retry(0, "1"))
        self.assertEqual(len(calls), 3) # two failures, then one success, then stop
        self.assertEqual(waits, [1, 2])
        node = Node(1, 0, [], lambda *a: (_ for _ in ()).throw(ConnectionError()), sleep=lambda s: None, retries=3)
        self.assertFalse(node.send_with_retry(0, "1"))


if __name__ == "__main__":
    unittest.main()
