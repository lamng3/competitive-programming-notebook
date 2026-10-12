# Point set, range sum, and every old version stays readable.
# Nodes live in parallel lists; node 0 is the empty tree, so version 0 is root 0.


class PersistentSparseST:
    def __init__(self, n: int):
        self.N = n
        self.sum, self.left, self.right = [0], [0], [0]

    def _new(self, s, l: int, r: int) -> int:
        self.sum.append(s)
        self.left.append(l)
        self.right.append(r)
        return len(self.sum) - 1

    def join(self, l: int, r: int) -> int:
        return self._new(self.sum[l] + self.sum[r], l, r)

    # a new root where a[pos] = val; the old root is untouched
    def update(self, root: int, pos: int, val, tl: int = 0, tr: int = None) -> int:
        if tr is None: tr = self.N - 1
        if tl == tr: return self._new(val, 0, 0)
        tm = tl + (tr - tl) // 2
        lc, rc = self.left[root], self.right[root]
        if pos <= tm: return self.join(self.update(lc, pos, val, tl, tm), rc)
        return self.join(lc, self.update(rc, pos, val, tm + 1, tr))

    # sum of a[ql..qr] in the version rooted at root
    def query(self, root: int, ql: int, qr: int, tl: int = 0, tr: int = None):
        if tr is None: tr = self.N - 1
        if root == 0 or ql > qr: return 0
        if ql == tl and tr == qr: return self.sum[root]
        tm = tl + (tr - tl) // 2
        left = self.query(self.left[root], ql, min(tm, qr), tl, tm)
        right = self.query(self.right[root], max(tm + 1, ql), qr, tm + 1, tr)
        return left + right
