"""accumulate is a prefix sum. combinations and permutations replace nested loops over subsets."""

from itertools import accumulate, combinations, groupby, permutations


def main():
    a = [1, 2, 3, 4]
    print("prefix sums:", list(accumulate(a)))

    print("pairs:", list(combinations(range(4), 2)))
    print("perms of 3, take 2:", list(permutations(range(3), 2)))

    s = "aabbbcc"
    runs = [(ch, len(list(grp))) for ch, grp in groupby(s)]
    print("consecutive runs:", runs)


if __name__ == "__main__":
    main()
