"""The containers that replace vector, queue, set, map, and priority_queue."""

import heapq
from collections import Counter, defaultdict, deque


def main():
    dq = deque([2, 3])
    dq.appendleft(1)
    dq.append(4)
    print("deque pop left, pop right:", dq.popleft(), dq.pop())

    h = []
    for x in (3, 1, 2):
        heapq.heappush(h, x)
    print("min-heap pop:", heapq.heappop(h))

    maxh = []
    for x in (3, 1, 2):
        heapq.heappush(maxh, -x)
    print("max-heap pop:", -heapq.heappop(maxh))

    seen = set()
    seen.add(1)
    print("1 in set:", 1 in seen)

    freq = Counter("aab")
    print("Counter:", freq, "most common:", freq.most_common(1))

    g = defaultdict(list)
    g[1].append(2)
    g[1].append(3)
    print("adj list:", dict(g))

    d = {1: 10}
    print("missing key:", d.get(2, 0))


if __name__ == "__main__":
    main()
