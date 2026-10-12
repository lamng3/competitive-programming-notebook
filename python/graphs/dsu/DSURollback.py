class DSURollback:
    def __init__(self, n: int) -> None:
        self.par = list(range(n))
        self.sz = [1] * n
        self.history = [] # who became a child, one entry per successful unite

    def find(self, v: int) -> int:
        while v != self.par[v]: # no path compression: it would make undo impossible
            v = self.par[v]
        return v

    def unite(self, a: int, b: int) -> bool:
        a, b = self.find(a), self.find(b)
        if a == b: return False
        if self.sz[a] < self.sz[b]: # union by size keeps find O(log n)
            a, b = b, a
        self.par[b] = a
        self.sz[a] += self.sz[b]
        self.history.append(b)
        return True

    # undo the last successful unite
    def rollback(self) -> None:
        if not self.history: return
        b = self.history.pop()
        a = self.par[b]
        self.sz[a] -= self.sz[b]
        self.par[b] = b
