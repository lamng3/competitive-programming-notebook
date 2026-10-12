"""Tests for interviews/practical

Run from anywhere:
    cpunit interviewpractical --py
or from this folder:
    python3 -m unittest -v test_interviewpractical
"""
import os
import random
import sys
import unittest
from collections import deque

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from ChangeDirectory import cd
from InfectionSimulation import last_recovery_day
from IPv4Iterator import IPv4Iterator, cidr_range, to_int, to_str
from TreeMessages import Node

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


class TestIPv4(unittest.TestCase):

    def test_parse_format(self):
        for ip in ["0.0.0.0", "255.255.255.255", "10.0.1.254"]:
            self.assertEqual(to_str(to_int(ip)), ip)
        for bad in ["1.2.3", "1.2.3.256", "a.b.c.d", "1.2.3.4.5", "1..2.3"]:
            with self.assertRaises(ValueError): to_int(bad)

    def test_ranges(self):
        self.assertEqual(list(IPv4Iterator("255.255.14.254", "255.255.15.1")),
                         ["255.255.14.254", "255.255.14.255", "255.255.15.0", "255.255.15.1"])
        self.assertEqual(list(IPv4Iterator("0.0.1.1", "0.0.0.255")), ["0.0.1.1", "0.0.1.0", "0.0.0.255"])
        self.assertEqual(list(IPv4Iterator("1.1.1.1", "1.1.1.1")), ["1.1.1.1"])
        self.assertEqual(list(IPv4Iterator("255.255.255.254", "255.255.255.255")), ["255.255.255.254", "255.255.255.255"])
        it = IPv4Iterator("1.1.1.1", "1.1.1.2")
        out = []
        while it.hasNext(): out.append(it.next())
        self.assertEqual(out, ["1.1.1.1", "1.1.1.2"])
        with self.assertRaises(StopIteration): it.next()

    def test_cidr(self):
        self.assertEqual(list(IPv4Iterator.from_cidr("192.168.1.0/30")), ["192.168.1.0", "192.168.1.1", "192.168.1.2", "192.168.1.3"])
        self.assertEqual(list(IPv4Iterator.from_cidr("192.168.1.2/31", False)), ["192.168.1.3", "192.168.1.2"])
        self.assertEqual(list(IPv4Iterator.from_cidr("10.1.2.3/32")), ["10.1.2.3"])
        self.assertEqual(cidr_range("1.2.3.4/0"), (0, 2**32 - 1)) # never walk this one
        self.assertEqual(cidr_range("10.1.2.3/16"), (to_int("10.1.0.0"), to_int("10.1.255.255")))


def simulate(grid, D):
    # day by day with real recovery, to check the BFS reduction
    n, m = len(grid), len(grid[0])
    infected_at = {(r, c): 0 for r in range(n) for c in range(m) if grid[r][c] == "X"}
    immune = {(r, c) for r in range(n) for c in range(m) if grid[r][c] == "#"}
    if not infected_at: return 0
    day = 0
    while True:
        active = [p for p, t in infected_at.items() if p not in immune]
        if not active: return day
        day += 1
        new = []
        for r, c in active: # spread from cells infected before today
            for a, b in ((r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)):
                if 0 <= a < n and 0 <= b < m and (a, b) not in infected_at and (a, b) not in immune: new.append((a, b))
        for p, t in list(infected_at.items()):
            if p not in immune and day - t >= D: immune.add(p) # recovered
        for p in new: infected_at.setdefault(p, day)


class TestInfection(unittest.TestCase):

    def test_examples(self):
        self.assertEqual(last_recovery_day(["X..", "...", "..."], 2), 6)
        self.assertEqual(last_recovery_day(["X#.", ".#.", "..#"], 3), 6)
        self.assertEqual(last_recovery_day(["...", ".#."], 5), 0)

    def test_against_day_by_day_simulation(self):
        rng = random.Random(9)
        for _ in range(300):
            n, m, D = rng.randint(1, 6), rng.randint(1, 6), rng.randint(1, 4)
            grid = ["".join(rng.choice("X....##") for _ in range(m)) for _ in range(n)]
            self.assertEqual(last_recovery_day(grid, D), simulate(grid, D), (grid, D))


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
