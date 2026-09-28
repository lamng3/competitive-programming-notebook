"""readline is the usual contest input. map(int, line.split()) replaces cin >> a >> b."""

import io
import sys


def solve_all(data):
    sys.stdin = io.StringIO(data)
    input = sys.stdin.readline

    tt = int(input())
    out = []
    for _ in range(tt):
        n, m = map(int, input().split())
        a = list(map(int, input().split()))
        out.append((n, m, a))
    return out


def main():
    sample = """\
2
3 4
1 2 3
1 5
9
"""
    print(solve_all(sample))


if __name__ == "__main__":
    main()
