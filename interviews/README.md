# Interviews

Interview problems, one folder per question. Each folder has `solution.cpp`, `solution.py`, and a `tests/` folder; `cpunit <folder>` runs the tests in both languages, e.g. `cpunit lfu_cache`.

## LeetCode: design and implementation

| Question | The idea |
| --- | --- |
| [design_hit_counter](design_hit_counter) — [362](https://leetcode.com/problems/design-hit-counter/) | A deque of (second, hits) buckets, so a burst is one entry |
| [insert_delete_getrandom_o1](insert_delete_getrandom_o1) — [380](https://leetcode.com/problems/insert-delete-getrandom-o1/) | Array plus index map; delete moves the last element into the hole |
| [lfu_cache](lfu_cache) — [460](https://leetcode.com/problems/lfu-cache/) | One recency list per frequency, and the minimum frequency |
| [text_justification](text_justification) — [68](https://leetcode.com/problems/text-justification/) | Greedy lines, then base spaces plus one extra for the leftmost gaps |
| [top_k_frequent_elements](top_k_frequent_elements) — [347](https://leetcode.com/problems/top-k-frequent-elements/) | Bucket sort by frequency, O(n) |
| [number_of_orders_in_the_backlog](number_of_orders_in_the_backlog) — [1801](https://leetcode.com/problems/number-of-orders-in-the-backlog/) | An order book: a max-heap of buys, a min-heap of sells |
| [snapshot_array](snapshot_array) — [1146](https://leetcode.com/problems/snapshot-array/) | Store only changes, binary search the history |

## Design

| Question | The idea |
| --- | --- |
| [connect_four](connect_four) | A win passes through the last disc: check its 4 lines, not the board |

## Practical

A small real system, with the edge cases that make it real.

| Question | The idea |
| --- | --- |
| [change_directory](change_directory) | `cd` with symlinks: a stack of names, resolved through links after every step; a loop is an error |
| [ipv4_iterator](ipv4_iterator) | An address is a 32-bit number: parse, count, format; ranges and CIDR blocks, both directions |
| [infection_simulation](infection_simulation) | Recovery never blocks a spread, so it is a multi-source BFS plus D |
| [tree_messages](tree_messages) | Tree size by messages: count down, sizes up; retries with backoff, duplicates counted once |
