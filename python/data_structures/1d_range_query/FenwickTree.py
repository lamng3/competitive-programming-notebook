class FenwickTree:
    # 1-indexed, as in FenwickTree.h: add(i, u) and sum(i) take i in [1, n]
    def __init__(self, n_or_a):
        if isinstance(n_or_a, int):
            self.n = n_or_a
            self.ft = [0] * (self.n + 1)
        else:
            self.init(n_or_a)

    # build from a list in O(n): push each node's total into its parent
    def init(self, a: list) -> None:
        self.n = len(a)
        self.ft = [0] + list(a)
        for i in range(1, self.n + 1):
            j = i + (i & -i)
            if j <= self.n: self.ft[j] += self.ft[i]

    def add(self, i: int, u) -> None:
        while i <= self.n:
            self.ft[i] += u
            i += i & -i

    # sum(i) = a[1] + ... + a[i]; sum(L, R) = a[L] + ... + a[R]
    def sum(self, L: int, R: int = None):
        if R is not None:
            return self.sum(R) - self.sum(L - 1) if L <= R else 0
        s, i = 0, L
        while i > 0:
            s += self.ft[i]
            i -= i & -i
        return s
