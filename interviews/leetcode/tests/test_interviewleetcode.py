"""Tests for interviews/leetcode

Run from anywhere:
    cpunit interviewleetcode --py
or from this folder:
    python3 -m unittest -v test_interviewleetcode
"""
import os
import random
import re
import sys
import unittest
from collections import Counter
from importlib import import_module

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
HitCounter = import_module("362").HitCounter
RandomizedSet = import_module("380").RandomizedSet
LFUCache = import_module("460").LFUCache
Justify = import_module("68").Solution
TopK = import_module("347").Solution
Backlog = import_module("1801").Solution
SnapshotArray = import_module("1146").SnapshotArray


class TestInterviewLeetCode(unittest.TestCase):

    def test_362_hit_counter(self):
        rng = random.Random(1)
        for _ in range(50):
            hc, hits, t = HitCounter(), [], 1
            for _ in range(200):
                t += rng.choice([0, 0, 1, 7, 150, 400])
                if rng.random() < 0.6:
                    hc.hit(t)
                    hits.append(t)
                else:
                    self.assertEqual(hc.getHits(t), sum(1 for h in hits if h > t - 300))

    def test_380_randomized_set(self):
        rng = random.Random(2)
        rs, ref = RandomizedSet(), set()
        for _ in range(3000):
            x, op = rng.randint(0, 30), rng.random()
            if op < 0.45: self.assertEqual(rs.insert(x), x not in ref); ref.add(x)
            elif op < 0.9: self.assertEqual(rs.remove(x), x in ref); ref.discard(x)
            elif ref: self.assertIn(rs.getRandom(), ref)
        rs = RandomizedSet()
        for x in range(4): rs.insert(x)
        seen = Counter(rs.getRandom() for _ in range(4000))
        self.assertTrue(all(800 < seen[x] < 1200 for x in range(4)), seen)

    def test_460_lfu_against_brute_force(self):
        rng = random.Random(3)
        for _ in range(100):
            cap = rng.randint(0, 4)
            lfu, ref, clock = LFUCache(cap), {}, 0 # ref: key -> [value, freq, last use]
            for _ in range(80):
                clock += 1
                k = rng.randint(0, 6)
                if rng.random() < 0.5:
                    want = -1
                    if k in ref:
                        ref[k][1] += 1
                        ref[k][2] = clock
                        want = ref[k][0]
                    self.assertEqual(lfu.get(k), want)
                else:
                    v = rng.randint(0, 99)
                    lfu.put(k, v)
                    if cap == 0: continue
                    if k in ref:
                        ref[k] = [v, ref[k][1] + 1, clock]
                    else:
                        if len(ref) == cap:
                            del ref[min(ref, key=lambda x: (ref[x][1], ref[x][2]))]
                        ref[k] = [v, 1, clock]

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
                if inner: self.assertEqual(inner, sorted(inner, reverse=True)) # extra spaces go left

    def test_347_top_k(self):
        rng = random.Random(5)
        for _ in range(200):
            nums = [rng.randint(0, 8) for _ in range(rng.randint(1, 30))]
            cnt = Counter(nums)
            k = rng.randint(1, len(cnt))
            got = TopK().topKFrequent(nums, k)
            self.assertEqual(len(set(got)), k)
            self.assertEqual(sorted((cnt[x] for x in got), reverse=True), sorted(cnt.values(), reverse=True)[:k])

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

    def test_1146_snapshot_array(self):
        rng = random.Random(7)
        for _ in range(50):
            n = rng.randint(1, 6)
            sa, cur, snaps = SnapshotArray(n), [0] * n, []
            for _ in range(100):
                op = rng.random()
                if op < 0.5:
                    i, v = rng.randrange(n), rng.randint(0, 9)
                    sa.set(i, v)
                    cur[i] = v
                elif op < 0.7:
                    self.assertEqual(sa.snap(), len(snaps))
                    snaps.append(cur[:])
                elif snaps:
                    s, i = rng.randrange(len(snaps)), rng.randrange(n)
                    self.assertEqual(sa.get(i, s), snaps[s][i])


if __name__ == "__main__":
    unittest.main()
