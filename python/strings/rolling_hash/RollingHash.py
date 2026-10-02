class RollingHash:
    def __init__(self):
        self.base = 313
        self.mod = (1 << 61) - 1
        self.hash = [0]
        self.pow = [1]

    def push_back(self, c: str) -> int:
        self.hash.append((self.hash[-1] * self.base + ord(c)) % self.mod)
        self.pow.append(self.pow[-1] * self.base % self.mod)

    def get_hash(self, L: int = None, R: int = None) -> int:
        if L is None and R is None: return self.hash[-1]
        term = self.hash[L] * self.pow[R - L + 1] % self.mod
        return (self.hash[R + 1] + self.mod - term) % self.mod
