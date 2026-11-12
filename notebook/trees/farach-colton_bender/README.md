# Farach-Colton and Bender LCA

LCA in O(n) build and O(1) per query. The code follows
[cp-algorithms](https://cp-algorithms.com/graph/lca_farachcoltonbender.html) with the same names,
with its `precompute_lca` split into named steps.

| File | What it is |
|:--|:--|
| `FCB.h` | the class to include: `FCB fcb(adj, root); fcb.lca(u, v);` |
| `tests/fcb_test.cpp` | unit test, run with `cpunit fcb` |
| `notebook/examples/trees/farach-colton_bender/fcb.cpp` | the same code as a full solution |

These notes answer the questions that come up when reading the code again.

---

## The idea in one paragraph

Walk the tree as an Euler tour and write down every vertex we pass, including
each time we come back up to it. Between a visit of `u` and a visit of `v`, the
shallowest vertex is `lca(u, v)`. So LCA becomes a range-minimum query (RMQ) by
height over the tour. Neighbouring heights in the tour differ by exactly 1, and
that is what lets the RMQ answer in O(1) after O(n) work.

```
lca(u, v) = shallowest vertex in euler_tour[first_visit[u] .. first_visit[v]]
```

## Code map

| Function | What it does |
|:--|:--|
| `dfs(v, p, h)` | writes `v`, recurses into each child, writes `v` again after each one |
| `min_by_h(i, j)` | of two `euler_tour` indices, the one whose vertex is shallower |
| `precompute_log(m)` | `log_2[x] = log_2[x/2] + 1`, with `log_2[0] = -1` |
| `precompute_sparse_table(m)` | `st[b][0]` = min of block `b`; `st[b][k]` combines two runs of `2^(k-1)` blocks |
| `precompute_block_mask(m)` | one bit per step inside each block, 1 = height + 1 |
| `precompute_blocks(m)` | for each mask, the min of every `[l, r]` inside a block of that shape |
| `precompute_lca(root)` | runs the tour, picks the block size, then the three steps above |
| `lca_in_block(b, l, r)` | `blocks[block_mask[b]][l][r]` turned back into a tour index |
| `lca(v, u)` | one block, or the suffix of `l`'s block + whole blocks in between + the prefix of `r`'s block |

`min_by_h` compares heights straight from the tour, so there is no separate
array of heights to keep in sync.

## The tour on a small tree

```
        1
      /   \
     2     3
    / \   / \
   4   5 6   7
```

```
index       0 1 2 3 4 5 6 7 8 9 10 11 12
euler_tour  1 2 4 2 5 2 1 3 6 3 7  3  1
height      0 1 2 1 2 1 0 1 2 1 2  1  0
```

```
dfs(v):
    write v
    for each child u:
        dfs(u)
        write v          <- back up through v
```

The tour has `2n - 1` entries: `n` entries on entry, plus one for each of the
`n - 1` edges on the way back up.

## Why the minimum in the range is the LCA

Take `lca(4, 6)`. The range is `euler_tour[2..8]`:

```
euler_tour  4 2 5 2 1 3 6
height      2 1 2 1 0 1 2       min height 0 at vertex 1 = lca(4, 6)
```

Two facts make this work for any `u`, `v`:

1. **The walk never goes above the LCA.** Both `u` and `v` are inside the
   LCA's subtree. The tour stays inside that subtree from when it enters the
   LCA until it leaves it, so nothing shallower appears in the range.
2. **The walk passes through the LCA.** To get from `u`'s branch to `v`'s
   branch, the tour has to come back up to the LCA. If `u` is the LCA itself
   (`u` is an ancestor of `v`), then `u` is at the end of the range.

Ties are harmless: inside the LCA's subtree, the LCA is the only vertex at its
height, so every index holding the minimum height holds the LCA.

## Why we write `v` again after each child

Without `euler_tour.push_back(v)` after each child, each vertex is written once:

```
euler_tour  1 2 4 5 3 6 7
height      0 1 2 2 1 2 2
```

`lca(4, 6)` would look at `4 5 3 6` and answer 3, but the LCA is 1. Vertex 1
was only written at the start, so it never appears between 4 and 6. Fact 2
above fails.

It also breaks the +-1 steps. Without the re-writes the tour can jump from a
deep leaf straight to the next branch, several levels up in one step, and the
block masks only describe steps of +1 or -1.

## Why only `first_visit`, and no last visit

`first_visit[v]` is where `v` first appears in the tour. There is no last visit
array, because a query needs just one index per vertex, and any visit of `u`
with any visit of `v` gives the same answer. Facts 1 and 2 hold for every visit:
each visit of `u` lies inside the LCA's part of the tour, and going from `u` to
`v` still passes through the LCA.

So the query doesn't care whether `u` or `v` is finished when it is visited.
The first visit is just a single, convenient index to keep, filled in when the
tour enters `v`.

`lca(2, 6)` gives the same answer from the first visit of 2 and from its last:

```
first visit of 2 (index 1) .. first visit of 6 (index 8)
euler_tour  2 4 2 5 2 1 3 6
height      1 2 1 2 1 0 1 2     -> 1

last visit of 2 (index 5) .. first visit of 6 (index 8)
euler_tour  2 1 3 6
height      1 0 1 2             -> 1
```

## The range is not a subtree

`euler_tour[2..8]` above is part of 2's subtree, then vertex 1, then part of
3's subtree. It is a walk from `u` to `v` through the LCA, not a subtree. The
sparse table and the blocks are cuts of the tour by index. They never line up
with subtrees.

The other tree flattening in this notebook, `notebook/trees/euler_tour/EulerTour.h`,
is for a different job:

| | `EulerTour.h` (`S`, `E`) | FCB tour (`first_visit`) |
|:--|:--|:--|
| each vertex is written | once | on entry and after each child |
| length | `n` | `2n - 1` |
| a contiguous range is | a whole subtree, `[S[u], E[u])` | a walk between two vertices |
| used for | subtree queries: sum over u's subtree | LCA as a range minimum |
| needs an end index | yes, `E[u]` closes the subtree | no, any one visit works |

## The RMQ in three parts

Cut the tour into blocks of `block_size = log2(m) / 2` entries. A query
`[l, r]` splits into three parts:

```
l ... ] [ block ] [ block ] ... [ block ] [ ... r
suffix of     whole blocks in between      prefix of
l's block                                  r's block
```

- **Whole blocks**: `st[b][k]` is the min of blocks `[b, b + 2^k)`. There are
  `m / block_size` blocks with `log(m)` levels each, so O(m) in total. A query
  takes two runs of `2^k` blocks that may overlap, and that is fine for min,
  because `min(x, x) = x`.
- **Inside a block**: a block is `block_size - 1` steps of +1 or -1, so its
  shape is a bitmask. The height at offset `r` is the height at offset 0 plus
  the steps before `r`, so two blocks with the same mask differ only by a
  constant and have their minimums in the same places. `blocks[mask]` is built
  once per mask, from the first block with that mask: at most
  `2^(block_size - 1) <= sqrt(m)` masks with `block_size^2` entries each.

### Block masks on the small tree

With `block_size = 3` (the real code picks 1 for 13 entries; 3 shows it better):

```
blocks   [0 1 2] [1 2 1] [0 1 2] [1 2 1] [0]
steps     + +     + -     + +     + -
mask      0b11    0b01    0b11    0b01    0
```

Bit `j-1` is the step from offset `j-1` to `j`: 1 when the height goes up by 1
(one level deeper), 0 when it goes down. Blocks 1 and 3 have the same mask, so
they share one table. The short last block skips offsets past the end of the
tour, and no query reaches them.

`blocks[0b01]`, built from block 1 (heights `1 2 1`):

```
       r=0  r=1  r=2
l=0     0    0    2      tie between offsets 0 and 2: min_by_h keeps the right one
l=1          1    2
l=2               2
```

On a tie both offsets hold the same vertex, so either answer is correct.

## Sizes at n = 5 * 10^5

| | value |
|:--|:--|
| tour length `m` | 999,999 |
| `block_size` | `log_2[m] / 2 = 19 / 2 = 9` |
| `block_cnt` | 111,111 |
| sparse table levels | `log_2[111111] + 1 = 17` |
| masks | at most `2^8 = 256`, 81 entries each |

## Pitfalls

- **Edges are undirected.** Store `a - b` both ways, or the tour misses
  children listed second.
- **`log_2` must cover the tour, not `n`.** The tour has `2n - 1` entries.
- **Reset between test cases.** cp-algorithms builds `log_2` with `push_back`
  and `blocks` with `resize`, which keep old data on a second call. This code
  uses `assign` and `clear`.
- **Recursion depth.** A path of 5 * 10^5 vertices recurses that deep. That is
  fine on Codeforces; locally run `ulimit -s 65520` first.
- **`cin` on a Mac is slow.** Reading 2 * 10^6 numbers takes about 1.9s locally
  but about 0.15s on a Linux judge. The algorithm itself takes about 0.2s.
