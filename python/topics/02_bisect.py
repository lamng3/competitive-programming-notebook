"""bisect_left is lower_bound. bisect_right is upper_bound. The list must be sorted."""

from bisect import bisect_left, bisect_right

INF = 10**18


def lower_bound(a, x):
    return bisect_left(a, x)


def upper_bound(a, x):
    return bisect_right(a, x)


def first_true(lo, hi, ok):
    """Smallest x in [lo, hi] with ok(x). hi is exclusive, same as while (lo < hi)."""
    while lo < hi:
        mid = (lo + hi) // 2
        if ok(mid):
            hi = mid
        else:
            lo = mid + 1
    return lo


def main():
    a = [1, 2, 2, 2, 4, 5]
    print("lower_bound 2:", lower_bound(a, 2))
    print("upper_bound 2:", upper_bound(a, 2))
    print("count of 2:", upper_bound(a, 2) - lower_bound(a, 2))
    print("lower_bound 3 (insertion point):", lower_bound(a, 3))
    print("lower_bound 6 (past the end):", lower_bound(a, 6))

    # pairs compare lexicographically, so this is lower_bound on the first field
    pairs = [(1, 10), (2, 1), (2, 7), (4, 0)]
    print("first pair with x >= 2:", lower_bound(pairs, (2, -INF)))
    print("first pair with x > 2:", upper_bound(pairs, (2, INF)))

    # smallest integer whose square is >= 20
    n = 20
    ans = first_true(0, n + 1, lambda x: x * x >= n)
    print("ceil sqrt 20:", ans)


if __name__ == "__main__":
    main()
