from bisect import bisect_right


# 1146. Snapshot Array [Medium]
# Store only changes: each index keeps (snap_id, value) pairs in increasing snap_id,
# and get finds the last change made at or before snap_id with a binary search.
class SnapshotArray:

    def __init__(self, length: int):
        self.snap_id = 0
        self.hist = [[(-1, 0)] for _ in range(length)] # a sentinel: 0 before any snap

    def set(self, index: int, val: int) -> None:
        h = self.hist[index]
        if h[-1][0] == self.snap_id: h[-1] = (self.snap_id, val) # same snap: overwrite
        else: h.append((self.snap_id, val))

    def snap(self) -> int:
        self.snap_id += 1
        return self.snap_id - 1

    def get(self, index: int, snap_id: int) -> int:
        h = self.hist[index]
        i = bisect_right(h, (snap_id, float("inf"))) - 1 # last pair with id <= snap_id
        return h[i][1]
