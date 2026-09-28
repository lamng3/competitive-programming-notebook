"""* spreads a list. It expands the elements, it does not pass the list as one object."""


def add(x, y, z):
    return x + y + z


def main():
    a = [1, 2, 3]
    b = [4, 5]

    print("spread into a call:", add(*a))
    print("spread into a new list:", [0, *a, *b, 6])
    print("print each item:", end=" ")
    print(*a)

    first, *mid, last = [1, 2, 3, 4, 5]
    print("first, mid, last:", first, mid, last)

    # swap, and unpack a pair the way tie() does
    x, y = 1, 2
    x, y = y, x
    print("swapped:", x, y)

    rows = [
        [1, 2, 3],
        [4, 5, 6],
    ]
    print("transpose with zip(*rows):", list(zip(*rows)))

    # merge dicts the same way
    base = {"mod": 10**9 + 7}
    extra = {**base, "inf": 10**18}
    print("spread a dict:", extra)


if __name__ == "__main__":
    main()
