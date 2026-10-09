import random
from utils.hash import djb2, fnv1a

class CuckooFilter:
    BUCKET_SIZE = 4
    EMPTY = 0

    def __init__(self, n, max_kicks) -> None:
        self.n = n
        self.hash = djb2
        self.fingerprint = fnv1a
        self.max_kicks = max_kicks
        self.B = [[0] * self.BUCKET_SIZE for _ in range(self.n)]

    def _find(self, i: int, v: int) -> int:
        for j in range(self.BUCKET_SIZE):
            if self.B[i][j] == v: return j
        return -1

    def insert(self, key: str) -> bool:
        f = self.fingerprint(key)
        i1 = self.hash(key) % self.n
        i2 = (i1 ^ self.hash(str(f))) % self.n
        p1, p2 = self._find(i1, self.EMPTY), self._find(i2, self.EMPTY)
        if p1 != -1:
            self.B[i1][p1] = f
            return True
        if p2 != -1:
            self.B[i2][p2] = f
            return True
        # randomize bucket i1 and i2
        i = i1 if random.random() < 0.5 else i2
        # remember each swap to undo on failure
        kicks = []
        for kick in range(self.max_kicks):
            # randomize a position to swap
            e = random.getrandbits(64) % self.BUCKET_SIZE
            f, self.B[i][e] = self.B[i][e], f
            kicks.append((i, e))
            i = (i ^ self.hash(str(f))) % self.n
            p = self._find(i, self.EMPTY)
            if p != -1:
                self.B[i][p] = f
                return True
        for k in reversed(range(len(kicks))):
            f, self.B[kicks[k][0]][kicks[k][1]] = self.B[kicks[k][0]][kicks[k][1]], f
        return False

    def lookup(self, key: str) -> bool:
        f = self.fingerprint(key)
        i1 = self.hash(key) % self.n
        i2 = (i1 ^ self.hash(str(f))) % self.n
        return self._find(i1, f) != -1 or self._find(i2, f) != -1

    def remove(self, key: str) -> bool:
        f = self.fingerprint(key)
        i1 = self.hash(key) % self.n
        i2 = (i1 ^ self.hash(str(f))) % self.n
        p1, p2 = self._find(i1, f), self._find(i2, f)
        if p1 != -1:        
            self.B[i1][p1] = self.EMPTY
            return True
        if p2 != -1:
            self.B[i2][p2] = self.EMPTY
            return True
        return False

    def fill_rate(self) -> float:
        used = sum(v != self.EMPTY for bucket in self.B for v in bucket)
        return used / (self.n * self.BUCKET_SIZE)

    def false_positive_rate(self) -> float:
        # a lookup compares f with up to 2 buckets, each entry matches with prob 1/255
        entries = 2 * self.BUCKET_SIZE * self.fill_rate()
        return 1 - (1 - 1 / 255) ** entries
