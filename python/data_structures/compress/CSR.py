# Compressed sparse row: entries grouped by row in one flat list.
# row i is data[offset[i]:offset[i+1]]


class CSR:
    def __init__(self, n: int):
        self.n = n
        self.built = False
        self.row, self.data = [], []

    # stage entry x into row i; any order, any number of times
    def add(self, i: int, x) -> None:
        assert 0 <= i < self.n and not self.built
        self.row.append(i)
        self.data.append(x)

    # group everything by row in one O(n + nnz) counting sort
    def build(self) -> None:
        assert not self.built
        self.built = True
        self.offset = [0] * (self.n + 1)
        for i in self.row: self.offset[i + 1] += 1 # count entries per row
        for i in range(1, self.n + 1): self.offset[i] += self.offset[i - 1] # prefix sums = row starts
        cur = self.offset[:]
        tmp = [None] * len(self.data)
        for i, x in zip(self.row, self.data): # scatter into each slice
            tmp[cur[i]] = x
            cur[i] += 1
        self.data, self.row = tmp, []

    def __getitem__(self, i: int) -> list:
        assert self.built
        return self.data[self.offset[i]:self.offset[i + 1]]
