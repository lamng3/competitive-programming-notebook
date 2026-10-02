class DSU:
    def __init__(self, n: int) -> None:
        self.par = list(range(n))
        self.sz = [1] * n

    def find(self, v: int) -> int:
        if v != self.par[v]:
            self.par[v] = self.find(self.par[v])
        return self.par[v]

    def unite(self, a: int, b: int) -> bool:
        a, b = self.find(a), self.find(b)
        if a == b: return False
        if self.sz[a] < self.sz[b]: # swap
            a, b = b, a
        self.par[b] = a
        self.sz[a] += self.sz[b]
        return True
