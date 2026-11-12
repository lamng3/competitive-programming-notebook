# Farach-Colton and Bender LCA

LCA in O(n) build and O(1) per query.

| File | What it is |
|:--|:--|
| `FCB.h` | the class to include: `FCB fcb(adj, root); fcb.lca(u, v);` |
| `tests/fcb_test.cpp` | unit test, run with `cpunit fcb` |
| `notebook/examples/trees/farach-colton_bender/fcb.cpp` | the same code as a full solution, written step by step |

Reference: <https://cp-algorithms.com/graph/lca_farachcoltonbender.html>

These notes answer the questions that come up when reading the code again.

---

## The idea in one paragraph

Walk the tree as an Euler tour and write down every vertex we pass, including
each time we come back up to it. Between a visit of `u` and a visit of `v`, the
shallowest vertex is `lca(u, v)`. So LCA becomes a range-minimum query (RMQ) over
the heights along the tour. Neighbouring heights in the tour differ by exactly
1, and that is what lets the RMQ answer in O(1) after O(n) work.

```
lca(u, v) = euler[argmin(nodeStart[u], nodeStart[v])]
```

## Build steps

1. **Euler tour**: `euler[]`, `nodeStart[]`, `nodeHeight[]`
2. **Heights**: `arr[i] = nodeHeight[euler[i]]`
3. **Log table**: `lg2[]` (`fcb.cpp` builds it once in `preprocess`)
4. **+-1 RMQ on `arr`**:
   a sparse table over blocks, then block masks, then mask tables

## Code map

The two files use the same names, so this table works for both.

| Function | What it does |
|:--|:--|
| `buildLog(m)` | `lg2[x] = lg2[x/2] + 1`, with `lg2[0] = -1` |
| `eulerTour(u, p, h)` | writes `u`, recurses into each child, writes `u` again after each one |
| `buildEulerTour(n, root)` | resets the arrays and runs the tour from `root` |
| `minIdx(i, j)` | the position with the smaller `arr` value |
| `buildBlockSparseTable()` | `st[b][0]` = min of block `b`; `st[b][k]` combines two runs of `2^(k-1)` blocks |
| `querySparseTable(bl, br)` | min of blocks `[bl, br]` from two overlapping runs, `k = lg2[br - bl + 1]` |
| `buildBlockMasks()` | one bit per step inside each block, 1 = up |
| `buildMaskTables()` | for every mask and every `l`, walk right and keep the lowest running height |
| `queryInBlock(b, l, r)` | `maskTable[blockMask[b]][l][r]` turned back into a tour position |
| `buildRMQ()` | picks the block size, then builds the sparse table, masks and mask tables |
| `argmin(l, r)` | one block, or the suffix of `l`'s block + whole blocks in between + the prefix of `r`'s block |
| `buildLCA(n, root)` / `FCB(adj, root)` | builds the tour, the heights and the RMQ, in that order |
| `lca(u, v)` | `euler[argmin(nodeStart[u], nodeStart[v])]` |

## The tour on a small tree

```
        1
      /   \
     2     3
    / \   / \
   4   5 6   7
```

```
pos     0 1 2 3 4 5 6 7 8 9 10 11 12
euler   1 2 4 2 5 2 1 3 6 3 7  3  1
height  0 1 2 1 2 1 0 1 2 1 2  1  0
```

```
tour(u):
    write u
    for each child v:
        tour(v)
        write u          <- back up through u
```

The tour has `2n - 1` entries. Each step goes down to a child or back up to
the parent, so neighbouring heights differ by exactly 1.

## Why the minimum in the range is the LCA

Take `lca(4, 6)`. The range is `euler[2..8]`:

```
euler   4 2 5 2 1 3 6
height  2 1 2 1 0 1 2       min height 0 at vertex 1 = lca(4, 6)
```

Two facts make this work for any `u`, `v`:

1. **The walk never goes above the LCA.** Both `u` and `v` are inside the
   LCA's subtree. The tour stays inside that subtree from when it enters the
   LCA until it leaves it, so nothing shallower appears in the range.
2. **The walk passes through the LCA.** To get from `u`'s branch to `v`'s
   branch, the tour has to come back up to the LCA. If `u` is the LCA itself
   (`u` is an ancestor of `v`), then `u` is at the end of the range.

Ties are harmless: inside the LCA's subtree, the LCA is the only vertex at its
height, so every position holding the minimum height holds the LCA.

## Why only `nodeStart`, and no `nodeEnd`

`nodeStart[u]` is where `u` first appears in the tour. There is no `nodeEnd`,
because a query needs just one position per vertex, and any visit of `u` with
any visit of `v` gives the same answer. Facts 1 and 2 above hold for every
visit: each visit of `u` lies inside the LCA's part of the tour, and going from
`u` to `v` still has to pass through the LCA.

