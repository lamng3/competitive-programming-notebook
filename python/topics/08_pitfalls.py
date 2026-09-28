"""The mismatches with C++ that change answers."""


def uses_shared_default(x, bag=[]):
    bag.append(x)
    return bag


def main():
    # / is float division. // is floor division, toward -infinity.
    assert 7 / 2 == 3.5
    assert 7 // 2 == 3
    assert (-7) // 2 == -4

    # modulo follows the divisor, so a negative number stays non-negative
    assert (-1) % 5 == 4

    # assignment aliases the list. slice to copy.
    a = [1, 2]
    b = a
    b.append(3)
    assert a == [1, 2, 3]
    a = [1, 2]
    b = a[:]
    b.append(3)
    assert a == [1, 2]

    # * repeats the same inner list. build each row on its own.
    bad = [[0] * 3] * 2
    bad[0][0] = 1
    assert bad[1][0] == 1
    grid = [[0] * 3 for _ in range(2)]
    grid[0][0] = 1
    assert grid[1][0] == 0

    # a default list is created once and reused
    assert uses_shared_default(1) == [1]
    assert uses_shared_default(2) == [1, 2]

    # range(L, R) is [L, R), so range(1, n + 1) is FOR(i, 1, n)
    assert list(range(1, 4)) == [1, 2, 3]

    # int does not overflow
    assert 2**100 > 10**18

    print("pitfalls ok")


if __name__ == "__main__":
    main()
