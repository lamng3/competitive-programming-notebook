# Interviews

Interview problems in C++ and Python, side by side. The set follows the topics in [minhcool/TrainingForInterviews](https://github.com/minhcool/TrainingForInterviews); the solutions here are written from scratch in the notebook's style.

Every folder has tests: `cpunit interviewleetcode`, `cpunit interviewdesign`, and `cpunit interviewpractical` run both languages.

## LeetCode: design and implementation

| Problem | Files | The idea |
| --- | --- | --- |
| [362 — Design Hit Counter](https://leetcode.com/problems/design-hit-counter/) | [cpp](leetcode/362.cpp), [py](leetcode/362.py) | A deque of (second, hits) buckets, so a burst is one entry |
| [380 — Insert Delete GetRandom O(1)](https://leetcode.com/problems/insert-delete-getrandom-o1/) | [cpp](leetcode/380.cpp), [py](leetcode/380.py) | Array plus index map; delete moves the last element into the hole |
| [460 — LFU Cache](https://leetcode.com/problems/lfu-cache/) | [cpp](leetcode/460.cpp), [py](leetcode/460.py) | One recency list per frequency, and the minimum frequency |
| [68 — Text Justification](https://leetcode.com/problems/text-justification/) | [cpp](leetcode/68.cpp), [py](leetcode/68.py) | Greedy lines, then base spaces plus one extra for the leftmost gaps |
| [347 — Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/) | [cpp](leetcode/347.cpp), [py](leetcode/347.py) | Bucket sort by frequency, O(n) |
| [1801 — Number of Orders in the Backlog](https://leetcode.com/problems/number-of-orders-in-the-backlog/) | [cpp](leetcode/1801.cpp), [py](leetcode/1801.py) | An order book: a max-heap of buys, a min-heap of sells |
| [1146 — Snapshot Array](https://leetcode.com/problems/snapshot-array/) | [cpp](leetcode/1146.cpp), [py](leetcode/1146.py) | Store only changes, binary search the history |

## Design

| Problem | Files | The idea |
| --- | --- | --- |
| Connect 4 | [cpp](design/Connect4.cpp), [py](design/Connect4.py) | A win passes through the last disc: check its 4 lines, not the board |

## Practical

The kind asked in practical coding rounds: a small real system, with the edge cases that make it real.

| Problem | Files | The idea |
| --- | --- | --- |
| `cd` with symlinks | [cpp](practical/ChangeDirectory.cpp), [py](practical/ChangeDirectory.py) | A stack of names, resolved through links after every step; a loop is an error |
| IPv4 range and CIDR iterator | [cpp](practical/IPv4Iterator.cpp), [py](practical/IPv4Iterator.py) | An address is a 32-bit number: parse, count, format |
| Infection simulation | [cpp](practical/InfectionSimulation.cpp), [py](practical/InfectionSimulation.py) | Recovery never blocks a spread, so it is a multi-source BFS plus D |
| Tree size by messages | [cpp](practical/TreeMessages.cpp), [py](practical/TreeMessages.py) | Count down, sizes up; retries with backoff, and duplicates counted once |
