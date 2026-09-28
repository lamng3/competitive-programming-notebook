"""A difference array spreads one +v across [L, R], then a prefix sum rebuilds the array."""


def range_add(diff, L, R, v):
    diff[L] += v
    diff[R + 1] -= v


def prefix_sums(a):
    pref = [0]
    for x in a:
        pref.append(pref[-1] + x)
    return pref


def rebuild(diff):
    for i in range(1, len(diff)):
        diff[i] += diff[i - 1]
    return diff


def main():
    a = [2, 1, 3, 4]
    pref = prefix_sums(a)
    # sum of a[1..2] inclusive, 0-indexed
    print("range sum [1, 2]:", pref[3] - pref[1])

    n = 5
    diff = [0] * (n + 1)
    range_add(diff, 1, 3, 3)
    got = rebuild(diff)[:n]
    print("spread +3 on [1, 3]:", got)
    assert got == [0, 3, 3, 3, 0]


if __name__ == "__main__":
    main()
