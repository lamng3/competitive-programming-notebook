"""The patterns to write from memory, and to review a solution against.

Control flow stays traditional: explicit loops, a queue, a stack, left <= right.
Python only shortens the bookkeeping (accumulate, Counter, cache, sorted(set())).
Every function here runs; copy its shape, not its name.
"""
from collections import Counter, deque
from functools import cache
from heapq import heappop, heappush
from itertools import accumulate
from math import inf

dr = [1, -1, 0, 0]
dc = [0, 0, 1, -1]


# ---------- prefix sums ----------

# P[i] = a[0] + ... + a[i-1], so sum(a[l..r]) = P[r+1] - P[l]
def prefix_sums(a: list) -> list:
    return list(accumulate(a, initial=0))


# P[r][c] = sum of g[0..r-1][0..c-1]
# sum of g[r1..r2][c1..c2] = P[r2+1][c2+1] - P[r1][c2+1] - P[r2+1][c1] + P[r1][c1]
def prefix_sums_2d(g: list) -> list:
    n, m = len(g), len(g[0])
    P = [[0] * (m + 1) for _ in range(n + 1)] # never [[0] * (m+1)] * (n+1): one row, aliased
    for r in range(n):
        for c in range(m):
            P[r + 1][c + 1] = g[r][c] + P[r][c + 1] + P[r + 1][c] - P[r][c]
    return P


# ---------- binary search on the answer ----------

# smallest x in [lo, hi] with valid(x), where valid is False ... False True ... True
# hi + 1 if there is none; on a sorted list, bisect_left / bisect_right do this
def binary_search(lo: int, hi: int, valid) -> int:
    ans = hi + 1
    left, right = lo, hi
    while left <= right:
        mid = left + (right - left) // 2
        if valid(mid):
            ans = mid
            right = mid - 1
        else: left = mid + 1
    return ans


# ---------- BFS ----------

# fewest steps from (sr, sc) to every cell, -1 if unreachable; grid[r][c] == 1 is a wall
def bfs_grid(grid: list, sr: int, sc: int) -> list:
    n, m = len(grid), len(grid[0])

    def inrange(r: int, c: int):
        return 0 <= r and r < n and 0 <= c and c < m

    dist = [[-1] * m for _ in range(n)] # doubles as seen
    dist[sr][sc] = 0
    q = deque()
    q.append((sr, sc))
    while q:
        r, c = q.popleft()
        for i in range(4):
            nr, nc = r + dr[i], c + dc[i]
            if not inrange(nr, nc) or dist[nr][nc] != -1 or grid[nr][nc] == 1: continue
            dist[nr][nc] = dist[r][c] + 1
            q.append((nr, nc))
    return dist


# fewest edges from s to every vertex, -1 if unreachable; g[u] = list of neighbors
def bfs(g: list, s: int) -> list:
    dist = [-1] * len(g)
    dist[s] = 0
    q = deque()
    q.append(s)
    while q:
        u = q.popleft()
        for v in g[u]:
            if dist[v] != -1: continue
            dist[v] = dist[u] + 1
            q.append(v)
    return dist


# ---------- DFS ----------

# number of 4-connected groups of 1s
def count_islands(grid: list) -> int:
    n, m = len(grid), len(grid[0])
    seen = set()

    def inrange(r: int, c: int):
        return 0 <= r and r < n and 0 <= c and c < m

    def dfs(r: int, c: int):
        seen.add((r, c))
        for i in range(4):
            nr, nc = r + dr[i], c + dc[i]
            if not inrange(nr, nc) or (nr, nc) in seen or grid[nr][nc] == 0: continue
            dfs(nr, nc)

    ans = 0
    for r in range(n):
        for c in range(m):
            if grid[r][c] == 1 and (r, c) not in seen:
                dfs(r, c)
                ans += 1
    return ans


# subtree sizes of a tree rooted at 0; a tree needs a parent, not a seen set
def subtree_sizes(g: list) -> list:
    sz = [1] * len(g)

    def dfs(u: int, p: int):
        for v in g[u]:
            if v == p: continue
            dfs(v, u)
            sz[u] += sz[v]

    dfs(0, -1)
    return sz


# ---------- shortest paths and order ----------

# g[u] = list of (v, w) with w >= 0
def dijkstra(g: list, s: int) -> list:
    dist = [inf] * len(g)
    dist[s] = 0
    pq = [(0, s)]
    while pq:
        d, u = heappop(pq)
        if d > dist[u]: continue # stale entry: a shorter path already settled u
        for v, w in g[u]:
            if d + w < dist[v]:
                dist[v] = d + w
                heappush(pq, (dist[v], v))
    return dist


# Kahn's algorithm: a topological order of 0..n-1, or [] if there is a cycle
def topo_sort(n: int, edges: list) -> list:
    g = [[] for _ in range(n)]
    indeg = [0] * n
    for u, v in edges:
        g[u].append(v)
        indeg[v] += 1
    q = deque(u for u in range(n) if indeg[u] == 0)
    order = []
    while q:
        u = q.popleft()
        order.append(u)
        for v in g[u]:
            indeg[v] -= 1
            if indeg[v] == 0: q.append(v)
    return order if len(order) == n else []


# ---------- windows and stacks ----------

# longest substring with at most k distinct characters
def longest_k_distinct(s: str, k: int) -> int:
    cnt = Counter()
    ans = left = 0
    for right, ch in enumerate(s):
        cnt[ch] += 1
        while len(cnt) > k: # shrink until the window is valid again
            cnt[s[left]] -= 1
            if cnt[s[left]] == 0: del cnt[s[left]] # else len(cnt) never drops
            left += 1
        ans = max(ans, right - left + 1)
    return ans


# nxt[i] = first j > i with a[j] > a[i], or n
def next_greater(a: list) -> list:
    n = len(a)
    nxt = [n] * n
    st = [] # indices whose answer is not known yet, values decreasing
    for i in range(n):
        while st and a[st[-1]] < a[i]:
            nxt[st.pop()] = i
        st.append(i)
    return nxt


# ---------- backtracking and DP ----------

# every subset of a, in the order the recursion meets them
def subsets(a: list) -> list:
    ans, path = [], []

    def backtrack(i: int):
        if i == len(a):
            ans.append(path[:]) # copy: path keeps changing
            return
        backtrack(i + 1)        # skip a[i]
        path.append(a[i])       # take a[i]
        backtrack(i + 1)
        path.pop()

    backtrack(0)
    return ans


# longest common subsequence: @cache replaces the memo table
def lcs(s: str, t: str) -> int:
    @cache
    def dp(i: int, j: int) -> int:
        if i == len(s) or j == len(t): return 0
        if s[i] == t[j]: return 1 + dp(i + 1, j + 1)
        return max(dp(i + 1, j), dp(i, j + 1))

    return dp(0, 0)


# ---------- one-liners ----------

# coordinate compression: value -> rank in sorted order
def compress(a: list) -> list:
    rank = {x: i for i, x in enumerate(sorted(set(a)))}
    return [rank[x] for x in a]
