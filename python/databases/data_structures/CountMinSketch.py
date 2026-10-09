import math, heapq
from utils.hash import random_seeds, hash_with_seed

class CountMinSketch:
    INF = math.inf

    def __init__(self, width, depth, seeds=None):
        self.width = width
        self.depth = depth
        self.seeds = seeds if (seeds is not None and len(seeds) == self.depth) else random_seeds(self.depth)
        self.hash_functions = [hash_with_seed] * self.depth
        self.matrix = [[0] * self.width for _ in range(self.depth)]

    def insert(self, x) -> None:
        for r in range(self.depth):
            c = self.hash_functions[r](x, self.seeds[r]) % self.width
            self.matrix[r][c] += 1

    def count(self, x) -> int:
        res = self.INF
        for r in range(self.depth):
            c = self.hash_functions[r](x, self.seeds[r]) % self.width
            res = min(res, self.matrix[r][c])
        return res

    def clear(self):
        self.matrix = [[0] * self.width for _ in range(self.depth)]

    def merge(self, other) -> None:
        if other.width != self.width or other.depth != self.depth or other.seeds != self.seeds:
            return None            
        res = CountMinSketch(self.width, self.depth, self.seeds)
        for r in range(self.depth):
            for c in range(self.width):
                res.matrix[r][c] = self.matrix[r][c] + other.matrix[r][c]
        return res

    def top_k(self, k, candidates):
        min_heap = []
        for candidate in candidates:
            cnt = self.count(candidate)
            heapq.heappush(min_heap, (cnt, candidate))
            if len(min_heap) > k:
                heapq.heappop(min_heap)
        return [candidate for cnt, candidate in sorted(min_heap, reverse=True)]
