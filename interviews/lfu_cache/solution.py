from collections import OrderedDict, defaultdict


# 460. LFU Cache [Hard]
# freq -> keys in recency order (an OrderedDict is a linked list with O(1) lookup).
# Evict the least recent key of the smallest frequency. The smallest frequency only
# changes in two ways: a touch can raise it by one, and a new key resets it to 1.
class LFUCache:

    def __init__(self, capacity: int):
        self.cap = capacity
        self.val, self.freq = {}, {}
        self.keys = defaultdict(OrderedDict) # freq -> keys, least recent first
        self.minf = 0

    def _touch(self, key: int) -> None:
        f = self.freq[key]
        del self.keys[f][key]
        if not self.keys[f]:
            del self.keys[f]
            if self.minf == f: self.minf += 1
        self.freq[key] = f + 1
        self.keys[f + 1][key] = None

    def get(self, key: int) -> int:
        if key not in self.val: return -1
        self._touch(key)
        return self.val[key]

    def put(self, key: int, value: int) -> None:
        if self.cap == 0: return
        if key in self.val:
            self.val[key] = value
            self._touch(key)
            return
        if len(self.val) == self.cap:
            old, _ = self.keys[self.minf].popitem(last=False) # least recent at min freq
            if not self.keys[self.minf]: del self.keys[self.minf]
            del self.val[old], self.freq[old]
        self.val[key], self.freq[key] = value, 1
        self.keys[1][key] = None
        self.minf = 1
