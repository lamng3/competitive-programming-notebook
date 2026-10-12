import random


# 380. Insert Delete GetRandom O(1) [Medium]
# A list for O(1) random access, a dict for O(1) lookup of where each value sits.
# Delete moves the last element into the hole, so the list never has gaps.
class RandomizedSet:

    def __init__(self):
        self.vals = []
        self.pos = {} # value -> index in vals

    def insert(self, val: int) -> bool:
        if val in self.pos: return False
        self.pos[val] = len(self.vals)
        self.vals.append(val)
        return True

    def remove(self, val: int) -> bool:
        if val not in self.pos: return False
        i, last = self.pos[val], self.vals[-1]
        self.vals[i] = last # last fills the hole (a no-op when val is last)
        self.pos[last] = i
        self.vals.pop()
        del self.pos[val]
        return True

    def getRandom(self) -> int:
        return random.choice(self.vals)
