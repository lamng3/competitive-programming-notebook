"""list.sort mutates. sorted returns a new list. key= replaces a custom comparator."""

from operator import itemgetter


def main():
    a = [(2, 1), (1, 9), (2, 3)]
    print("lexicographic:", sorted(a))

    by_second = sorted(a, key=itemgetter(1))
    print("by second field:", by_second)

    # first ascending, second descending: negate the field you want reversed
    mixed = sorted(a, key=lambda p: (p[0], -p[1]))
    print("first asc, second desc:", mixed)

    b = [3, 1, 2]
    b.sort(reverse=True)
    print("in place reverse:", b)


if __name__ == "__main__":
    main()
