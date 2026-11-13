# Farach-Colton and Bender LCA

LCA in O(n) build and O(1) per query, following
[cp-algorithms](https://cp-algorithms.com/graph/lca_farachcoltonbender.html).

| File | What it is |
|:--|:--|
| `FCB.h` | the class to include: `FCB fcb(adj, root); fcb.lca(u, v);` |
| `tests/fcb_test.cpp` | unit test, run with `cpunit fcb` |
| `notebook/examples/trees/farach-colton_bender/fcb.cpp` | the same code as a full solution |

**In a contest**, use a plain sparse table over the whole Euler tour instead. It
is O(n log n) to build, still O(1) per query, and has no blocks or masks. See
`contests/codeforces/342d2/E.cpp`. Part 1 below proves that version too.

The algorithm has two parts:

1. **LCA to RMQ.** The LCA of `u` and `v` is the shallowest vertex between them
   in the Euler tour.
2. **±1 RMQ.** Neighbouring heights in the tour differ by exactly 1, so the
   range minimum can be answered in O(1) after O(n) work.

---

## Part 1: LCA is the shallowest vertex between u and v in the tour

**Notation.** `T[0..m-1]` is the tour (`euler_tour`), `h(x)` is the depth of
`x` (`height`), `sub(x)` is the subtree of `x`, and `first(x)` and `last(x)`
are the first and last indices where `x` appears in `T`.

`flatten(v)` writes `v`, then for each child `c` calls `flatten(c)` and writes
`v` again.

On this tree, rooted at 1, with children 2, 3 under 1, children 4, 5 under 2,
and children 6, 7 under 3:

```
index  0 1 2 3 4 5 6 7 8 9 10 11 12
T      1 2 4 2 5 2 1 3 6 3 7  3  1
h      0 1 2 1 2 1 0 1 2 1 2  1  0
```

### Lemma 1: shape of the tour

`m = 2n - 1`, and neighbouring entries are always a vertex and its parent, so
`|h(T[i+1]) - h(T[i])| = 1`.

*Proof.* Each vertex is written once on entry, and its parent is written once
more when it returns, which is once per edge: `n + (n - 1)` entries. A write
after `v` is either a child of `v` being entered (+1), or `v`'s parent being
written after `flatten(v)` returns (−1). ∎

### Lemma 2: a subtree is one contiguous block of the tour

`T[first(x) .. last(x)]` contains exactly the entries of the vertices in
`sub(x)`. Every entry in it has height at least `h(x)`, and only `x` itself
has height exactly `h(x)`.

*Proof.* `flatten(x)` makes its first write at `first(x)` and its last write at
`last(x)`. Everything written in between comes from calls on descendants of
`x`, and every call on a descendant runs in between. Descendants other than `x`
are deeper than `x`. ∎

### Theorem: the shallowest entry between u and v is lca(u, v)

Let `w = lca(u, v)`, and take any index `i` of `u` and any index `j` of `v`,
with `i <= j`. Then `w` appears in `T[i..j]`, and every other entry in
`T[i..j]` is deeper than `w`.

*Proof.* Since `u` and `v` are in `sub(w)`, Lemma 2 puts `i` and `j` inside
`[first(w), last(w)]`, so all of `T[i..j]` lies in `sub(w)`. Every entry has
height at least `h(w)`, and only `w` has height exactly `h(w)`. It remains to
show that `w` appears in `T[i..j]`.

- If `u = w` or `v = w`, then `T[i]` or `T[j]` is `w`.
- Otherwise `u` and `v` lie under two different children `c1` and `c2` of `w`.
  If they were under the same child, that child would be a deeper common
  ancestor. By Lemma 2, `c1`'s block holds `i` and `c2`'s block holds `j`.
  The blocks are disjoint and `i <= j`, so `c1`'s block comes first. Right
  after `flatten(c1)` returns, `flatten(w)` writes `w` at index `last(c1) + 1`,
  and that index is outside `c2`'s block. So
  `i <= last(c1) < last(c1) + 1 < first(c2) <= j`. ∎

Example: `lca(4, 6)` scans `T[2..8] = 4 2 5 2 1 3 6`. The heights are
`2 1 2 1 0 1 2`, so the shallowest entry is vertex 1.

### What follows from the theorem

- **One index per vertex is enough.** The theorem holds for any occurrence of
  `u` and of `v`, so the code stores only `first_visit`. There is no "last
  visit" array, and it doesn't matter whether `u` or `v` is finished at that
  index. For example, `lca(2, 6)` gives 1 starting from 2's first index (1)
  and from its last index (5).
- **Ties are harmless.** Only `w` reaches the minimum height in `T[i..j]`, so
  `min_by_h` can break ties either way.
- **The range is a walk from u to v, not a subtree.** `T[2..8]` above is part of
  2's subtree, then 1, then part of 3's subtree. Subtree ranges are a different
  flattening, `S` and `E` in `notebook/trees/euler_tour/EulerTour.h`, which
  writes each vertex once.
- **`v` must be written again after each child.** Without that write, the `w`
  between `c1` and `c2` in the proof doesn't exist. The tour becomes
  `1 2 4 5 3 6 7`, and `lca(4, 6)` scans `4 5 3 6` and answers 3 instead of 1.
  Lemma 1's ±1 steps also break.

So `lca(u, v) = T[argmin over [first(u), first(v)] of h]`, a range-minimum
query (RMQ) on `A[i] = h(T[i])`.

---

## Part 2: ±1 RMQ in O(m) build and O(1) query

Cut `A` into blocks of `b = max(1, floor(log2 m) / 2)` entries (`block_size`).
There are `c = ceil(m / b)` blocks (`block_cnt`). For a query `[l, r]`, let
`bl = l / b` and `br = r / b`.

- If `bl == br`, it's one in-block query.
- Otherwise `[l, r]` splits into three disjoint parts: the suffix of block `bl`,
  the whole blocks `bl+1 .. br-1` (possibly none), and the prefix of block
  `br`. The minimum of `[l, r]` is the smallest of the three parts' minimums.

The whole blocks use a sparse table, and the suffix and prefix use per-shape
tables.

### Lemma 3: sparse table over blocks

`st[x][0]` is the position of the minimum of block `x`.
`st[x][k] = min(st[x][k-1], st[x + 2^(k-1)][k-1])` covers blocks
`[x, x + 2^k)`. For blocks `[L, R]`, `query_sparse_table` takes
`k = floor(log2(R - L + 1))`.

*Proof.* `2^k <= R - L + 1 < 2^(k+1)`, so the runs `[L, L + 2^k)` and
`(R - 2^k, R]` both lie inside `[L, R]` and together cover it. They may
overlap, which is fine for min because `min(x, x) = x`. A query only reads
`st[x][k]` with `x + 2^k <= c`, so the build skips runs past the last block.

*Cost.* `c · log c <= (m / b) · log m ≈ 2m`, so O(m). ∎

### Lemma 4: blocks with the same mask share their answers

For a block starting at `s`, let `step_j = A[s+j] - A[s+j-1]` for
`j = 1 .. b-1`; each step is +1 or −1 by Lemma 1. Bit `j-1` of `block_mask` is
1 exactly when `step_j = +1`, meaning the tour goes one level deeper:

```cpp
if (j > 0 && height[euler_tour[i]] > height[euler_tour[i - 1]]) block_mask[b] |= 1 << (j - 1);
```

*Claim.* Two blocks with the same mask have the minimum of every `[l, r]` at the
same offset.

*Proof.* `A[s + j] = A[s] + step_1 + ... + step_j`, so a block's heights are
determined by its mask, up to the constant `A[s]`. Adding a constant to every
entry doesn't move the minimum. ∎

So `precompute_blocks` fills `blocks[mask][l][r]` once per mask, from the first
block that has it, and skips the rest. `lca_in_block(x, l, r)` reads
`blocks[block_mask[x]][l][r]` and adds `x · b` to turn the offset back into a
tour index.

Example with `b = 4`: heights `2 3 2 1` give steps `+ - -`, so mask `0b001`.
Heights `7 8 7 6` give the same mask, and both have their minimum at offset 3.

*The short last block.* If `b` doesn't divide `m`, the last block's missing
steps stay 0. Blocks are processed in order, so a table built from the last
block is only ever used by the last block, and the guard
`b * block_size + r < m` keeps it inside the tour. If an earlier full block has
the same mask, the two agree on every step the last block really has. Queries
never ask past `m - 1`.

### Lemma 5: total cost

There are at most `2^(b-1) <= 2^(log2(m)/2 - 1) = sqrt(m) / 2` masks, each with
a `b × b` table, for `O(sqrt(m) · log² m)`, which is much smaller than `m`.
Computing the masks is O(m), the sparse table is O(m) by Lemma 3, and the tour
is O(n). So the build is O(n). A query uses at most four table lookups, so
it's O(1). ∎

For `n = 5 · 10^5`: `m = 999,999`, `b = 9`, `c = 111,111` blocks, 17 sparse
table levels, and at most 256 masks with 81 entries each.

---

## Code map

| Function | Role |
|:--|:--|
| `flatten(v, p, h)` | the Euler tour: fills `euler_tour`, `first_visit`, `height` (Part 1) |
| `min_by_h(i, j)` | the tour index whose vertex is shallower |
| `precompute_log(m)` | `log_2[x] = floor(log2 x)`; `fcb.cpp` builds it once in `preprocess` |
| `precompute_sparse_table(m)` | block minimums and the sparse table over blocks (Lemma 3) |
| `query_sparse_table(L, R)` | minimum over whole blocks `[L, R]` (Lemma 3) |
| `precompute_block_mask(m)` | one bit per step inside each block (Lemma 4) |
| `precompute_blocks(m)` | in-block minimums, once per mask (Lemma 4) |
| `precompute_lca(root)` | tour, block size, then the three steps above |
| `lca_in_block(b, l, r)` | in-block minimum as a tour index |
| `lca(v, u)` | one block, or suffix + whole blocks + prefix |

## Pitfalls

- **Edges are undirected.** Store both directions.
- **`log_2` must cover the tour (`2n - 1` entries), not just `n`.**
- **Reset between test cases.** Use `assign` and `clear`. cp-algorithms'
  `push_back` and `resize` keep old data on a second call.
- **Recursion depth.** A path of 5 · 10^5 vertices recurses that deep. That's
  fine on Codeforces; locally, run `ulimit -s 65520` first.
