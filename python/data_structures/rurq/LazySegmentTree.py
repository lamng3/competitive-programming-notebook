class LazySegmentTree:
    # range add, range sum, 0-indexed, inclusive ranges
    def __init__(self, a: list):
        self.N = len(a)
        self.A = list(a)
        self.st = [0] * (4 * max(self.N, 1))
        self.lazy = [0] * (4 * max(self.N, 1))
        if self.N: self.build(0, 0, self.N - 1)

    def build(self, v: int, tl: int, tr: int) -> None:
        if tl == tr:
            self.st[v] = self.A[tl]
            return
        tm = tl + (tr - tl) // 2
        self.build(v * 2 + 1, tl, tm)
        self.build(v * 2 + 2, tm + 1, tr)
        self.st[v] = self.st[v * 2 + 1] + self.st[v * 2 + 2]

    # hand v's pending add to its children; st holds sums, so scale by length
    def push(self, v: int, tl: int, tm: int, tr: int) -> None:
        if self.lazy[v]:
            for c, length in ((v * 2 + 1, tm - tl + 1), (v * 2 + 2, tr - tm)):
                self.st[c] += self.lazy[v] * length
                self.lazy[c] += self.lazy[v]
            self.lazy[v] = 0

    # add x to a[ql..qr]
    def update(self, ql: int, qr: int, x, v: int = 0, tl: int = 0, tr: int = None) -> None:
        if tr is None: tr = self.N - 1
        if ql > qr: return
        if ql == tl and tr == qr:
            self.st[v] += x * (tr - tl + 1)
            self.lazy[v] += x
            return
        tm = tl + (tr - tl) // 2
        self.push(v, tl, tm, tr)
        self.update(ql, min(tm, qr), x, v * 2 + 1, tl, tm)
        self.update(max(tm + 1, ql), qr, x, v * 2 + 2, tm + 1, tr)
        self.st[v] = self.st[v * 2 + 1] + self.st[v * 2 + 2]

    # sum of a[ql..qr]
    def query(self, ql: int, qr: int, v: int = 0, tl: int = 0, tr: int = None):
        if tr is None: tr = self.N - 1
        if ql > qr: return 0
        if ql == tl and tr == qr: return self.st[v]
        tm = tl + (tr - tl) // 2
        self.push(v, tl, tm, tr)
        left = self.query(ql, min(tm, qr), v * 2 + 1, tl, tm)
        right = self.query(max(tm + 1, ql), qr, v * 2 + 2, tm + 1, tr)
        return left + right
