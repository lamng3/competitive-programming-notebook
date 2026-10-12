# Square Root Decomposition: point set, range sum in O(sqrt n)


class SRD:
    def __init__(self, sqrtn: int, a: list):
        self.BLOCK_SIZE = sqrtn # blocks of sqrtn elements; needs sqrtn * sqrtn >= len(a)
        self.A = list(a)
        self.blocks = [0] * sqrtn
        for i, x in enumerate(self.A):
            self.blocks[i // self.BLOCK_SIZE] += x

    # O(1): set A[x] = v
    def update(self, x: int, v) -> None:
        self.blocks[x // self.BLOCK_SIZE] += v - self.A[x]
        self.A[x] = v

    # O(sqrt n): sum of A[0, R) with one argument, A[L, R) with two
    def query(self, L: int, R: int = None):
        if R is not None: return self.query(R) - self.query(L)
        R = L
        if R <= 0: return 0
        B = self.BLOCK_SIZE
        return sum(self.blocks[:R // B]) + sum(self.A[R // B * B:R])
