class IterativeSegmentTree:
    # sums over a, 0-indexed; leaves live at tree[n..2n)
    def __init__(self, a: list):
        self.n = len(a)
        self.tree = [0] * self.n + list(a)
        self.build()

    # build the tree in O(n)
    def build(self) -> None:
        for i in range(self.n - 1, 0, -1):
            self.tree[i] = self.tree[i << 1] + self.tree[i << 1 | 1]

    # point update in O(log n): set a[p] = v
    def update(self, p: int, v) -> None:
        p += self.n
        self.tree[p] = v
        while p > 1:
            # p ^ 1 is the sibling of p
            self.tree[p >> 1] = self.tree[p] + self.tree[p ^ 1]
            p >>= 1

    # sum of a[l..r), half-open
    def query(self, l: int, r: int):
        res = 0
        l += self.n
        r += self.n
        while l < r:
            if l & 1: # l is a right child: take it and move right
                res += self.tree[l]
                l += 1
            if r & 1: # r is a right child: take its left sibling
                r -= 1
                res += self.tree[r]
            l >>= 1
            r >>= 1
        return res
