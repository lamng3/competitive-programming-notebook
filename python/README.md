# Python

Paste-ready snippets, one class per file. Categories and method names match `notebook/`, so a Python file reads next to its C++ header. Drop the next translation in the same place as its C++ header.

## Starters

- [template.py](template.py): contest starter (`cpnew A --py`)
- [leetcode.py](leetcode.py): LeetCode starter with the usual imports, `dr`/`dc`, and a raised recursion limit (`cpnew A leetcode --py`)
- [patterns.py](patterns.py): the patterns to write from memory and review against: prefix sums, binary search on the answer, BFS, DFS, Dijkstra, topological sort, sliding window, monotonic stack, backtracking, `@cache` DP, compression

## Structures

- [data_structures/1d_range_query/FenwickTree.py](data_structures/1d_range_query/FenwickTree.py)
- [data_structures/1d_range_query/IterativeSegmentTree.py](data_structures/1d_range_query/IterativeSegmentTree.py)
- [data_structures/1d_range_query/SegmentTree.py](data_structures/1d_range_query/SegmentTree.py)
- [data_structures/rurq/LazySegmentTree.py](data_structures/rurq/LazySegmentTree.py)
- [databases/data_structures/BloomFilter.py](databases/data_structures/BloomFilter.py)
- [databases/data_structures/CountMinSketch.py](databases/data_structures/CountMinSketch.py)
- [databases/data_structures/CuckooFilter.py](databases/data_structures/CuckooFilter.py)
- [databases/data_structures/Skiplist.py](databases/data_structures/Skiplist.py)
- [databases/data_structures/utils/hash.py](databases/data_structures/utils/hash.py)
- [graphs/dsu/DSU.py](graphs/dsu/DSU.py)
- [math/modular_arithmetic/ModFact.py](math/modular_arithmetic/ModFact.py)
- [strings/rolling_hash/RollingHash.py](strings/rolling_hash/RollingHash.py)
- [strings/trie/FileSystem.py](strings/trie/FileSystem.py)
- [strings/trie/Trie.py](strings/trie/Trie.py)
- [utils/CoordinateCompression.py](utils/CoordinateCompression.py)

Every structure has tests: `cpunit --list` shows them, and `cpunit <name> --py` runs one.
