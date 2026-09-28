# Python for CP

Algorithms stay in `notebook/`. This folder is the Python that replaces C++ syntax. Run a file to see the pattern:

```
python3 python/topics/02_bisect.py
```

The contest starter is `python/template.py`.

## Start here

1. [topics/01_oop.py](topics/01_oop.py) — `class`, `self`, methods, sorting objects. A tuple is enough until you need methods.
2. [topics/02_bisect.py](topics/02_bisect.py) — `bisect_left` is `lower_bound`, `bisect_right` is `upper_bound`, plus binary search on the answer.
3. [topics/03_unpacking.py](topics/03_unpacking.py) — spread a list with `*`: into a call, into another list, and `zip(*rows)` to transpose.

## Then these

4. [topics/04_collections.py](topics/04_collections.py) — `list`, `deque`, `heapq`, `set`, `dict`, `Counter`, `defaultdict`.
5. [topics/05_sorting.py](topics/05_sorting.py) — `sort` vs `sorted`, `key`, sorting one field backwards.
6. [topics/06_itertools.py](topics/06_itertools.py) — prefix sums with `accumulate`, `combinations`, `permutations`, `groupby`.
7. [topics/07_io.py](topics/07_io.py) — `readline`, `map(int, input().split())`, multiple tests.
8. [topics/08_pitfalls.py](topics/08_pitfalls.py) — floor division, Python modulo, copies, shared rows, `range` is half-open.
9. [topics/09_prefix_diff.py](topics/09_prefix_diff.py) — prefix sums, and spreading one update across a range with a difference array.
10. [topics/10_strings.py](topics/10_strings.py) — slices, reverse, `split` / `join`, `ord` / `chr`, find, replace, palindrome, and editing through a list.

## Drill next, in problems

- Graphs: adjacency lists, BFS, DFS, Dijkstra with `heapq`, DSU.
- String algorithms: hashing, Z-function, KMP. The language patterns are in `topics/10_strings.py`.
- Modular arithmetic: `pow(a, b, mod)` and the fact that `int` does not overflow.
- Recursion: `sys.setrecursionlimit`, and iterative DFS when the depth is large.
- Two pointers, sliding window, and frequency maps with `Counter`.
- Grids and 0-index vs 1-index loops (`range(1, n + 1)` is `FOR(i, 1, n)`).
- Speed: local variables inside a hot loop, PyPy on Codeforces, and C++ when the limit is tight.
