from math import isqrt

# Mo's algorithm: answer offline range queries by moving one window [mo_L, mo_R].
# The caller keeps the window state:
#   add(i)     A[i] enters the window
#   remove(i)  A[i] leaves the window
#   answer()   the answer for the current window


class Mo:
    def __init__(self, a: list):
        self.A = a
        self.BLOCK_SIZE = max(1, isqrt(len(a)))
        self.Q = [] # (L, R, id), inclusive

    def add_query(self, L: int, R: int, id: int) -> None:
        self.Q.append((L, R, id))

    # answers indexed by query id
    def process_queries(self, add, remove, answer) -> list:
        B = self.BLOCK_SIZE
        # sort by block of L, then R (zig-zag on odd blocks), so the window moves O((n + q) sqrt n)
        order = sorted(self.Q, key=lambda q: (q[0] // B, q[1] if (q[0] // B) % 2 == 0 else -q[1]))
        ans = [None] * len(self.Q)
        mo_L, mo_R = 0, -1 # empty window
        for L, R, id in order:
            # expand first, so the window never turns inside out
            while mo_L > L:
                mo_L -= 1
                add(mo_L)
            while mo_R < R:
                mo_R += 1
                add(mo_R)
            # then shrink
            while mo_L < L:
                remove(mo_L)
                mo_L += 1
            while mo_R > R:
                remove(mo_R)
                mo_R -= 1
            ans[id] = answer()
        return ans
