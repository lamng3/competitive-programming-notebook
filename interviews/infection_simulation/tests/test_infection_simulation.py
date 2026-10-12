"""Tests for interviews/infection_simulation

Run from anywhere:
    cpunit infection_simulation --py
or from this folder:
    python3 -m unittest -v test_infection_simulation
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from solution import last_recovery_day


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


if __name__ == "__main__":
    unittest.main()
