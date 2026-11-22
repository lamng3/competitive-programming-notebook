# LeetCode

Solutions are in `solve/`, by technique (contests in `weekly/` and `biweekly/`), and in `upsolve/`, for problems redone after a contest. `tests/` caches LeetCode's examples for `cptest`.

## USACO Guide on LeetCode

LeetCode practice for the modules of the USACO Guide's [Platinum](https://usaco.guide/plat) and [Advanced](https://usaco.guide/adv) sections: 140 handpicked problems, at most ten a module, easiest first by [contest rating](https://github.com/zerotrac/leetcode_problem_rating) (older problems have none). They are Hard unless marked Medium; 🔒 is premium. A ✓ links to a solution here (18 so far). For modules LeetCode doesn't cover, use the guide's own problems.

### Platinum

#### Range Queries

| Module | Problem | Rating |
|:--|:--|--:|
| [More Applications of Segment Tree](https://usaco.guide/plat/segtree-ext) | [3479. Fruits Into Baskets III](https://leetcode.com/problems/fruits-into-baskets-iii/) (Medium) | 2178 |
|  | [2940. Find Building Where Alice and Bob Can Meet](https://leetcode.com/problems/find-building-where-alice-and-bob-can-meet/) | 2327 |
|  | [2286. Booking Concert Tickets in Groups](https://leetcode.com/problems/booking-concert-tickets-in-groups/) | 2470 |
|  | [2213. Longest Substring of One Repeating Character](https://leetcode.com/problems/longest-substring-of-one-repeating-character/) | 2629 |
|  | [3165. Maximum Sum of Subsequence With Non-adjacent Elements](https://leetcode.com/problems/maximum-sum-of-subsequence-with-non-adjacent-elements/) | 2698 |
|  | [3410. Maximize Subarray Sum After Removing All Occurrences of One Element](https://leetcode.com/problems/maximize-subarray-sum-after-removing-all-occurrences-of-one-element/) | 2844 |
| [Range Queries with Sweep Line](https://usaco.guide/plat/range-sweep) | [1964. Find the Longest Valid Obstacle Course at Each Position](https://leetcode.com/problems/find-the-longest-valid-obstacle-course-at-each-position/) | 1933 |
|  | [354. Russian Doll Envelopes](https://leetcode.com/problems/russian-doll-envelopes/) |  |
|  | [2407. Longest Increasing Subsequence II](https://leetcode.com/problems/longest-increasing-subsequence-ii/) | 2280 |
|  | [3382. Maximum Area Rectangle With Point Constraints II](https://leetcode.com/problems/maximum-area-rectangle-with-point-constraints-ii/) | 2723 |
| [Range Update Range Query](https://usaco.guide/plat/RURQ) | [2569. Handling Sum Queries After Update](https://leetcode.com/problems/handling-sum-queries-after-update/) | 2398 |
|  | [1622. Fancy Sequence](https://leetcode.com/problems/fancy-sequence/) | 2476 |
|  | [3569. Maximize Count of Distinct Primes After Split](https://leetcode.com/problems/maximize-count-of-distinct-primes-after-split/) | 2697 |
|  | [3721. Longest Balanced Subarray II](https://leetcode.com/problems/longest-balanced-subarray-ii/) | 2724 |
|  | [2916. Subarrays Distinct Element Sum of Squares II](https://leetcode.com/problems/subarrays-distinct-element-sum-of-squares-ii/) | 2816 |
| [Sparse Segment Trees](https://usaco.guide/plat/sparse-segtree) | [732. My Calendar III](https://leetcode.com/problems/my-calendar-iii/) |  |
|  | [715. Range Module](https://leetcode.com/problems/range-module/) |  |
|  | [2276. Count Integers in Intervals](https://leetcode.com/problems/count-integers-in-intervals/) | 2222 |
| [2D Range Queries](https://usaco.guide/plat/2DRQ) | [✓](solve/quadtree/308.py) [308. Range Sum Query 2D - Mutable](https://leetcode.com/problems/range-sum-query-2d-mutable/) (Medium, 🔒) |  |
| [Square Root Decomposition](https://usaco.guide/plat/sqrt) | [✓](solve/sqrt_decomposition/3943.cpp) [3943. Number of Pairs After Increment](https://leetcode.com/problems/number-of-pairs-after-increment/) | 2410 |
|  | [✓](solve/mo_algorithm/3636.cpp) [3636. Threshold Majority Queries](https://leetcode.com/problems/threshold-majority-queries/) | 2451 |
|  | [✓](solve/combine_algorithms/3655.cpp) [3655. XOR After Range Multiplication Queries II](https://leetcode.com/problems/xor-after-range-multiplication-queries-ii/) | 2454 |
|  | [1714. Sum Of Special Evenly-Spaced Elements In Array](https://leetcode.com/problems/sum-of-special-evenly-spaced-elements-in-array/) (🔒) |  |

Not on LeetCode: [Divide & Conquer - SRQ](https://usaco.guide/plat/DC-SRQ).

#### Trees

| Module | Problem | Rating |
|:--|:--|--:|
| [Binary Jumping](https://usaco.guide/plat/binary-jump) | [✓](solve/binary_lifting/2509.cpp) [2509. Cycle Length Queries in a Tree](https://leetcode.com/problems/cycle-length-queries-in-a-tree/) | 1948 |
|  | [✓](solve/binary_lifting/1483.cpp) [1483. Kth Ancestor of a Tree Node](https://leetcode.com/problems/kth-ancestor-of-a-tree-node/) | 2115 |
|  | [✓](solve/binary_lifting/3559.cpp) [3559. Number of Ways to Assign Edge Weights II](https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-ii/) | 2146 |
|  | [3553. Minimum Weighted Subgraph With the Required Paths II](https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths-ii/) | 2411 |
|  | [3585. Find Weighted Median Node in Tree](https://leetcode.com/problems/find-weighted-median-node-in-tree/) | 2429 |
|  | [3534. Path Existence Queries in a Graph II](https://leetcode.com/problems/path-existence-queries-in-a-graph-ii/) | 2507 |
|  | [✓](solve/binary_lifting/2846.cpp) [2846. Minimum Edge Weight Equilibrium Queries in a Tree](https://leetcode.com/problems/minimum-edge-weight-equilibrium-queries-in-a-tree/) | 2508 |
|  | [✓](solve/binary_lifting/2836.cpp) [2836. Maximize Value of Function in a Ball Passing Game](https://leetcode.com/problems/maximize-value-of-function-in-a-ball-passing-game/) | 2769 |
| [Small-To-Large Merging](https://usaco.guide/plat/merging) | [✓](solve/euler_tour/2003.cpp) [2003. Smallest Missing Genetic Value in Each Subtree](https://leetcode.com/problems/smallest-missing-genetic-value-in-each-subtree/) | 2415 |
|  | [3590. Kth Smallest Path XOR Sum](https://leetcode.com/problems/kth-smallest-path-xor-sum/) | 2646 |
| [Heavy-Light Decomposition](https://usaco.guide/plat/hld) | [3515. Shortest Path in a Weighted Tree](https://leetcode.com/problems/shortest-path-in-a-weighted-tree/) | 2312 |
|  | [3841. Palindromic Path Queries in a Tree](https://leetcode.com/problems/palindromic-path-queries-in-a-tree/) | 2384 |
| [Centroid Decomposition](https://usaco.guide/plat/centroid) | [2867. Count Valid Paths in a Tree](https://leetcode.com/problems/count-valid-paths-in-a-tree/): also has a simpler DSU solution | 2428 |
| [Kruskal Reconstruction Tree](https://usaco.guide/plat/kruskal-tree) | [2503. Maximum Number of Points From Grid Queries](https://leetcode.com/problems/maximum-number-of-points-from-grid-queries/) | 2196 |
|  | [1697. Checking Existence of Edge Length Limited Paths](https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths/) | 2300 |
|  | [1724. Checking Existence of Edge Length Limited Paths II](https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths-ii/) (🔒) |  |

Not on LeetCode: [Virtual Tree](https://usaco.guide/plat/VT).

#### Geometry

| Module | Problem | Rating |
|:--|:--|--:|
| [Geometry Primitives](https://usaco.guide/plat/geo-pri) | [149. Max Points on a Line](https://leetcode.com/problems/max-points-on-a-line/) |  |
|  | [1610. Maximum Number of Visible Points](https://leetcode.com/problems/maximum-number-of-visible-points/) | 2147 |
|  | [1453. Maximum Number of Darts Inside of a Circular Dartboard](https://leetcode.com/problems/maximum-number-of-darts-inside-of-a-circular-dartboard/) | 2202 |
|  | [3235. Check if the Rectangle Corner Is Reachable](https://leetcode.com/problems/check-if-the-rectangle-corner-is-reachable/) |  |
|  | [3625. Count Number of Trapezoids II](https://leetcode.com/problems/count-number-of-trapezoids-ii/) | 2643 |
| [Sweep Line](https://usaco.guide/plat/sweep-line) | [1584. Min Cost to Connect All Points](https://leetcode.com/problems/min-cost-to-connect-all-points/) (Medium): Manhattan MST | 1858 |
|  | [218. The Skyline Problem](https://leetcode.com/problems/the-skyline-problem/) |  |
|  | [2613. Beautiful Pairs](https://leetcode.com/problems/beautiful-pairs/) (🔒): closest pair |  |
|  | [3009. Maximum Number of Intersections on the Chart](https://leetcode.com/problems/maximum-number-of-intersections-on-the-chart/) (🔒) |  |
| [Convex Hull](https://usaco.guide/plat/convex-hull) | [587. Erect the Fence](https://leetcode.com/problems/erect-the-fence/) |  |
| [Convex Hull Trick](https://usaco.guide/plat/convex-hull-trick) | [3500. Minimum Cost to Divide Array Into Subarrays](https://leetcode.com/problems/minimum-cost-to-divide-array-into-subarrays/) | 2569 |

#### Misc. Topics

| Module | Problem | Rating |
|:--|:--|--:|
| [Inclusion-Exclusion Principle](https://usaco.guide/plat/PIE) | [878. Nth Magical Number](https://leetcode.com/problems/nth-magical-number/) | 1897 |
|  | [2513. Minimize the Maximum of Two Arrays](https://leetcode.com/problems/minimize-the-maximum-of-two-arrays/) (Medium) | 2302 |
|  | [3116. Kth Smallest Amount With Single Denomination Combination](https://leetcode.com/problems/kth-smallest-amount-with-single-denomination-combination/) | 2388 |
|  | [3312. Sorted GCD Pair Queries](https://leetcode.com/problems/sorted-gcd-pair-queries/) | 2533 |
| [Matrix Exponentiation](https://usaco.guide/plat/matrix-expo) | [3337. Total Characters in String After Transformations II](https://leetcode.com/problems/total-characters-in-string-after-transformations-ii/) | 2412 |
|  | [3700. Number of ZigZag Arrays II](https://leetcode.com/problems/number-of-zigzag-arrays-ii/) | 2435 |
|  | [2851. String Transformation](https://leetcode.com/problems/string-transformation/) | 2858 |
| [Bitsets](https://usaco.guide/plat/bitsets) | [1981. Minimize the Difference Between Target and Chosen Elements](https://leetcode.com/problems/minimize-the-difference-between-target-and-chosen-elements/) (Medium) | 2010 |
|  | [3489. Zero Array Transformation IV](https://leetcode.com/problems/zero-array-transformation-iv/) (Medium) | 2068 |
|  | [3181. Maximum Total Reward Using Operations II](https://leetcode.com/problems/maximum-total-reward-using-operations-ii/) | 2688 |
| [Divide & Conquer - DP](https://usaco.guide/plat/DC-DP) | [✓](solve/zsolutions/410.cpp) [410. Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/) |  |
|  | [1478. Allocate Mailboxes](https://leetcode.com/problems/allocate-mailboxes/): the optimization is optional at this size | 2190 |
| [Sum over Subsets DP](https://usaco.guide/plat/dp-sos) | [982. Triples with Bitwise AND Equal To Zero](https://leetcode.com/problems/triples-with-bitwise-and-equal-to-zero/) | 2085 |
|  | [1178. Number of Valid Words for Each Puzzle](https://leetcode.com/problems/number-of-valid-words-for-each-puzzle/) | 2234 |
|  | [3670. Maximum Product of Two Integers With No Common Bits](https://leetcode.com/problems/maximum-product-of-two-integers-with-no-common-bits/) (Medium) | 2234 |

### Advanced

#### Data Structures

| Module | Problem | Rating |
|:--|:--|--:|
| [Max Suffix Query with Insertions Only](https://usaco.guide/adv/springboards) | [2926. Maximum Balanced Subsequence Sum](https://leetcode.com/problems/maximum-balanced-subsequence-sum/) | 2448 |
|  | [2736. Maximum Sum Queries](https://leetcode.com/problems/maximum-sum-queries/) | 2533 |
| [Wavelet Tree](https://usaco.guide/adv/wavelet) | [3762. Minimum Operations to Equalize Subarrays](https://leetcode.com/problems/minimum-operations-to-equalize-subarrays/) | 2497 |
| [Counting Minimums with Segment Tree](https://usaco.guide/adv/count-min) | [850. Rectangle Area II](https://leetcode.com/problems/rectangle-area-ii/) | 2236 |
|  | [3454. Separate Squares II](https://leetcode.com/problems/separate-squares-ii/) | 2671 |
| [Persistent Data Structures](https://usaco.guide/adv/persistent) | [1146. Snapshot Array](https://leetcode.com/problems/snapshot-array/) (Medium) | 1771 |
|  | [3762. Minimum Operations to Equalize Subarrays](https://leetcode.com/problems/minimum-operations-to-equalize-subarrays/): again, with a persistent segment tree | 2497 |
| [Treaps](https://usaco.guide/adv/treaps) | [480. Sliding Window Median](https://leetcode.com/problems/sliding-window-median/) |  |
|  | [2296. Design a Text Editor](https://leetcode.com/problems/design-a-text-editor/) | 1912 |
|  | [1825. Finding MK Average](https://leetcode.com/problems/finding-mk-average/) | 2396 |
|  | [1756. Design Most Recently Used Queue](https://leetcode.com/problems/design-most-recently-used-queue/) (Medium, 🔒) |  |

Not on LeetCode: [Segment Tree Beats](https://usaco.guide/adv/segtree-beats).

#### Convexity

| Module | Problem | Rating |
|:--|:--|--:|
| [Lagrangian Relaxation](https://usaco.guide/adv/lagrange) | [188. Best Time to Buy and Sell Stock IV](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/) |  |
| [Slope Trick](https://usaco.guide/adv/slope-trick) | [2263. Make Array Non-decreasing or Non-increasing](https://leetcode.com/problems/make-array-non-decreasing-or-non-increasing/) (🔒) |  |

Not on LeetCode: [LineContainer](https://usaco.guide/adv/line-container).

#### Graphs

| Module | Problem | Rating |
|:--|:--|--:|
| [Shortest Paths with Negative Edge Weights](https://usaco.guide/adv/sp-neg) | [787. Cheapest Flights Within K Stops](https://leetcode.com/problems/cheapest-flights-within-k-stops/) (Medium): Bellman–Ford; LeetCode has no negative weights | 1786 |
| [Eulerian Tours](https://usaco.guide/adv/eulerian-tours) | [✓](solve/eulerian_path/hierholzer_algorithm/directed/332.cpp) [332. Reconstruct Itinerary](https://leetcode.com/problems/reconstruct-itinerary/) |  |
|  | [✓](solve/eulerian_path/de_bruijn_sequence/753.cpp) [753. Cracking the Safe](https://leetcode.com/problems/cracking-the-safe/) | 2274 |
|  | [✓](solve/eulerian_path/hierholzer_algorithm/2097.cpp) [2097. Valid Arrangement of Pairs](https://leetcode.com/problems/valid-arrangement-of-pairs/) | 2651 |
| [BCCs and 2CCs](https://usaco.guide/adv/BCC-2CC) | [1192. Critical Connections in a Network](https://leetcode.com/problems/critical-connections-in-a-network/) | 2085 |
|  | [1568. Minimum Number of Days to Disconnect Island](https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/) | 2209 |
| [Strongly Connected Components](https://usaco.guide/adv/SCC) | [✓](solve/kosaraju/2360.cpp) [2360. Longest Cycle in a Graph](https://leetcode.com/problems/longest-cycle-in-a-graph/) | 1897 |
|  | [2876. Count Visited Nodes in a Directed Graph](https://leetcode.com/problems/count-visited-nodes-in-a-directed-graph/) | 2210 |
|  | [2127. Maximum Employees to Be Invited to a Meeting](https://leetcode.com/problems/maximum-employees-to-be-invited-to-a-meeting/) | 2449 |
| [Offline Deletion](https://usaco.guide/adv/offline-del) | [✓](solve/dsu_rollback/684.cpp) [684. Redundant Connection](https://leetcode.com/problems/redundant-connection/) (Medium): with DSU rollback |  |
|  | [2382. Maximum Segment Sum After Removals](https://leetcode.com/problems/maximum-segment-sum-after-removals/) | 2136 |
|  | [1938. Maximum Genetic Difference Query](https://leetcode.com/problems/maximum-genetic-difference-query/) | 2503 |
|  | [803. Bricks Falling When Hit](https://leetcode.com/problems/bricks-falling-when-hit/) | 2765 |
| [Euler's Formula](https://usaco.guide/adv/eulers-formula) | [959. Regions Cut By Slashes](https://leetcode.com/problems/regions-cut-by-slashes/) (Medium) | 2136 |

Not on LeetCode: [Critical (dominators)](https://usaco.guide/adv/critical), [Link Cut Tree](https://usaco.guide/adv/link-cut-tree).

#### Dynamic Programming

| Module | Problem | Rating |
|:--|:--|--:|
| [DP on Trees - Combining Subtrees](https://usaco.guide/adv/comb-sub) | [3562. Maximum Profit from Trading Stocks with Discounts](https://leetcode.com/problems/maximum-profit-from-trading-stocks-with-discounts/) | 2458 |
| [DP on Broken Profile](https://usaco.guide/adv/dp-broken-profile) | [1411. Number of Ways to Paint N × 3 Grid](https://leetcode.com/problems/number-of-ways-to-paint-n-3-grid/) | 1845 |
|  | [1931. Painting a Grid With Three Different Colors](https://leetcode.com/problems/painting-a-grid-with-three-different-colors/) | 2170 |
|  | [1659. Maximize Grid Happiness](https://leetcode.com/problems/maximize-grid-happiness/) | 2655 |
| [Additional DP Optimizations and Techniques](https://usaco.guide/adv/dp-more) | [1547. Minimum Cost to Cut a Stick](https://leetcode.com/problems/minimum-cost-to-cut-a-stick/) | 2116 |
|  | [1000. Minimum Cost to Merge Stones](https://leetcode.com/problems/minimum-cost-to-merge-stones/) | 2423 |

#### Flows

| Module | Problem | Rating |
|:--|:--|--:|
| [Maximum Flow](https://usaco.guide/adv/max-flow) | [1820. Maximum Number of Accepted Invitations](https://leetcode.com/problems/maximum-number-of-accepted-invitations/) (Medium, 🔒) |  |
|  | [1349. Maximum Students Taking Exam](https://leetcode.com/problems/maximum-students-taking-exam/) | 2386 |
| [Minimum Cut](https://usaco.guide/adv/min-cut) | [2123. Minimum Operations to Remove Adjacent Ones in Matrix](https://leetcode.com/problems/minimum-operations-to-remove-adjacent-ones-in-matrix/) (🔒) |  |
| [Minimum Cost Flow](https://usaco.guide/adv/min-cost-flow) | [1879. Minimum XOR Sum of Two Arrays](https://leetcode.com/problems/minimum-xor-sum-of-two-arrays/) | 2145 |
|  | [2172. Maximum AND Sum of Array](https://leetcode.com/problems/maximum-and-sum-of-array/) | 2392 |
|  | [3276. Select Cells in Grid With Maximum Score](https://leetcode.com/problems/select-cells-in-grid-with-maximum-score/) | 2403 |
|  | [1595. Minimum Cost to Connect Two Groups of Points](https://leetcode.com/problems/minimum-cost-to-connect-two-groups-of-points/) | 2538 |

Not on LeetCode: [Flow with Lower Bounds](https://usaco.guide/adv/flow-lb).

#### Polynomials

Not on LeetCode: [Introduction to Fast Fourier Transform](https://usaco.guide/adv/fft), [More Complex Operations Using FFT](https://usaco.guide/adv/fft-ext).

#### Strings

| Module | Problem | Rating |
|:--|:--|--:|
| [String Searching](https://usaco.guide/adv/string-search) | [3213. Construct String with Minimum Cost](https://leetcode.com/problems/construct-string-with-minimum-cost/) | 2171 |
|  | [2223. Sum of Scores of Built Strings](https://leetcode.com/problems/sum-of-scores-of-built-strings/) | 2220 |
|  | [3045. Count Prefix and Suffix Pairs II](https://leetcode.com/problems/count-prefix-and-suffix-pairs-ii/) | 2328 |
|  | [3303. Find the Occurrence of First Almost Equal Substring](https://leetcode.com/problems/find-the-occurrence-of-first-almost-equal-substring/) | 2509 |
|  | [3292. Minimum Number of Valid Strings to Form Target II](https://leetcode.com/problems/minimum-number-of-valid-strings-to-form-target-ii/) | 2662 |
|  | [1397. Find All Good Strings](https://leetcode.com/problems/find-all-good-strings/) | 2667 |
|  | [1960. Maximum Product of the Length of Two Palindromic Substrings](https://leetcode.com/problems/maximum-product-of-the-length-of-two-palindromic-substrings/) | 2691 |
| [Suffix Array](https://usaco.guide/adv/suffix-array) | [3934. Smallest Unique Subarray](https://leetcode.com/problems/smallest-unique-subarray/) | 2163 |
|  | [1044. Longest Duplicate Substring](https://leetcode.com/problems/longest-duplicate-substring/) | 2429 |
|  | [1923. Longest Common Subpath](https://leetcode.com/problems/longest-common-subpath/) | 2661 |
| [String Suffix Structures](https://usaco.guide/adv/string-suffix) | [1698. Number of Distinct Substrings in a String](https://leetcode.com/problems/number-of-distinct-substrings-in-a-string/) (Medium, 🔒) |  |

#### Misc. Topics

| Module | Problem | Rating |
|:--|:--|--:|
| [Extended Euclidean Algorithm](https://usaco.guide/adv/extend-euclid) | [365. Water and Jug Problem](https://leetcode.com/problems/water-and-jug-problem/) (Medium) |  |
|  | [780. Reaching Points](https://leetcode.com/problems/reaching-points/) | 1897 |
|  | [1250. Check If It Is a Good Array](https://leetcode.com/problems/check-if-it-is-a-good-array/) | 1983 |
|  | [2543. Check if Point Is Reachable](https://leetcode.com/problems/check-if-point-is-reachable/) | 2221 |
| [Catalan Numbers](https://usaco.guide/adv/catalan) | [96. Unique Binary Search Trees](https://leetcode.com/problems/unique-binary-search-trees/) (Medium) |  |
|  | [1259. Handshakes That Don't Cross](https://leetcode.com/problems/handshakes-that-dont-cross/) (🔒) | 1951 |
| [XOR Basis](https://usaco.guide/adv/xor-basis) | [3681. Maximum XOR of Subsequences](https://leetcode.com/problems/maximum-xor-of-subsequences/) | 2027 |
|  | [3630. Partition Array for Maximum XOR and AND](https://leetcode.com/problems/partition-array-for-maximum-xor-and-and/) | 2744 |
| [Fracturing Search](https://usaco.guide/adv/fracturing-search) | [1439. Find the Kth Smallest Sum of a Matrix With Sorted Rows](https://leetcode.com/problems/find-the-kth-smallest-sum-of-a-matrix-with-sorted-rows/) | 2134 |
|  | [✓](solve/3691.cpp) [3691. Maximum Total Subarray Value II](https://leetcode.com/problems/maximum-total-subarray-value-ii/) | 2469 |
|  | [2386. Find the K-Sum of an Array](https://leetcode.com/problems/find-the-k-sum-of-an-array/) | 2648 |
| [Game Theory](https://usaco.guide/adv/game-theory) | [294. Flip Game II](https://leetcode.com/problems/flip-game-ii/) (Medium, 🔒) |  |
|  | [810. Chalkboard XOR Game](https://leetcode.com/problems/chalkboard-xor-game/) | 2341 |
|  | [913. Cat and Mouse](https://leetcode.com/problems/cat-and-mouse/) | 2567 |
|  | [1728. Cat and Mouse II](https://leetcode.com/problems/cat-and-mouse-ii/) | 2849 |
|  | [2005. Subtree Removal Game with Fibonacci Tree](https://leetcode.com/problems/subtree-removal-game-with-fibonacci-tree/) (🔒) |  |
| [Matroids](https://usaco.guide/adv/matroid) | [630. Course Schedule III](https://leetcode.com/problems/course-schedule-iii/) |  |
|  | [1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/) | 2572 |
| [Randomness](https://usaco.guide/adv/random) | [1157. Online Majority Element In Subarray](https://leetcode.com/problems/online-majority-element-in-subarray/) | 2205 |
|  | [4033. Valid K-Unique Subarrays I](https://leetcode.com/problems/valid-k-unique-subarrays-i/) | 2314 |
| [Interactive and Communication Problems](https://usaco.guide/adv/interactive) | [✓](solve/binary_tree/297.cpp) [297. Serialize and Deserialize Binary Tree](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/): communication |  |
|  | [1095. Find in Mountain Array](https://leetcode.com/problems/find-in-mountain-array/) | 1827 |
|  | [1274. Number of Ships in a Rectangle](https://leetcode.com/problems/number-of-ships-in-a-rectangle/) (🔒) | 1997 |
|  | [843. Guess the Word](https://leetcode.com/problems/guess-the-word/) | 2078 |

Not on LeetCode: [Prefix Sums of Number-Theoretic Functions](https://usaco.guide/adv/prefix-sums-nt-1), [Matroid Intersection](https://usaco.guide/adv/matroid-isect), [Vectorization in C++](https://usaco.guide/adv/vectorization).
