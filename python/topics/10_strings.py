"""A string is immutable. s[L:R] is [L, R). Build pieces in a list, then join."""

from collections import Counter


def main():
    s = "abca"

    print("slice [1, 3):", s[1:3])
    print("last char:", s[-1])
    print("reverse:", s[::-1])
    print("prefix of length 2:", s[:2])
    print("drop first char:", s[1:])

    # assign through a list; s[i] = "z" raises TypeError
    chars = list(s)
    chars[0] = "z"
    print("edit via list:", "".join(chars))

    print("repeat:", "ab" * 3)
    print("join:", "-".join(["a", "b", "c"]))
    print("split on whitespace:", "a  b\tc".split())
    print("split on one comma:", "a,,b".split(","))

    # readline keeps the newline; strip both ends, rstrip only the end
    line = "  ab \n"
    print("strip:", repr(line.strip()))
    print("rstrip newline:", repr("ab \n".rstrip("\n")))

    print("alpha index of c:", ord("c") - ord("a"))
    print("index 2 back to a char:", chr(ord("a") + 2))
    print("shift each char:", "".join(chr(ord(c) + 1) for c in "abc"))

    t = "banana"
    print("find ana:", t.find("ana"))
    print("rfind a:", t.rfind("a"))
    print("non-overlapping count of aa in aaa:", "aaa".count("aa"))
    print("replace:", "a.b.a".replace(".", ""))
    print("startswith / endswith:", s.startswith("ab"), s.endswith("ca"))

    print("palindrome:", "abba" == "abba"[::-1])
    print("same multiset:", Counter("aab") == Counter("aba"))
    print("sorted chars:", "".join(sorted("bac")))
    print("lower:", "AbC".lower())
    print("digit string:", "007".isdigit(), int("007"))

    assert s[1:3] == "bc"
    assert "".join(chars) == "zbca"
    assert ord("c") - ord("a") == 2
    assert "banana".find("ana") == 1
    assert "aaa".count("aa") == 1


if __name__ == "__main__":
    main()