So the query doesn't care whether `u` or `v` is finished when it is visited.
The first visit is just a single, convenient position to keep: one `int` per
vertex, filled in when the tour enters `u`.

`lca(2, 6)` gives the same answer from the first visit of 2 and from its last:

```
first visit of 2 (pos 1) .. first visit of 6 (pos 8)
euler   2 4 2 5 2 1 3 6
height  1 2 1 2 1 0 1 2     -> 1

last visit of 2 (pos 5) .. first visit of 6 (pos 8)
euler   2 1 3 6
height  1 0 1 2             -> 1
```

## The range is not a subtree

`euler[2..8]` above is part of 2's subtree, then vertex 1, then part of 3's
subtree. It is a walk from `u` to `v` through the LCA, not a subtree.

The other tree flattening in this notebook, `notebook/trees/euler_tour/EulerTour.h`,
is for a different job:

| | `EulerTour.h` (`S`, `E`) | FCB tour (`nodeStart`) |
|:--|:--|:--|
| each vertex is written | once | on entry and after each child |
| length | `n` | `2n - 1` |
| a contiguous range is | a whole subtree, `[S[u], E[u])` | a walk between two vertices |
| used for | subtree queries: sum over u's subtree | LCA as a range minimum |
| needs an end index | yes, `E[u]` closes the subtree | no, any one visit works |

## The +-1 RMQ

`argmin(l, r)` returns the position of the minimum of `arr[l..r]`, where
`arr[i] = nodeHeight[euler[i]]`. This part never looks at the tree. It works
for any array whose neighbours differ by exactly 1.

Cut `arr` into blocks of `b = log2(m) / 2` entries. A query splits into three
parts:

```
l ... ] [ block ] [ block ] ... [ block ] [ ... r
suffix of     whole blocks in between      prefix of
l's block                                  r's block
```

- **Whole blocks**: a sparse table over the block minimums.
  `st[b][k]` is the position of the minimum of blocks `[b, b + 2^k)`. There are
  only `m / b` blocks, so the table takes `(m / b) log(m / b) = O(m)`. Like the
  rest of the RMQ, it covers runs of tour positions, not subtrees.
- **Inside a block**: a block is `b - 1` steps, each +1 or -1, so its shape is
  a `(b - 1)`-bit mask. Where the minimum of `[l, r]` sits depends only on that
  mask, not on the actual heights. We precompute the answer for every mask
  once: `2^(b-1) <= sqrt(m)` masks with `b^2` answers each.

### Block masks on the small tree

With `b = 3` (the real code would pick `b = 1` for 13 entries; 3 just shows it
better):

```
blocks   [0 1 2] [1 2 1] [0 1 2] [1 2 1] [0]
steps     + +     + -     + +     + -
mask      0b11    0b01    0b11    0b01    0
```

Bit `j-1` is the step from offset `j-1` to `j`: 1 for up, 0 for down. Blocks 1
and 3 have the same mask, so they share one table. The short last block reads
its missing steps as 0, and no query ever reaches them.

`maskTable[0b01]` (shape: up, then down, so relative heights `0 1 0`):

```
       r=0  r=1  r=2
l=0     0    0    0      tie at offsets 0 and 2: keep the left one
l=1          1    2
l=2               2
```

It is built from the mask alone: walk right from `l` with a running height
`h`, and keep where `h` was lowest.

## Sizes at n = 5 * 10^5

| | value |
|:--|:--|
| tour length `m` | 999,999 |
| block size `b` | `lg2[m] / 2 = 19 / 2 = 9` |
| blocks | 111,111 |
| sparse table levels | `lg2[111111] + 1 = 17` |
| masks | `2^8 = 256`, 81 answers each |

## Pitfalls hit while writing it

- **`lg2` must cover the tour, not `n`.** The tour has `2n - 1` entries, so
  build `lg2` up to `2 * MAX_N`. Also use `assign`, not `push_back`, then index
  into it.
- **Edges are undirected.** Store `a - b` both ways, or the tour misses
  children listed second.
- **Write `u` again after each child.** A tour that writes each vertex once
  (the `EulerTour.h` kind) loses the +-1 property and the "walk passes through
  the LCA" fact.
- **Recursion depth.** A path of 5 * 10^5 vertices recurses that deep. That is fine
  on Codeforces; locally run `ulimit -s 65520` first.
- **`cin` on a Mac is slow.** Reading 2 * 10^6 numbers takes about 1.9s locally
  but about 0.15s on a Linux judge. The algorithm itself takes about 0.2s.
