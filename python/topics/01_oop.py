"""class is a C++ struct with methods. self is the object, written out every time."""


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __lt__(self, other):
        return (self.x, self.y) < (other.x, other.y)

    def __repr__(self):
        return f"({self.x}, {self.y})"


class DSU:
    def __init__(self, n):
        self.parent = list(range(n))
        self.sz = [1] * n

    def find(self, v):
        if v == self.parent[v]:
            return v
        self.parent[v] = self.find(self.parent[v])
        return self.parent[v]

    def unite(self, a, b):
        a, b = self.find(a), self.find(b)
        if a == b:
            return False
        if self.sz[a] < self.sz[b]:
            a, b = b, a
        self.parent[b] = a
        self.sz[a] += self.sz[b]
        return True


def main():
    pts = [Point(2, 1), Point(1, 5), Point(2, 0)]
    pts.sort()
    print("sorted points:", pts)

    # a tuple already sorts lexicographically, so skip the class until you need methods
    pairs = [(2, 1), (1, 5), (2, 0)]
    pairs.sort()
    print("sorted tuples:", pairs)

    dsu = DSU(4)
    dsu.unite(0, 1)
    dsu.unite(2, 3)
    print("0 and 1 same:", dsu.find(0) == dsu.find(1))
    print("0 and 2 same:", dsu.find(0) == dsu.find(2))
    dsu.unite(1, 2)
    print("after unite, size of 0's component:", dsu.sz[dsu.find(0)])


if __name__ == "__main__":
    main()
