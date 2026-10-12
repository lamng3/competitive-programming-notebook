from collections import deque


# 362. Design Hit Counter [Medium]
# One (timestamp, count) bucket per second, not one entry per hit:
# a burst of a million hits in one second is still one deque entry.
class HitCounter:

    def __init__(self):
        self.q = deque() # [timestamp, hits], timestamps increasing
        self.total = 0

    def hit(self, timestamp: int) -> None:
        if self.q and self.q[-1][0] == timestamp:
            self.q[-1][1] += 1
        else:
            self.q.append([timestamp, 1])
        self.total += 1

    # hits in (timestamp - 300, timestamp]
    def getHits(self, timestamp: int) -> int:
        while self.q and self.q[0][0] <= timestamp - 300:
            self.total -= self.q.popleft()[1]
        return self.total
