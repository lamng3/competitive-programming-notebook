# Python

Paste-ready templates, one topic per folder. Where a C++ header exists, the Python file sits at the same path under `python/` with the same method names, so the two read side by side. Everything is generic: the problem plugs in through arguments (`ok(r, c)` for which cells can be entered, `add`/`remove` for a window, `step`/`accept` for a digit DP), so a template is copied, not edited.

Every file has tests: `cpunit --list` shows them, and `cpunit <name> --py` runs one. Where the C++ header has a test of the same name, `cpunit <name>` runs both.

## Starters

- [template.py](template.py): contest starter (`cpnew A --py`)
- [leetcode.py](leetcode.py): LeetCode starter with the usual imports, `dr`/`dc`, and a raised recursion limit (`cpnew A leetcode --py`)

## Arrays

- [arrays/prefix_sums/PrefixSum.py](arrays/prefix_sums/PrefixSum.py): `PrefixSum` and `PrefixSum2D`, inclusive range sums in O(1)
- [arrays/sliding_window/SlidingWindow.py](arrays/sliding_window/SlidingWindow.py): `longest_window` and `shortest_window`, with the window state kept by the caller
- [arrays/monotonic_stack/MonotonicStack.py](arrays/monotonic_stack/MonotonicStack.py): `next_index` and `prev_index`; pass `gt`/`lt` for greater/smaller

## Searching

- [searching/binary_search/BinarySearch.py](searching/binary_search/BinarySearch.py): `first_true`, `last_true`, and `first_true_real`
- [searching/backtracking/Backtracking.py](searching/backtracking/Backtracking.py): `backtrack(n, choices, ok)`, `subsets`, `permutations`

## Graphs

- [graphs/bfs/BFS.py](graphs/bfs/BFS.py): multi-source `bfs`, `bfs_grid` with an `ok(r, c)` callback, and 0-1 BFS
- [graphs/dfs/DFS.py](graphs/dfs/DFS.py): `components`, `flood_fill`, and `tree_dfs` (parent, depth, size, order), all with explicit stacks
- [graphs/shortest_path/Dijkstra.py](graphs/shortest_path/Dijkstra.py): `dijkstra` with parents, and `path`
- [graphs/topological_sort/TopoSort.py](graphs/topological_sort/TopoSort.py): Kahn's algorithm, `[]` on a cycle
- [graphs/dsu/DSU.py](graphs/dsu/DSU.py), [graphs/dsu/DSURollback.py](graphs/dsu/DSURollback.py)

## Trees

- [trees/euler_tour/EulerTour.py](trees/euler_tour/EulerTour.py): entry and exit times, so a subtree is a range

## Dynamic programming

- [dynamic_programming/digit_dp/DigitDP.py](dynamic_programming/digit_dp/DigitDP.py): `count_up_to(N, start, step, accept)`

## Range queries

- [data_structures/1d_range_query/FenwickTree.py](data_structures/1d_range_query/FenwickTree.py)
- [data_structures/1d_range_query/IterativeSegmentTree.py](data_structures/1d_range_query/IterativeSegmentTree.py)
- [data_structures/1d_range_query/SegmentTree.py](data_structures/1d_range_query/SegmentTree.py): any `combine` and `identity`
- [data_structures/1d_range_query/SRD.py](data_structures/1d_range_query/SRD.py): square root decomposition
- [data_structures/1d_range_query/Mo.py](data_structures/1d_range_query/Mo.py): Mo's algorithm with `add`/`remove`/`answer` callbacks
- [data_structures/rurq/LazySegmentTree.py](data_structures/rurq/LazySegmentTree.py): range add, range sum
- [data_structures/rurq/SparseSegmentTree.py](data_structures/rurq/SparseSegmentTree.py): range assign over a huge range
- [data_structures/rurq/PersistentSegmentTree.py](data_structures/rurq/PersistentSegmentTree.py): every version stays readable
- [data_structures/compress/CSR.py](data_structures/compress/CSR.py): compressed sparse row
- [utils/CoordinateCompression.py](utils/CoordinateCompression.py)

## Math

- [math/modular_arithmetic/ModFact.py](math/modular_arithmetic/ModFact.py): factorials and `nCk`
- [math/modular_arithmetic/ModInv.py](math/modular_arithmetic/ModInv.py): `binpow` and `modInverse`

## Strings

- [strings/rolling_hash/RollingHash.py](strings/rolling_hash/RollingHash.py)
- [strings/trie/Trie.py](strings/trie/Trie.py), [strings/trie/FileSystem.py](strings/trie/FileSystem.py)

## Databases

- [databases/data_structures/BloomFilter.py](databases/data_structures/BloomFilter.py)
- [databases/data_structures/CountMinSketch.py](databases/data_structures/CountMinSketch.py)
- [databases/data_structures/CuckooFilter.py](databases/data_structures/CuckooFilter.py)
- [databases/data_structures/Skiplist.py](databases/data_structures/Skiplist.py)
- [databases/data_structures/utils/hash.py](databases/data_structures/utils/hash.py)
