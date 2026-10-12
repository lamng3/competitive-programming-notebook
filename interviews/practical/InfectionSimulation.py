from collections import deque

# Grid: 'X' infected on day 0, '.' healthy, '#' immune. Each day an infected cell
# infects its 4 neighbors; D days after infection it recovers and becomes immune.
# Return the day the last infected cell recovers (0 if nothing is ever infected).
#
# Recovery never stops a spread: a cell infected on day t infects its neighbors on
# day t + 1, before it recovers on day t + D (D >= 1), and a recovered cell cannot be
# infected again. So every cell is infected exactly once, at its BFS distance from the
# nearest 'X', and the answer is that largest distance plus D: a multi-source BFS.

dr = [1, -1, 0, 0]
dc = [0, 0, 1, -1]


def last_recovery_day(grid: list, D: int) -> int:
    n, m = len(grid), len(grid[0])

    def inrange(r: int, c: int):
        return 0 <= r and r < n and 0 <= c and c < m

    day = [[-1] * m for _ in range(n)] # infection day, -1 never
    q = deque()
    for r in range(n):
        for c in range(m):
            if grid[r][c] == "X":
                day[r][c] = 0
                q.append((r, c))
    if not q: return 0
    last = 0
    while q:
        r, c = q.popleft()
        last = day[r][c]
        for i in range(4):
            nr, nc = r + dr[i], c + dc[i]
            if not inrange(nr, nc) or day[nr][nc] != -1 or grid[nr][nc] == "#": continue
            day[nr][nc] = day[r][c] + 1
            q.append((nr, nc))
    return last + D
