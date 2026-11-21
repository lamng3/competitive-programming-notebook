# TODO: topics to study

A study list in C++: one stub per topic, to fill in.

The sections and the subfolders inside them are numbered in study order: each one leans on the ones before it.

To study a topic: read a write-up of the idea, fill in the stub in the notebook's style, add a test next to it (`cpunit <name>`), then move it into `notebook/` and tick it here.

9 of 456 have a C++ version in the notebook.

## Sections

1. [Numeric](#1-numeric) (15): Binary, ternary, and parallel binary search, fast powers. The tools every later section leans on.
2. [Data Structure](#2-data-structure) (86): Range queries first (Fenwick, sparse table, segment trees), then sqrt tricks, line containers, treaps, and the rest.
3. [Grid](#3-grid) (4): Grid moves, BFS, and Dijkstra: graph search on the most common input shape.
4. [Graph Theory](#4-graph-theory) (73): Shortest paths, spanning trees, connectivity, then trees (LCA, HLD, centroids), then special graphs.
5. [Dynamic Programming](#5-dynamic-programming) (10): Knapsack, then the optimizations: divide and conquer, Knuth, monotone queue, SMAWK, Lagrange.
6. [String](#6-string) (34): Hashing and tries, then prefix structures (suffix array, automata), then palindromes and Lyndon words.
7. [Number Theory](#7-number-theory) (32): Modular arithmetic, Euclid and CRT, factorization, then multiplicative prefix sums.
8. [Continued Fraction and Farey Sequence](#8-continued-fraction-and-farey-sequence) (2): Best rational approximations: a short follow-on to number theory.
9. [Combinatorial](#9-combinatorial) (57): Counting, LIS, permutations, then flows and matchings, matroids, and Young tableaux.
10. [Linear Algebra](#10-linear-algebra) (22): Matrices, Gaussian elimination (also over GF2), and linear recurrences.
11. [Power Series](#11-power-series) (26): FFT and NTT first; everything else in this section multiplies polynomials with them.
12. [Abstract Algebra](#12-abstract-algebra) (23): Groups, rings, and finite fields: the structures behind modular arithmetic and hashing.
13. [Geometry](#13-geometry) (37): Points and lines first, then polygons, circles, convex hulls, sweeps, and triangulations.
14. [Succinct Structures](#14-succinct-structures) (1): Bit-packed rank and select.
15. [Heuristic Algorithms](#15-heuristic-algorithms) (2): Simulated annealing and randomized search, for when nothing exact fits.
16. [Random Generators](#16-random-generators) (11): Random trees, graphs, and polygons, for stress-testing everything above.
17. [Miscellaneous](#17-miscellaneous) (20): Fast IO, big integers, bit tricks, and other utilities.
18. [Network Communication](#18-network-communication) (1): Communication problems, where two programs talk through a limited channel.

## 1. Numeric

Binary, ternary, and parallel binary search, fast powers. The tools every later section leans on.

- [ ] [Binary geometric sum](01_searching/binary_geometric_sum.h)
- [ ] [Binary geometric sum general](01_searching/binary_geometric_sum_general.h)
- [x] Binary power — ours: [`ModInv.h`](https://github.com/lamng3/competitive-programming-notebook/blob/main/notebook/math/modular_arithmetic/ModInv.h)
- [ ] [Binary power general](01_searching/binary_power_general.h)
- [ ] [Binary string](01_searching/binary_string.h)
- [ ] [Continuous binary search](01_searching/continuous_binary_search.h) (Python: [`BinarySearch.py`](https://github.com/lamng3/competitive-programming-notebook/blob/main/python/searching/binary_search/BinarySearch.py))
- [ ] [Counting iterator](01_searching/counting_iterator.h)
- [ ] [Discrete golden section search](01_searching/discrete_golden_section_search.h)
- [ ] [Discrete ternary search](01_searching/discrete_ternary_search.h)
- [ ] [Double parallel binary search](01_searching/double_parallel_binary_search.h)
- [ ] [Find prefix xor order](01_searching/find_prefix_xor_order.h)
- [ ] [Fractional search](01_searching/fractional_search.h)
- [ ] [Golden section search](01_searching/golden_section_search.h)
- [ ] [Parallel binary search](01_searching/parallel_binary_search.h)
- [ ] [Solve cubic equation](01_searching/solve_cubic_equation.h)

## 2. Data Structure

Range queries first (Fenwick, sparse table, segment trees), then sqrt tricks, line containers, treaps, and the rest.

### Fenwick Tree

- [x] Fenwick tree — ours: [`FenwickTree.h`](https://github.com/lamng3/competitive-programming-notebook/blob/main/notebook/data_structures/1d_range_query/FenwickTree.h)
- [ ] [Fenwick tree 2D sparse sum](02_data_structures/01_fenwick_tree/fenwick_tree_2d_sparse_sum.h)
- [ ] [Fenwick tree 2D sum](02_data_structures/01_fenwick_tree/fenwick_tree_2d_sum.h)
- [ ] [Fenwick tree 3D sum](02_data_structures/01_fenwick_tree/fenwick_tree_3d_sum.h)
- [ ] [Range add query sum solver](02_data_structures/01_fenwick_tree/range_add_query_sum_solver.h)
- [ ] [Range add query sum solver 2D](02_data_structures/01_fenwick_tree/range_add_query_sum_solver_2d.h)
- [ ] [Range xor query xor solver 2D](02_data_structures/01_fenwick_tree/range_xor_query_xor_solver_2d.h)

### Sparse Table

- [ ] [Range minmax query solver](02_data_structures/02_sparse_table/range_minmax_query_solver.h)
- [ ] [Sparse table](02_data_structures/02_sparse_table/sparse_table.h)
- [ ] [Sparse table 2D](02_data_structures/02_sparse_table/sparse_table_2d.h)
- [ ] [Sparse table 2D square](02_data_structures/02_sparse_table/sparse_table_2d_square.h)

### Disjoint Sparse Table

- [ ] [Disjoint sparse table](02_data_structures/03_disjoint_sparse_table/disjoint_sparse_table.h)

### Segment Tree

- [ ] [Mergesort tree](02_data_structures/04_segment_tree/mergesort_tree.h)
- [ ] [Mergesort tree point update](02_data_structures/04_segment_tree/mergesort_tree_point_update.h)
- [x] Segment tree — ours: [`SegmentTree.h`](https://github.com/lamng3/competitive-programming-notebook/blob/main/notebook/data_structures/1d_range_query/SegmentTree.h)
- [ ] [Segment tree 2D](02_data_structures/04_segment_tree/segment_tree_2d.h)
- [ ] [Segment tree 2D sparse](02_data_structures/04_segment_tree/segment_tree_2d_sparse.h)
- [ ] [Segment tree 3D](02_data_structures/04_segment_tree/segment_tree_3d.h)
- [x] Segment tree dynamic — ours: [`SparseSegmentTree.h`](https://github.com/lamng3/competitive-programming-notebook/blob/main/notebook/data_structures/rurq/SparseSegmentTree.h)
- [x] Segment tree persistent — ours: [`PersistentSegmentTree.h`](https://github.com/lamng3/competitive-programming-notebook/blob/main/notebook/data_structures/rurq/PersistentSegmentTree.h)
- [ ] [Segment tree wide](02_data_structures/04_segment_tree/segment_tree_wide.h)

### Disjoint Set

- [x] Disjoint set — ours: [`DSU.h`](https://github.com/lamng3/competitive-programming-notebook/blob/main/notebook/graphs/dsu/DSU.h)
- [ ] [Disjoint set 2D](02_data_structures/05_disjoint_set/disjoint_set_2d.h)
- [x] Disjoint set rollback — ours: [`DSURollback.h`](https://github.com/lamng3/competitive-programming-notebook/blob/main/notebook/graphs/dsu/DSURollback.h)
- [ ] [Persistent disjoint set](02_data_structures/05_disjoint_set/persistent_disjoint_set.h)

### Sliding Window Aggregation

- [ ] [SWAG deque](02_data_structures/06_sliding_window_aggregation/swag_deque.h)
- [ ] [SWAG queue](02_data_structures/06_sliding_window_aggregation/swag_queue.h)

### Sqrt Decomposition

- [ ] [Mo 2D](02_data_structures/07_sqrt_decomposition/mo_2d.h)
- [ ] [Mo 2D hilbert curve ordering](02_data_structures/07_sqrt_decomposition/mo_2d_hilbert_curve_ordering.h)
- [ ] [Mo 2D rectilinear spanning tree ordering](02_data_structures/07_sqrt_decomposition/mo_2d_rectilinear_spanning_tree_ordering.h)
- [ ] [Mo 2D rollback](02_data_structures/07_sqrt_decomposition/mo_2d_rollback.h)
- [ ] [Mo 3D](02_data_structures/07_sqrt_decomposition/mo_3d.h)
- [ ] [Mo sweepline](02_data_structures/07_sqrt_decomposition/mo_sweepline.h)
- [ ] [Sqrt decomposition heavy point update light range query commutative group](02_data_structures/07_sqrt_decomposition/sqrt_decomposition_heavy_point_update_light_range_query_commutative_group.h)
- [ ] [Sqrt decomposition light point update heavy range query commutative monoid](02_data_structures/07_sqrt_decomposition/sqrt_decomposition_light_point_update_heavy_range_query_commutative_monoid.h)
- [ ] [Sqrt decomposition light range update heavy point query commutative group](02_data_structures/07_sqrt_decomposition/sqrt_decomposition_light_range_update_heavy_point_query_commutative_group.h)

### Static Range Query Processor

- [ ] [Static range query processor](02_data_structures/08_static_range_query_processor/static_range_query_processor.h)
- [ ] [Static range query processor 2D](02_data_structures/08_static_range_query_processor/static_range_query_processor_2d.h)
- [ ] [Static range query processor 3D](02_data_structures/08_static_range_query_processor/static_range_query_processor_3d.h)

### Heap

- [ ] [Skew heap](02_data_structures/09_heap/skew_heap.h)

### Priority Queue

- [ ] [Partially retroactive priority queue](02_data_structures/10_priority_queue/partially_retroactive_priority_queue.h)
- [ ] [Priority queue with update](02_data_structures/10_priority_queue/priority_queue_with_update.h)

### Treap

- [ ] [Treap](02_data_structures/11_treap/treap.h)

### Cartesian Tree

- [ ] [Cartesian tree](02_data_structures/12_cartesian_tree/cartesian_tree.h)

### Trie

- [ ] [Binary trie dynamic](02_data_structures/13_trie/binary_trie_dynamic.h)

### Line Container

- [ ] [Kinetic tournament](02_data_structures/14_line_container/kinetic_tournament.h)
- [ ] [Li chao tree](02_data_structures/14_line_container/li_chao_tree.h)
- [ ] [Li chao tree fixed query](02_data_structures/14_line_container/li_chao_tree_fixed_query.h)
- [ ] [Li chao tree order statistic](02_data_structures/14_line_container/li_chao_tree_order_statistic.h)
- [ ] [Line container](02_data_structures/14_line_container/line_container.h)
- [ ] [Piecewise linear function container](02_data_structures/14_line_container/piecewise_linear_function_container.h)
- [ ] [Piecewise linear function container with skew heap](02_data_structures/14_line_container/piecewise_linear_function_container_with_skew_heap.h)
- [ ] [Sorted line container](02_data_structures/14_line_container/sorted_line_container.h)

### Interval Processor

- [ ] [Colorful interval set](02_data_structures/15_interval_processor/colorful_interval_set.h)
- [ ] [Interval set](02_data_structures/15_interval_processor/interval_set.h)

### Integral Set

- [ ] [Integral map](02_data_structures/16_integral_set/integral_map.h)
- [ ] [Integral multiset](02_data_structures/16_integral_set/integral_multiset.h)

### Persistent Array

- [ ] [Persistent array](02_data_structures/17_persistent_array/persistent_array.h)

### Potential Tracker

- [ ] [Potential tracker](02_data_structures/18_potential_tracker/potential_tracker.h)

### Wavelet Structures

- [ ] [Wavelet matrix](02_data_structures/19_wavelet_structures/wavelet_matrix.h)
- [ ] [Wavelet tree](02_data_structures/19_wavelet_structures/wavelet_tree.h)

### Kd Tree

- [ ] [K-d tree minmax](02_data_structures/20_kd_tree/kdtree_minmax.h)

### Multidimentional Array

- [ ] [K-d array](02_data_structures/21_multidimentional_array/kdarray.h)
- [ ] [K-d sum](02_data_structures/21_multidimentional_array/kdsum.h)

### Range MEX Query Solver

- [ ] [Range MEX query solver offline](02_data_structures/22_range_mex_query_solver/range_mex_query_solver_offline.h)
- [ ] [Range MEX query solver online](02_data_structures/22_range_mex_query_solver/range_mex_query_solver_online.h)

### Range Mode Query

- [ ] [Range mode query solver online](02_data_structures/23_range_mode_query/range_mode_query_solver_online.h)

### Range Inversion Query Solver

- [ ] [Range inversion query solver offline](02_data_structures/24_range_inversion_query_solver/range_inversion_query_solver_offline.h)

### Distinct Value Query solver

- [ ] [Distinct value count query solve online cubic root](02_data_structures/25_distinct_value_query_solver/distinct_value_count_query_solve_online_cubic_root.h)
- [ ] [Distinct value query solver offline](02_data_structures/25_distinct_value_query_solver/distinct_value_query_solver_offline.h)
- [ ] [Distinct value query solver online](02_data_structures/25_distinct_value_query_solver/distinct_value_query_solver_online.h)

### Value Range Query Solver

- [ ] [Value range query solver online sqrt](02_data_structures/26_value_range_query_solver/value_range_query_solver_online_sqrt.h)

### Value Trackers

- [ ] [Range choose sum tracker](02_data_structures/27_value_trackers/range_choose_sum_tracker.h)
- [ ] [Sorted range sum tracker](02_data_structures/27_value_trackers/sorted_range_sum_tracker.h)

### Sequence Update Processor

- [ ] [Arithmetic sequence update processor](02_data_structures/28_sequence_update_processor/arithmetic_sequence_update_processor.h)
- [ ] [Polynomial sequence update processor](02_data_structures/28_sequence_update_processor/polynomial_sequence_update_processor.h)

### Data Structure Enhancer

- [ ] [Data structure deletion enabler offline](02_data_structures/29_data_structure_enhancer/data_structure_deletion_enabler_offline.h)
- [ ] [Data structure insertion enabler online](02_data_structures/29_data_structure_enhancer/data_structure_insertion_enabler_online.h)
- [ ] [Data structure multidimensional priority queue like deletion enabler online](02_data_structures/29_data_structure_enhancer/data_structure_multidimensional_priority_queue_like_deletion_enabler_online.h)
- [ ] [Data structure priority queue like deletion enabler online](02_data_structures/29_data_structure_enhancer/data_structure_priority_queue_like_deletion_enabler_online.h)
- [ ] [Data structure queue like deletion enabler online](02_data_structures/29_data_structure_enhancer/data_structure_queue_like_deletion_enabler_online.h)

### Unital Sorter

- [ ] [Unital sorter](02_data_structures/30_unital_sorter/unital_sorter.h)

### Link Cut Trees

- [ ] [Link cut trees](02_data_structures/31_link_cut_trees/link_cut_trees.h)

### Cut Join Tree

- [ ] [Cut join tree](02_data_structures/32_cut_join_tree/cut_join_tree.h)

### Top Tree

- [ ] [Static top tree](02_data_structures/33_top_tree/static_top_tree.h)

### PQ Tree

- [ ] [PQ tree](02_data_structures/34_pq_tree/pq_tree.h)

## 3. Grid

Grid moves, BFS, and Dijkstra: graph search on the most common input shape.

- [ ] [Direction vectors](03_grid/direction_vectors.h)
- [ ] [Grid BFS forest](03_grid/grid_bfs_forest.h)
- [ ] [Grid dijkstra](03_grid/grid_dijkstra.h)
- [ ] [Grid path](03_grid/grid_path.h)

## 4. Graph Theory

Shortest paths, spanning trees, connectivity, then trees (LCA, HLD, centroids), then special graphs.

- [ ] [Edge path into vertex path](04_graphs/edge_path_into_vertex_path.h)
- [ ] [Find all cycle masks](04_graphs/find_all_cycle_masks.h)
- [ ] [Graph](04_graphs/graph.h)

### Shortest Path Algorithms

- [ ] [Successive shortest path solver](04_graphs/01_shortest_path_algorithms/successive_shortest_path_solver.h)

### Shortest Path Algorithms / Bellman Ford

- [ ] [Bellman ford](04_graphs/01_shortest_path_algorithms/bellman_ford/bellman_ford.h)

### Shortest Path Algorithms / Dial

- [ ] [Dial](04_graphs/01_shortest_path_algorithms/dial/dial.h)

### Shortest Path Algorithms / Dijkstra

- [ ] [Dijkstra](04_graphs/01_shortest_path_algorithms/dijkstra/dijkstra.h) (Python: [`Dijkstra.py`](https://github.com/lamng3/competitive-programming-notebook/blob/main/python/graphs/shortest_path/Dijkstra.py))
- [ ] [Dijkstra dense](04_graphs/01_shortest_path_algorithms/dijkstra/dijkstra_dense.h)

### Shortest Path Algorithms / Floyd Warshall

- [ ] [Floyd warshall](04_graphs/01_shortest_path_algorithms/floyd_warshall/floyd_warshall.h)

### Shortest Path Algorithms / Minimum Mean Weight Cycle

- [ ] [Minimum mean weight cycle](04_graphs/01_shortest_path_algorithms/minimum_mean_weight_cycle/minimum_mean_weight_cycle.h)

### Shortest Path Algorithms / Shortest Path Faster Algorithm

- [ ] [SPFA](04_graphs/01_shortest_path_algorithms/shortest_path_faster_algorithm/spfa.h)

### Spanning Forest Algorithms

- [ ] [BFS forest](04_graphs/02_spanning_forest_algorithms/bfs_forest.h)
- [ ] [Complement spanning forest](04_graphs/02_spanning_forest_algorithms/complement_spanning_forest.h)
- [ ] [Count spanning forest](04_graphs/02_spanning_forest_algorithms/count_spanning_forest.h)
- [ ] [DFS forest](04_graphs/02_spanning_forest_algorithms/dfs_forest.h)
- [ ] [Lexicographical BFS forest](04_graphs/02_spanning_forest_algorithms/lexicographical_bfs_forest.h)
- [ ] [Minimum spanning arborescence](04_graphs/02_spanning_forest_algorithms/minimum_spanning_arborescence.h)
- [ ] [Minimum spanning forest](04_graphs/02_spanning_forest_algorithms/minimum_spanning_forest.h)
- [ ] [Minimum steiner tree](04_graphs/02_spanning_forest_algorithms/minimum_steiner_tree.h)

### DFS Based

- [ ] [Find dominators](04_graphs/03_dfs_based/find_dominators.h)
- [ ] [Greedy coloring](04_graphs/03_dfs_based/greedy_coloring.h)
- [ ] [Reachable even cycle finder](04_graphs/03_dfs_based/reachable_even_cycle_finder.h)
- [ ] [Topological sorter](04_graphs/03_dfs_based/topological_sorter.h) (Python: [`TopoSort.py`](https://github.com/lamng3/competitive-programming-notebook/blob/main/python/graphs/topological_sort/TopoSort.py))

### Connectivity

- [ ] [Biconnected components](04_graphs/04_connectivity/biconnected_components.h)
- [ ] [Bipolar orientation](04_graphs/04_connectivity/bipolar_orientation.h)
- [ ] [Ear decomposition](04_graphs/04_connectivity/ear_decomposition.h)
- [ ] [Recover two sat](04_graphs/04_connectivity/recover_two_sat.h)
- [ ] [Strong augmentation](04_graphs/04_connectivity/strong_augmentation.h)
- [ ] [Strongly connected components](04_graphs/04_connectivity/strongly_connected_components.h)
- [ ] [Strongly connected components offline incremental](04_graphs/04_connectivity/strongly_connected_components_offline_incremental.h)
- [ ] [Two sat solver](04_graphs/04_connectivity/two_sat_solver.h)

### Euler Walk

- [ ] [Euler walk](04_graphs/05_euler_walk/euler_walk.h)

### Forest Algorithms

- [ ] [Almost uniformly partitionable](04_graphs/06_forest_algorithms/almost_uniformly_partitionable.h)
- [ ] [Binary lifting](04_graphs/06_forest_algorithms/binary_lifting.h)
- [ ] [Centroid decomposition](04_graphs/06_forest_algorithms/centroid_decomposition.h)
- [ ] [Centroid processor](04_graphs/06_forest_algorithms/centroid_processor.h)
- [ ] [Compressed tree](04_graphs/06_forest_algorithms/compressed_tree.h)
- [ ] [Forest path query solver commutative group](04_graphs/06_forest_algorithms/forest_path_query_solver_commutative_group.h)
- [ ] [Forest query solver](04_graphs/06_forest_algorithms/forest_query_solver.h)
- [ ] [Heavy light decomposition](04_graphs/06_forest_algorithms/heavy_light_decomposition.h)
- [ ] [LCA solver](04_graphs/06_forest_algorithms/lca_solver.h)
- [ ] [LCA solver offline](04_graphs/06_forest_algorithms/lca_solver_offline.h)
- [ ] [Precalc directional heights](04_graphs/06_forest_algorithms/precalc_directional_heights.h)
- [ ] [Prufer code](04_graphs/06_forest_algorithms/prufer_code.h)
- [ ] [Rerooter](04_graphs/06_forest_algorithms/rerooter.h)
- [ ] [Shallowest decomposition](04_graphs/06_forest_algorithms/shallowest_decomposition.h)
- [ ] [Skew binary lifting](04_graphs/06_forest_algorithms/skew_binary_lifting.h)
- [ ] [Small to large on forest](04_graphs/06_forest_algorithms/small_to_large_on_forest.h)
- [ ] [Static path minmax processor](04_graphs/06_forest_algorithms/static_path_minmax_processor.h)
- [ ] [Tree hasher](04_graphs/06_forest_algorithms/tree_hasher.h)
- [ ] [Weighted binary lifting](04_graphs/06_forest_algorithms/weighted_binary_lifting.h)

### Clique

- [ ] [Count cliques](04_graphs/07_clique/count_cliques.h)
- [ ] [Count cliques weighted](04_graphs/07_clique/count_cliques_weighted.h)
- [ ] [Enumerate maximal cliques](04_graphs/07_clique/enumerate_maximal_cliques.h)
- [ ] [Enumerate maximal cliques large](04_graphs/07_clique/enumerate_maximal_cliques_large.h)
- [ ] [Find a maximum clique](04_graphs/07_clique/find_a_maximum_clique.h)
- [ ] [Find a maximum clique large](04_graphs/07_clique/find_a_maximum_clique_large.h)

### Sqrt Trick

- [ ] [Count 4 cycles](04_graphs/08_sqrt_trick/count_4_cycles.h)
- [ ] [Find 3 cycles](04_graphs/08_sqrt_trick/find_3_cycles.h)
- [ ] [Find 4 cycles](04_graphs/08_sqrt_trick/find_4_cycles.h)

### Special Graphs

- [ ] [Admissible graph](04_graphs/09_special_graphs/admissible_graph.h)
- [ ] [Find maximal cycles in tournament graphs](04_graphs/09_special_graphs/find_maximal_cycles_in_tournament_graphs.h)
- [ ] [Functional graph processor](04_graphs/09_special_graphs/functional_graph_processor.h)
- [ ] [Maximum independent set on cactus](04_graphs/09_special_graphs/maximum_independent_set_on_cactus.h)
- [ ] [Recognize chordal graphs](04_graphs/09_special_graphs/recognize_chordal_graphs.h)
- [ ] [Recognize cographs](04_graphs/09_special_graphs/recognize_cographs.h)

### Graph Decomposition

- [ ] [Decompose into paths of length 2](04_graphs/10_graph_decomposition/decompose_into_paths_of_length_2.h)

### Chromatic Polynomial

- [ ] [Chromatic polynomial functional graph](04_graphs/11_chromatic_polynomial/chromatic_polynomial_functional_graph.h)

### Tree Decomposition

- [ ] [Is tree decomposition of](04_graphs/12_tree_decomposition/is_tree_decomposition_of.h)
- [ ] [Maximum independent set on tree decomposition](04_graphs/12_tree_decomposition/maximum_independent_set_on_tree_decomposition.h)
- [ ] [Tree decomposition cactus halin graph](04_graphs/12_tree_decomposition/tree_decomposition_cactus_halin_graph.h)
- [ ] [Tree decomposition chordal graph](04_graphs/12_tree_decomposition/tree_decomposition_chordal_graph.h)
- [ ] [Tree decomposition halin graph](04_graphs/12_tree_decomposition/tree_decomposition_halin_graph.h)

## 5. Dynamic Programming

Knapsack, then the optimizations: divide and conquer, Knuth, monotone queue, SMAWK, Lagrange.

### Knapsack

- [ ] [Knapsack optimizer](05_dynamic_programming/01_knapsack/knapsack_optimizer.h)
- [ ] [Subset sum optimizer](05_dynamic_programming/01_knapsack/subset_sum_optimizer.h)
- [ ] [Subset sum processor](05_dynamic_programming/01_knapsack/subset_sum_processor.h)

- [ ] [Count rectangles within grid](05_dynamic_programming/count_rectangles_within_grid.h)
- [ ] [Divide and conquer optimization](05_dynamic_programming/divide_and_conquer_optimization.h)
- [ ] [Knuth optimization](05_dynamic_programming/knuth_optimization.h)
- [ ] [Lagrange optimization](05_dynamic_programming/lagrange_optimization.h)
- [ ] [Monotone queue optimization](05_dynamic_programming/monotone_queue_optimization.h)
- [ ] [Smawk](05_dynamic_programming/smawk.h)
- [ ] [Span with subarray](05_dynamic_programming/span_with_subarray.h)

## 6. String

Hashing and tries, then prefix structures (suffix array, automata), then palindromes and Lyndon words.

### Hash

- [x] Hash — ours: [`rollinghash.h`](https://github.com/lamng3/competitive-programming-notebook/blob/main/notebook/strings/rolling_hash/rollinghash.h)
- [ ] [Hash bidirectional](06_strings/01_hash/hash_bidirectional.h)
- [ ] [Substring hasher](06_strings/01_hash/substring_hasher.h)

### Trie

- [ ] [Binary trie](06_strings/02_trie/binary_trie.h)
- [ ] [Trie](06_strings/02_trie/trie.h) (Python: [`Trie.py`](https://github.com/lamng3/competitive-programming-notebook/blob/main/python/strings/trie/Trie.py))

### Longest Common Subsequence

- [ ] [Circular longest common subsequence](06_strings/03_longest_common_subsequence/circular_longest_common_subsequence.h)
- [ ] [Longest common subsequence](06_strings/03_longest_common_subsequence/longest_common_subsequence.h)
- [ ] [Longest common subsequence lengths](06_strings/03_longest_common_subsequence/longest_common_subsequence_lengths.h)

### Manacher

- [ ] [Manacher](06_strings/04_manacher/manacher.h)

### Suffix Array

- [ ] [Suffix array](06_strings/05_suffix_array/suffix_array.h)
- [ ] [Suffix array slow](06_strings/05_suffix_array/suffix_array_slow.h)

### Suffix Automaton

- [ ] [Suffix automaton](06_strings/06_suffix_automaton/suffix_automaton.h)

### Suffix Tree

- [ ] [Suffix tree](06_strings/07_suffix_tree/suffix_tree.h)

### Aho Corasic Automaton

- [ ] [Aho corasic automaton fixed](06_strings/08_aho_corasic_automaton/aho_corasic_automaton_fixed.h)
- [ ] [Aho corasic automaton unfixed](06_strings/08_aho_corasic_automaton/aho_corasic_automaton_unfixed.h)

### Palindrome Automaton

- [ ] [Palindrome automaton](06_strings/09_palindrome_automaton/palindrome_automaton.h)

### Lyndon

- [ ] [Lyndon factorization](06_strings/10_lyndon/lyndon_factorization.h)
- [ ] [Minimal rotation](06_strings/10_lyndon/minimal_rotation.h)

### Main Lorentz

- [ ] [Main lorentz](06_strings/11_main_lorentz/main_lorentz.h)

### Matching With Wildcards

- [ ] [Matching with wildcards](06_strings/12_matching_with_wildcards/matching_with_wildcards.h)
- [ ] [Matching with wildcards randomized](06_strings/12_matching_with_wildcards/matching_with_wildcards_randomized.h)

### Burrows Wheeler Transform

- [ ] [Burrows wheeler transform](06_strings/13_burrows_wheeler_transform/burrows_wheeler_transform.h)

### Finite Automaton

- [ ] [Deterministic finite automaton](06_strings/14_finite_automaton/deterministic_finite_automaton.h)

### Autocorrelation

- [ ] [Autocorrelation free variable count](06_strings/15_autocorrelation/autocorrelation_free_variable_count.h)
- [ ] [Autocorrelation membership test](06_strings/15_autocorrelation/autocorrelation_membership_test.h)
- [ ] [Autocorrelation to string](06_strings/15_autocorrelation/autocorrelation_to_string.h)
- [ ] [Enumerate autocorrelations](06_strings/15_autocorrelation/enumerate_autocorrelations.h)
- [ ] [String to autocorrelation](06_strings/15_autocorrelation/string_to_autocorrelation.h)

### Composite String Comparator

- [ ] [Composite string comparator](06_strings/16_composite_string_comparator/composite_string_comparator.h)

### String Processor

- [ ] [String processor](06_strings/17_string_processor/string_processor.h)

### Utility

- [ ] [Count common substrings](06_strings/18_utility/count_common_substrings.h)
- [ ] [Count distinct substrings](06_strings/18_utility/count_distinct_substrings.h)
- [ ] [Distinct substring count query solver offline](06_strings/18_utility/distinct_substring_count_query_solver_offline.h)
- [ ] [Longest common substring](06_strings/18_utility/longest_common_substring.h)

## 7. Number Theory

Modular arithmetic, Euclid and CRT, factorization, then multiplicative prefix sums.

- [ ] [Barret reduction](07_number_theory/barret_reduction.h)
- [ ] [Diophantine](07_number_theory/diophantine.h)
- [ ] [Dirichlet convolution formulae](07_number_theory/dirichlet_convolution_formulae.h)
- [ ] [Divisor count function prefix sum](07_number_theory/divisor_count_function_prefix_sum.h)
- [ ] [Divisor processor](07_number_theory/divisor_processor.h)
- [ ] [Extended euclidean](07_number_theory/extended_euclidean.h)
- [ ] [Factorize](07_number_theory/factorize.h)
- [ ] [Find first residue](07_number_theory/find_first_residue.h)
- [ ] [Floor sum](07_number_theory/floor_sum.h)
- [ ] [Floor sum weighted](07_number_theory/floor_sum_weighted.h)
- [ ] [Harmonic loop](07_number_theory/harmonic_loop.h)
- [ ] [Inverse linear congruential generator](07_number_theory/inverse_linear_congruential_generator.h)
- [ ] [Jacobi symbol](07_number_theory/jacobi_symbol.h)
- [ ] [Number theory](07_number_theory/number_theory.h)
- [ ] [Pollard rho](07_number_theory/pollard_rho.h)
- [ ] [Solve EGZ](07_number_theory/solve_egz.h)

### Modular

- [ ] [Mod sqrt](07_number_theory/01_modular/mod_sqrt.h)
- [ ] [Modular fixed](07_number_theory/01_modular/modular_fixed.h)
- [ ] [Modular unfixed](07_number_theory/01_modular/modular_unfixed.h)
- [ ] [Montgomery modular fixed](07_number_theory/01_modular/montgomery_modular_fixed.h)
- [ ] [Montgomery modular unfixed](07_number_theory/01_modular/montgomery_modular_unfixed.h)

### Chinese Remainder Theorem

- [ ] [Chinese remainder theorem coprime fixed width](07_number_theory/02_chinese_remainder_theorem/chinese_remainder_theorem_coprime_fixed_width.h)
- [ ] [Chinese remainder theorem linear](07_number_theory/02_chinese_remainder_theorem/chinese_remainder_theorem_linear.h)

### Integer Decomposition

- [ ] [Solve fermat three triangle](07_number_theory/03_integer_decomposition/solve_fermat_three_triangle.h)
- [ ] [Solve fermat two square](07_number_theory/03_integer_decomposition/solve_fermat_two_square.h)
- [ ] [Solve lagrange four square](07_number_theory/03_integer_decomposition/solve_lagrange_four_square.h)
- [ ] [Solve legendre three square](07_number_theory/03_integer_decomposition/solve_legendre_three_square.h)

### Multiplicative Prefix Sum

- [ ] [Count primes](07_number_theory/04_multiplicative_prefix_sum/count_primes.h)
- [ ] [Meissel lehmer](07_number_theory/04_multiplicative_prefix_sum/meissel_lehmer.h)
- [ ] [Min25 sieve](07_number_theory/04_multiplicative_prefix_sum/min25_sieve.h)
- [ ] [Min25 sieve wrong](07_number_theory/04_multiplicative_prefix_sum/min25_sieve_wrong.h)
- [ ] [Xudyh sieve](07_number_theory/04_multiplicative_prefix_sum/xudyh_sieve.h)

## 8. Continued Fraction and Farey Sequence

Best rational approximations: a short follow-on to number theory.

- [ ] [Continued fraction](08_number_theory_continued_fractions/continued_fraction.h)
- [ ] [Farey sequence](08_number_theory_continued_fractions/farey_sequence.h)

## 9. Combinatorial

Counting, LIS, permutations, then flows and matchings, matroids, and Young tableaux.

- [ ] [Bidirectional ballot sequence count](09_combinatorics/bidirectional_ballot_sequence_count.h)
- [ ] [Combinatorics](09_combinatorics/combinatorics.h)
- [ ] [Compute sum of non intersecting tuples of paths](09_combinatorics/compute_sum_of_non_intersecting_tuples_of_paths.h)
- [ ] [Enumerate partitions](09_combinatorics/enumerate_partitions.h)
- [ ] [Enumerate polyominos](09_combinatorics/enumerate_polyominos.h)
- [ ] [Q combinatorics](09_combinatorics/q_combinatorics.h)

### Permutation

- [ ] [Count inversions](09_combinatorics/01_permutation/count_inversions.h)
- [ ] [Permutation](09_combinatorics/01_permutation/permutation.h)

### Longest Monotone Subsequence

- [ ] [Longest increasing bisubsequence](09_combinatorics/02_longest_monotone_subsequence/longest_increasing_bisubsequence.h)
- [ ] [Longest increasing subsequence](09_combinatorics/02_longest_monotone_subsequence/longest_increasing_subsequence.h)
- [ ] [Longest increasing subsequence processor](09_combinatorics/02_longest_monotone_subsequence/longest_increasing_subsequence_processor.h)

### Flow Matching And Cut

- [ ] [Blossom maximum unweighted matching](09_combinatorics/03_flow_matching_and_cut/blossom_maximum_unweighted_matching.h)
- [ ] [Dinic maximum flow](09_combinatorics/03_flow_matching_and_cut/dinic_maximum_flow.h)
- [ ] [Flow decomposition](09_combinatorics/03_flow_matching_and_cut/flow_decomposition.h)
- [ ] [Global min cut](09_combinatorics/03_flow_matching_and_cut/global_min_cut.h)
- [ ] [Gomory hu](09_combinatorics/03_flow_matching_and_cut/gomory_hu.h)
- [ ] [Hopcroft karp algorithm](09_combinatorics/03_flow_matching_and_cut/hopcroft_karp_algorithm.h)
- [ ] [Hungarian weighted bipartite matching](09_combinatorics/03_flow_matching_and_cut/hungarian_weighted_bipartite_matching.h)
- [ ] [Kuhn algorithm](09_combinatorics/03_flow_matching_and_cut/kuhn_algorithm.h)
- [ ] [Maximum antichain](09_combinatorics/03_flow_matching_and_cut/maximum_antichain.h)
- [ ] [Maximum density subset](09_combinatorics/03_flow_matching_and_cut/maximum_density_subset.h)
- [ ] [Maximum weight matching](09_combinatorics/03_flow_matching_and_cut/maximum_weight_matching.h)
- [ ] [Maximum weight matching short](09_combinatorics/03_flow_matching_and_cut/maximum_weight_matching_short.h)
- [ ] [Minimum path cover](09_combinatorics/03_flow_matching_and_cut/minimum_path_cover.h)
- [ ] [Network simplex](09_combinatorics/03_flow_matching_and_cut/network_simplex.h)
- [ ] [Positive bipartite two sat](09_combinatorics/03_flow_matching_and_cut/positive_bipartite_two_sat.h)
- [ ] [Push relabel](09_combinatorics/03_flow_matching_and_cut/push_relabel.h)
- [ ] [Spanning tree polytope separation oracle](09_combinatorics/03_flow_matching_and_cut/spanning_tree_polytope_separation_oracle.h)

### Flow Matching And Cut / Minimum Cost Maximum Flow

- [ ] [Minimum cost maximum flow johnson](09_combinatorics/03_flow_matching_and_cut/minimum_cost_maximum_flow/minimum_cost_maximum_flow_johnson.h)
- [ ] [Minimum cost maximum flow push relabel](09_combinatorics/03_flow_matching_and_cut/minimum_cost_maximum_flow/minimum_cost_maximum_flow_push_relabel.h)
- [ ] [Minimum cost maximum flow SPFA](09_combinatorics/03_flow_matching_and_cut/minimum_cost_maximum_flow/minimum_cost_maximum_flow_spfa.h)

### Flow Matching And Cut / Fundamentals

- [ ] [Flow network](09_combinatorics/03_flow_matching_and_cut/fundamentals/flow_network.h)
- [ ] [Flow network weighted](09_combinatorics/03_flow_matching_and_cut/fundamentals/flow_network_weighted.h)
- [ ] [Flow network with demand](09_combinatorics/03_flow_matching_and_cut/fundamentals/flow_network_with_demand.h)
- [ ] [Maximum bipartite matching solver](09_combinatorics/03_flow_matching_and_cut/fundamentals/maximum_bipartite_matching_solver.h)

### Linear Programming

- [ ] [Linear programming solver simplex](09_combinatorics/04_linear_programming/linear_programming_solver_simplex.h)

### Matroid

- [ ] [Matroid intersection](09_combinatorics/05_matroid/matroid_intersection.h)
- [ ] [Matroid intersection weighted bellman ford](09_combinatorics/05_matroid/matroid_intersection_weighted_bellman_ford.h)
- [ ] [Matroid intersection weighted SPFA](09_combinatorics/05_matroid/matroid_intersection_weighted_spfa.h)

### Matroid / Matroid Generators

- [ ] [GF2 linear matroid](09_combinatorics/05_matroid/matroid_generators/gf2_linear_matroid.h)
- [ ] [Colorful matroid](09_combinatorics/05_matroid/matroid_generators/colorful_matroid.h)
- [ ] [Graphic matroid](09_combinatorics/05_matroid/matroid_generators/graphic_matroid.h)
- [ ] [Partition matroid](09_combinatorics/05_matroid/matroid_generators/partition_matroid.h)
- [ ] [Rigidity matroid](09_combinatorics/05_matroid/matroid_generators/rigidity_matroid.h)

### Submodularity

- [ ] [Check antisubmodularity](09_combinatorics/06_submodularity/check_antisubmodularity.h)
- [ ] [Graph representable monge function optimization](09_combinatorics/06_submodularity/graph_representable_monge_function_optimization.h)
- [ ] [Graph representable submodular function optimization](09_combinatorics/06_submodularity/graph_representable_submodular_function_optimization.h)

### Young Tableau

- [ ] [RSK inverse mapping](09_combinatorics/07_young_tableau/rsk_inverse_mapping.h)
- [ ] [RSK mapping](09_combinatorics/07_young_tableau/rsk_mapping.h)
- [ ] [RSK mapping fast](09_combinatorics/07_young_tableau/rsk_mapping_fast.h)
- [ ] [Count young tableaux](09_combinatorics/07_young_tableau/count_young_tableaux.h)
- [ ] [Longest k increasing subsequence nk log n nk²](09_combinatorics/07_young_tableau/longest_k_increasing_subsequence_nklogn_nk2.h)
- [ ] [Longest k increasing subsequence nr](09_combinatorics/07_young_tableau/longest_k_increasing_subsequence_nr.h)

### Block Minmax Processor

- [ ] [Block minmax processor](09_combinatorics/08_block_minmax_processor/block_minmax_processor.h)
- [ ] [Block minmax processor 2D](09_combinatorics/08_block_minmax_processor/block_minmax_processor_2d.h)

### Edge Coloring

- [ ] [Edge coloring bipartite](09_combinatorics/09_edge_coloring/edge_coloring_bipartite.h)
- [ ] [Edge coloring vizing](09_combinatorics/09_edge_coloring/edge_coloring_vizing.h)

## 10. Linear Algebra

Matrices, Gaussian elimination (also over GF2), and linear recurrences.

### Matrix

- [ ] [Characteristic polynomial](10_linear_algebra/01_matrix/characteristic_polynomial.h)
- [ ] [Characteristic polynomial commutative ring](10_linear_algebra/01_matrix/characteristic_polynomial_commutative_ring.h)
- [ ] [Determinant commutative ring](10_linear_algebra/01_matrix/determinant_commutative_ring.h)
- [ ] [Determinant linear polynomial](10_linear_algebra/01_matrix/determinant_linear_polynomial.h)
- [ ] [Determinant polynomial](10_linear_algebra/01_matrix/determinant_polynomial.h)
- [ ] [Matrix](10_linear_algebra/01_matrix/matrix.h)
- [ ] [Matrix AND OR base](10_linear_algebra/01_matrix/matrix_and_or_base.h)
- [ ] [Matrix OR AND](10_linear_algebra/01_matrix/matrix_or_and.h)
- [ ] [Matrix Z2](10_linear_algebra/01_matrix/matrix_z2.h)
- [ ] [Matrix fixed](10_linear_algebra/01_matrix/matrix_fixed.h)
- [ ] [Matrix inverse tracker](10_linear_algebra/01_matrix/matrix_inverse_tracker.h)
- [ ] [Sparse determinant](10_linear_algebra/01_matrix/sparse_determinant.h)
- [ ] [Sparse minimal polynomial](10_linear_algebra/01_matrix/sparse_minimal_polynomial.h)
- [ ] [Tridiagonal matrix determinant](10_linear_algebra/01_matrix/tridiagonal_matrix_determinant.h)
- [ ] [Tridiagonal matrix equation solver](10_linear_algebra/01_matrix/tridiagonal_matrix_equation_solver.h)

### Linear Equation Solver

- [ ] [Linear equation solver](10_linear_algebra/02_linear_equation_solver/linear_equation_solver.h)
- [ ] [Linear equation solver GF2](10_linear_algebra/02_linear_equation_solver/linear_equation_solver_gf2.h)
- [ ] [Pick subset with given xor](10_linear_algebra/02_linear_equation_solver/pick_subset_with_given_xor.h)

### Linear Recurrence Solver

- [ ] [Fibonacci](10_linear_algebra/03_linear_recurrence_solver/fibonacci.h)
- [ ] [Linear recurrence solver](10_linear_algebra/03_linear_recurrence_solver/linear_recurrence_solver.h)
- [ ] [Linear recurrence solver bostan mori](10_linear_algebra/03_linear_recurrence_solver/linear_recurrence_solver_bostan_mori.h)
- [ ] [Linear recurrence solver modular exponentiation](10_linear_algebra/03_linear_recurrence_solver/linear_recurrence_solver_modular_exponentiation.h)

## 11. Power Series

FFT and NTT first; everything else in this section multiplies polynomials with them.

### Transformations

- [ ] [Chirp z transform](11_power_series/01_transformations/chirp_z_transform.h)
- [ ] [Fast fourier transform](11_power_series/01_transformations/fast_fourier_transform.h)
- [ ] [Fast fourier transform multidimensional](11_power_series/01_transformations/fast_fourier_transform_multidimensional.h)
- [ ] [Number theoric transform](11_power_series/01_transformations/number_theoric_transform.h)

- [ ] [Chebyshev eval](11_power_series/chebyshev_eval.h)
- [ ] [Interpolate range naive](11_power_series/interpolate_range_naive.h)
- [ ] [Polynomial shift sampling](11_power_series/polynomial_shift_sampling.h)
- [ ] [Power series](11_power_series/power_series.h)
- [ ] [Power series composition](11_power_series/power_series_composition.h)
- [ ] [Power series compositional inverse](11_power_series/power_series_compositional_inverse.h)
- [ ] [Power series naive](11_power_series/power_series_naive.h)
- [ ] [Power series online](11_power_series/power_series_online.h)
- [ ] [Power series sqrt](11_power_series/power_series_sqrt.h)
- [ ] [Rational polynomial single term extraction](11_power_series/rational_polynomial_single_term_extraction.h)
- [ ] [Reduce quadratic GF2 polynomial](11_power_series/reduce_quadratic_gf2_polynomial.h)
- [ ] [Sequential polynomial](11_power_series/sequential_polynomial.h)
- [ ] [Subproduct tree](11_power_series/subproduct_tree.h)
- [ ] [Taylor shift](11_power_series/taylor_shift.h)
- [ ] [Touchard polynomial](11_power_series/touchard_polynomial.h)

### Convolutions

- [ ] [Convolve subset](11_power_series/02_convolutions/convolve_subset.h)

### Power Sum

- [ ] [Bernoulli number](11_power_series/03_power_sum/bernoulli_number.h)
- [ ] [Power sum](11_power_series/03_power_sum/power_sum.h)
- [ ] [Power sum prefix evaluation](11_power_series/03_power_sum/power_sum_prefix_evaluation.h)

### Bell Number

- [ ] [Bell number](11_power_series/04_bell_number/bell_number.h)

### Set Power Series

- [ ] [Exponential set power series](11_power_series/05_set_power_series/exponential_set_power_series.h)
- [ ] [Logarithm set power series](11_power_series/05_set_power_series/logarithm_set_power_series.h)

## 12. Abstract Algebra

Groups, rings, and finite fields: the structures behind modular arithmetic and hashing.

- [ ] [Cosets](12_abstract_algebra/cosets.h)
- [ ] [Division ring](12_abstract_algebra/division_ring.h)
- [ ] [Elliptic curve](12_abstract_algebra/elliptic_curve.h)
- [ ] [Field of fraction](12_abstract_algebra/field_of_fraction.h)
- [ ] [Find a commutative group basis](12_abstract_algebra/find_a_commutative_group_basis.h)
- [ ] [Find the order of all group elements](12_abstract_algebra/find_the_order_of_all_group_elements.h)
- [ ] [Group](12_abstract_algebra/group.h)
- [ ] [Group generator](12_abstract_algebra/group_generator.h)
- [ ] [Monoid](12_abstract_algebra/monoid.h)
- [ ] [Nimber product](12_abstract_algebra/nimber_product.h)
- [ ] [Quotient group](12_abstract_algebra/quotient_group.h)
- [ ] [Ring](12_abstract_algebra/ring.h)
- [ ] [Test closedness](12_abstract_algebra/test_closedness.h)
- [ ] [Test commutative group isomorphism](12_abstract_algebra/test_commutative_group_isomorphism.h)
- [ ] [Test commutative group nilpotency](12_abstract_algebra/test_commutative_group_nilpotency.h)
- [ ] [Test direct product](12_abstract_algebra/test_direct_product.h)
- [ ] [Test group axioms](12_abstract_algebra/test_group_axioms.h)
- [ ] [Test group commutativity](12_abstract_algebra/test_group_commutativity.h)
- [ ] [Test normal subgroup](12_abstract_algebra/test_normal_subgroup.h)

### Finite Field

- [ ] [Factorizer over finite field](12_abstract_algebra/01_finite_field/factorizer_over_finite_field.h)
- [ ] [Finite field char 2 small](12_abstract_algebra/01_finite_field/finite_field_char2_small.h)
- [ ] [Irreducibility finite field](12_abstract_algebra/01_finite_field/irreducibility_finite_field.h)

### Lambda Operations

- [ ] [Lambda arithmetic monoid action](12_abstract_algebra/02_lambda_operations/lambda_arithmetic_monoid_action.h)

## 13. Geometry

Points and lines first, then polygons, circles, convex hulls, sweeps, and triangulations.

### Point

- [ ] [Point](13_geometry/01_point/point.h)
- [ ] [Point3](13_geometry/01_point/point3.h)

### Line

- [ ] [Find closed lines intersections](13_geometry/02_line/find_closed_lines_intersections.h)
- [ ] [Line](13_geometry/02_line/line.h)
- [ ] [Line3](13_geometry/02_line/line3.h)
- [ ] [Line intersection](13_geometry/02_line/line_intersection.h)
- [ ] [Line to line distance](13_geometry/02_line/line_to_line_distance.h)

### Polygon

- [ ] [Point in polygon](13_geometry/03_polygon/point_in_polygon.h)
- [ ] [Polygon cut](13_geometry/03_polygon/polygon_cut.h)
- [ ] [Segment in polygon](13_geometry/03_polygon/segment_in_polygon.h)

### Convex Polygon

- [ ] [Convex polygon](13_geometry/04_convex_polygon/convex_polygon.h)
- [ ] [Convex polygon diameter](13_geometry/04_convex_polygon/convex_polygon_diameter.h)
- [ ] [Convex polygon extreme point](13_geometry/04_convex_polygon/convex_polygon_extreme_point.h)
- [ ] [Convex polygon locate](13_geometry/04_convex_polygon/convex_polygon_locate.h)
- [ ] [Convex polyhedra](13_geometry/04_convex_polygon/convex_polyhedra.h)
- [ ] [Count convex polygon](13_geometry/04_convex_polygon/count_convex_polygon.h)
- [ ] [Find convex polygon point inclusion relations](13_geometry/04_convex_polygon/find_convex_polygon_point_inclusion_relations.h)
- [ ] [Half planes intersection](13_geometry/04_convex_polygon/half_planes_intersection.h)

### Circle

- [ ] [Circle](13_geometry/05_circle/circle.h)
- [ ] [Circle common tangents](13_geometry/05_circle/circle_common_tangents.h)
- [ ] [Circle intersection](13_geometry/05_circle/circle_intersection.h)
- [ ] [Circle polygon intersection](13_geometry/05_circle/circle_polygon_intersection.h)
- [ ] [Find circle point inclusion relations](13_geometry/05_circle/find_circle_point_inclusion_relations.h)
- [ ] [Minimum enclosing circle](13_geometry/05_circle/minimum_enclosing_circle.h)
- [ ] [Radical axis](13_geometry/05_circle/radical_axis.h)

### Norm

- [ ] [Find a closest pair](13_geometry/06_norm/find_a_closest_pair.h)
- [ ] [Find a furthest pair L1](13_geometry/06_norm/find_a_furthest_pair_l1.h)
- [ ] [Find a furthest pair L2](13_geometry/06_norm/find_a_furthest_pair_l2.h)
- [ ] [Find a furthest pair L∞](13_geometry/06_norm/find_a_furthest_pair_linf.h)
- [ ] [Rectilinear minimum spanning tree](13_geometry/06_norm/rectilinear_minimum_spanning_tree.h)

### Sweepline

- [ ] [Radial sweepline grouper](13_geometry/07_sweepline/radial_sweepline_grouper.h)
- [ ] [Radial sweepline sorter](13_geometry/07_sweepline/radial_sweepline_sorter.h)

### Decomposition

- [ ] [Delaunay triangulation](13_geometry/08_decomposition/delaunay_triangulation.h)
- [ ] [Quad edge](13_geometry/08_decomposition/quad_edge.h)
- [ ] [Trapzoidal decomposition](13_geometry/08_decomposition/trapzoidal_decomposition.h)
- [ ] [Triangular decomposition](13_geometry/08_decomposition/triangular_decomposition.h)

- [ ] [Triangle centers](13_geometry/triangle_centers.h)

## 14. Succinct Structures

Bit-packed rank and select.

- [ ] [Succinct dictionary](14_succinct_structures/succinct_dictionary.h)

## 15. Heuristic Algorithms

Simulated annealing and randomized search, for when nothing exact fits.

- [ ] [Hamiltonian path of random graph](15_heuristics/hamiltonian_path_of_random_graph.h)
- [ ] [Simulated annealing](15_heuristics/simulated_annealing.h)

## 16. Random Generators

Random trees, graphs, and polygons, for stress-testing everything above.

- [ ] [Generate chordal graph](16_random_generators/generate_chordal_graph.h)
- [ ] [Generate colinear points](16_random_generators/generate_colinear_points.h)
- [ ] [Generate edge cactus](16_random_generators/generate_edge_cactus.h)
- [ ] [Generate graph](16_random_generators/generate_graph.h)
- [ ] [Generate parallel planar graph](16_random_generators/generate_parallel_planar_graph.h)
- [ ] [Generate planar graph](16_random_generators/generate_planar_graph.h)
- [ ] [Generate simple graph](16_random_generators/generate_simple_graph.h)
- [ ] [Generate simple polygon](16_random_generators/generate_simple_polygon.h)
- [ ] [Generate simply connected bipartite graph](16_random_generators/generate_simply_connected_bipartite_graph.h)
- [ ] [Generate simply connected graph](16_random_generators/generate_simply_connected_graph.h)
- [ ] [Generate tree](16_random_generators/generate_tree.h)

## 17. Miscellaneous

Fast IO, big integers, bit tricks, and other utilities.

- [ ] [Bigint](17_miscellaneous/bigint.h)
- [ ] [Bitset64](17_miscellaneous/bitset64.h)
- [ ] [Bitset augmentation](17_miscellaneous/bitset_augmentation.h)
- [ ] [De bruijn bit magic](17_miscellaneous/de_bruijn_bit_magic.h)
- [ ] [Fast IO](17_miscellaneous/fastio.h)
- [ ] [Floored root](17_miscellaneous/floored_root.h)
- [ ] [Hilbert curve 2D](17_miscellaneous/hilbert_curve_2d.h)
- [ ] [Int128 augmentation](17_miscellaneous/int128_augmentation.h)
- [ ] [Logging allocator](17_miscellaneous/logging_allocator.h)
- [ ] [MEX](17_miscellaneous/mex.h)
- [ ] [Next bit permutation](17_miscellaneous/next_bit_permutation.h)
- [ ] [PBDS](17_miscellaneous/pbds.h)
- [ ] [PNG parser](17_miscellaneous/png_parser.h)
- [ ] [Random](17_miscellaneous/random.h)
- [ ] [State evolver](17_miscellaneous/state_evolver.h)
- [ ] [Timer](17_miscellaneous/timer.h)
- [ ] [Trygub number](17_miscellaneous/trygub_number.h)
- [ ] [Type name](17_miscellaneous/type_name.h)
- [x] Value compressor — ours: [`CoordinateCompression.h`](https://github.com/lamng3/competitive-programming-notebook/blob/main/notebook/utils/CoordinateCompression.h)
- [ ] [Y combinator](17_miscellaneous/y_combinator.h)

## 18. Network Communication

Communication problems, where two programs talk through a limited channel.

- [ ] [Network communication manager](18_network_communication/network_communication_manager.h)
