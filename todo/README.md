# TODO: topics to study

A study list in C++, taken from the topics in **fextivity**'s library, [CP-aeren/Library](https://github.com/fextivity/CP-aeren/tree/main/Library). Credit for the topic list goes to fextivity. No code is copied: each topic has an empty C++ stub here, and the stub links fextivity's snippet as the reference.

The sections are numbered in study order: each one leans on the ones before it. Inside a section, subfolders follow fextivity's grouping.

To study a topic: read the reference and a write-up of the idea, fill in the stub in the notebook's style, add a test next to it (`cpunit <name>`), then move it into `notebook/` and tick it here.

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

- [ ] [Binary geometric sum](01_searching/binary_geometric_sum.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Numeric/binary_geometric_sum.sublime-snippet)
- [ ] [Binary geometric sum general](01_searching/binary_geometric_sum_general.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Numeric/binary_geometric_sum_general.sublime-snippet)
- [x] Binary power — ours: [`ModInv.h`](https://github.com/lamng3/competitive-programming-notebook/blob/main/notebook/math/modular_arithmetic/ModInv.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Numeric/binary_power.sublime-snippet)
- [ ] [Binary power general](01_searching/binary_power_general.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Numeric/binary_power_general.sublime-snippet)
- [ ] [Binary string](01_searching/binary_string.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Numeric/binary_string.sublime-snippet)
- [ ] [Continuous binary search](01_searching/continuous_binary_search.h) (Python: [`BinarySearch.py`](https://github.com/lamng3/competitive-programming-notebook/blob/main/python/searching/binary_search/BinarySearch.py)) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Numeric/continuous_binary_search.sublime-snippet)
- [ ] [Counting iterator](01_searching/counting_iterator.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Numeric/counting_iterator.sublime-snippet)
- [ ] [Discrete golden section search](01_searching/discrete_golden_section_search.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Numeric/discrete_golden_section_search.sublime-snippet)
- [ ] [Discrete ternary search](01_searching/discrete_ternary_search.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Numeric/discrete_ternary_search.sublime-snippet)
- [ ] [Double parallel binary search](01_searching/double_parallel_binary_search.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Numeric/double_parallel_binary_search.sublime-snippet)
- [ ] [Find prefix xor order](01_searching/find_prefix_xor_order.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Numeric/find_prefix_xor_order.sublime-snippet)
- [ ] [Fractional search](01_searching/fractional_search.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Numeric/fractional_search.sublime-snippet)
- [ ] [Golden section search](01_searching/golden_section_search.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Numeric/golden_section_search.sublime-snippet)
- [ ] [Parallel binary search](01_searching/parallel_binary_search.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Numeric/parallel_binary_search.sublime-snippet)
- [ ] [Solve cubic equation](01_searching/solve_cubic_equation.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Numeric/solve_cubic_equation.sublime-snippet)

## 2. Data Structure

Range queries first (Fenwick, sparse table, segment trees), then sqrt tricks, line containers, treaps, and the rest.

### Fenwick Tree

- [x] Fenwick tree — ours: [`FenwickTree.h`](https://github.com/lamng3/competitive-programming-notebook/blob/main/notebook/data_structures/1d_range_query/FenwickTree.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Fenwick_Tree/fenwick_tree.sublime-snippet)
- [ ] [Fenwick tree 2D sparse sum](02_data_structures/01_fenwick_tree/fenwick_tree_2d_sparse_sum.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Fenwick_Tree/fenwick_tree_2d_sparse_sum.sublime-snippet)
- [ ] [Fenwick tree 2D sum](02_data_structures/01_fenwick_tree/fenwick_tree_2d_sum.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Fenwick_Tree/fenwick_tree_2d_sum.sublime-snippet)
- [ ] [Fenwick tree 3D sum](02_data_structures/01_fenwick_tree/fenwick_tree_3d_sum.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Fenwick_Tree/fenwick_tree_3d_sum.sublime-snippet)
- [ ] [Range add query sum solver](02_data_structures/01_fenwick_tree/range_add_query_sum_solver.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Fenwick_Tree/range_add_query_sum_solver.sublime-snippet)
- [ ] [Range add query sum solver 2D](02_data_structures/01_fenwick_tree/range_add_query_sum_solver_2d.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Fenwick_Tree/range_add_query_sum_solver_2d.sublime-snippet)
- [ ] [Range xor query xor solver 2D](02_data_structures/01_fenwick_tree/range_xor_query_xor_solver_2d.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Fenwick_Tree/range_xor_query_xor_solver_2d.sublime-snippet)

### Sparse Table

- [ ] [Range minmax query solver](02_data_structures/02_sparse_table/range_minmax_query_solver.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Sparse_Table/range_minmax_query_solver.sublime-snippet)
- [ ] [Sparse table](02_data_structures/02_sparse_table/sparse_table.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Sparse_Table/sparse_table.sublime-snippet)
- [ ] [Sparse table 2D](02_data_structures/02_sparse_table/sparse_table_2d.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Sparse_Table/sparse_table_2d.sublime-snippet)
- [ ] [Sparse table 2D square](02_data_structures/02_sparse_table/sparse_table_2d_square.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Sparse_Table/sparse_table_2d_square.sublime-snippet)

### Disjoint Sparse Table

- [ ] [Disjoint sparse table](02_data_structures/03_disjoint_sparse_table/disjoint_sparse_table.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Disjoint_Sparse_Table/disjoint_sparse_table.sublime-snippet)

### Segment Tree

- [ ] [Mergesort tree](02_data_structures/04_segment_tree/mergesort_tree.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Segment_Tree/mergesort_tree.sublime-snippet)
- [ ] [Mergesort tree point update](02_data_structures/04_segment_tree/mergesort_tree_point_update.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Segment_Tree/mergesort_tree_point_update.sublime-snippet)
- [x] Segment tree — ours: [`SegmentTree.h`](https://github.com/lamng3/competitive-programming-notebook/blob/main/notebook/data_structures/1d_range_query/SegmentTree.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Segment_Tree/segment_tree.sublime-snippet)
- [ ] [Segment tree 2D](02_data_structures/04_segment_tree/segment_tree_2d.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Segment_Tree/segment_tree_2d.sublime-snippet)
- [ ] [Segment tree 2D sparse](02_data_structures/04_segment_tree/segment_tree_2d_sparse.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Segment_Tree/segment_tree_2d_sparse.sublime-snippet)
- [ ] [Segment tree 3D](02_data_structures/04_segment_tree/segment_tree_3d.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Segment_Tree/segment_tree_3d.sublime-snippet)
- [x] Segment tree dynamic — ours: [`SparseSegmentTree.h`](https://github.com/lamng3/competitive-programming-notebook/blob/main/notebook/data_structures/rurq/SparseSegmentTree.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Segment_Tree/segment_tree_dynamic.sublime-snippet)
- [x] Segment tree persistent — ours: [`PersistentSegmentTree.h`](https://github.com/lamng3/competitive-programming-notebook/blob/main/notebook/data_structures/rurq/PersistentSegmentTree.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Segment_Tree/segment_tree_persistent.sublime-snippet)
- [ ] [Segment tree wide](02_data_structures/04_segment_tree/segment_tree_wide.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Segment_Tree/segment_tree_wide.sublime-snippet)

### Disjoint Set

- [x] Disjoint set — ours: [`DSU.h`](https://github.com/lamng3/competitive-programming-notebook/blob/main/notebook/graphs/dsu/DSU.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Disjoint_Set/disjoint_set.sublime-snippet)
- [ ] [Disjoint set 2D](02_data_structures/05_disjoint_set/disjoint_set_2d.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Disjoint_Set/disjoint_set_2d.sublime-snippet)
- [x] Disjoint set rollback — ours: [`DSURollback.h`](https://github.com/lamng3/competitive-programming-notebook/blob/main/notebook/graphs/dsu/DSURollback.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Disjoint_Set/disjoint_set_rollback.sublime-snippet)
- [ ] [Persistent disjoint set](02_data_structures/05_disjoint_set/persistent_disjoint_set.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Disjoint_Set/persistent_disjoint_set.sublime-snippet)

### Sliding Window Aggregation

- [ ] [SWAG deque](02_data_structures/06_sliding_window_aggregation/swag_deque.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Sliding_Window_Aggregation/swag_deque.sublime-snippet)
- [ ] [SWAG queue](02_data_structures/06_sliding_window_aggregation/swag_queue.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Sliding_Window_Aggregation/swag_queue.sublime-snippet)

### Sqrt Decomposition

- [ ] [Mo 2D](02_data_structures/07_sqrt_decomposition/mo_2d.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Sqrt_Decomposition/mo_2d.sublime-snippet)
- [ ] [Mo 2D hilbert curve ordering](02_data_structures/07_sqrt_decomposition/mo_2d_hilbert_curve_ordering.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Sqrt_Decomposition/mo_2d_hilbert_curve_ordering.sublime-snippet)
- [ ] [Mo 2D rectilinear spanning tree ordering](02_data_structures/07_sqrt_decomposition/mo_2d_rectilinear_spanning_tree_ordering.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Sqrt_Decomposition/mo_2d_rectilinear_spanning_tree_ordering.sublime-snippet)
- [ ] [Mo 2D rollback](02_data_structures/07_sqrt_decomposition/mo_2d_rollback.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Sqrt_Decomposition/mo_2d_rollback.sublime-snippet)
- [ ] [Mo 3D](02_data_structures/07_sqrt_decomposition/mo_3d.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Sqrt_Decomposition/mo_3d.sublime-snippet)
- [ ] [Mo sweepline](02_data_structures/07_sqrt_decomposition/mo_sweepline.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Sqrt_Decomposition/mo_sweepline.sublime-snippet)
- [ ] [Sqrt decomposition heavy point update light range query commutative group](02_data_structures/07_sqrt_decomposition/sqrt_decomposition_heavy_point_update_light_range_query_commutative_group.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Sqrt_Decomposition/sqrt_decomposition_heavy_point_update_light_range_query_commutative_group.sublime-snippet)
- [ ] [Sqrt decomposition light point update heavy range query commutative monoid](02_data_structures/07_sqrt_decomposition/sqrt_decomposition_light_point_update_heavy_range_query_commutative_monoid.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Sqrt_Decomposition/sqrt_decomposition_light_point_update_heavy_range_query_commutative_monoid.sublime-snippet)
- [ ] [Sqrt decomposition light range update heavy point query commutative group](02_data_structures/07_sqrt_decomposition/sqrt_decomposition_light_range_update_heavy_point_query_commutative_group.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Sqrt_Decomposition/sqrt_decomposition_light_range_update_heavy_point_query_commutative_group.sublime-snippet)

### Static Range Query Processor

- [ ] [Static range query processor](02_data_structures/08_static_range_query_processor/static_range_query_processor.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Static_Range_Query_Processor/static_range_query_processor.sublime-snippet)
- [ ] [Static range query processor 2D](02_data_structures/08_static_range_query_processor/static_range_query_processor_2d.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Static_Range_Query_Processor/static_range_query_processor_2d.sublime-snippet)
- [ ] [Static range query processor 3D](02_data_structures/08_static_range_query_processor/static_range_query_processor_3d.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Static_Range_Query_Processor/static_range_query_processor_3d.sublime-snippet)

### Heap

- [ ] [Skew heap](02_data_structures/09_heap/skew_heap.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Heap/skew_heap.sublime-snippet)

### Priority Queue

- [ ] [Partially retroactive priority queue](02_data_structures/10_priority_queue/partially_retroactive_priority_queue.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Priority_Queue/partially_retroactive_priority_queue.sublime-snippet)
- [ ] [Priority queue with update](02_data_structures/10_priority_queue/priority_queue_with_update.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Priority_Queue/priority_queue_with_update.sublime-snippet)

### Treap

- [ ] [Treap](02_data_structures/11_treap/treap.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Treap/treap.sublime-snippet)

### Cartesian Tree

- [ ] [Cartesian tree](02_data_structures/12_cartesian_tree/cartesian_tree.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Cartesian_Tree/cartesian_tree.sublime-snippet)

### Trie

- [ ] [Binary trie dynamic](02_data_structures/13_trie/binary_trie_dynamic.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Trie/binary_trie_dynamic.sublime-snippet)

### Line Container

- [ ] [Kinetic tournament](02_data_structures/14_line_container/kinetic_tournament.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Line_Container/kinetic_tournament.sublime-snippet)
- [ ] [Li chao tree](02_data_structures/14_line_container/li_chao_tree.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Line_Container/li_chao_tree.sublime-snippet)
- [ ] [Li chao tree fixed query](02_data_structures/14_line_container/li_chao_tree_fixed_query.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Line_Container/li_chao_tree_fixed_query.sublime-snippet)
- [ ] [Li chao tree order statistic](02_data_structures/14_line_container/li_chao_tree_order_statistic.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Line_Container/li_chao_tree_order_statistic.sublime-snippet)
- [ ] [Line container](02_data_structures/14_line_container/line_container.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Line_Container/line_container.sublime-snippet)
- [ ] [Piecewise linear function container](02_data_structures/14_line_container/piecewise_linear_function_container.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Line_Container/piecewise_linear_function_container.sublime-snippet)
- [ ] [Piecewise linear function container with skew heap](02_data_structures/14_line_container/piecewise_linear_function_container_with_skew_heap.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Line_Container/piecewise_linear_function_container_with_skew_heap.sublime-snippet)
- [ ] [Sorted line container](02_data_structures/14_line_container/sorted_line_container.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Line_Container/sorted_line_container.sublime-snippet)

### Interval Processor

- [ ] [Colorful interval set](02_data_structures/15_interval_processor/colorful_interval_set.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Interval_Processor/colorful_interval_set.sublime-snippet)
- [ ] [Interval set](02_data_structures/15_interval_processor/interval_set.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Interval_Processor/interval_set.sublime-snippet)

### Integral Set

- [ ] [Integral map](02_data_structures/16_integral_set/integral_map.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Integral_Set/integral_map.sublime-snippet)
- [ ] [Integral multiset](02_data_structures/16_integral_set/integral_multiset.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Integral_Set/integral_multiset.sublime-snippet)

### Persistent Array

- [ ] [Persistent array](02_data_structures/17_persistent_array/persistent_array.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Persistent_Array/persistent_array.sublime-snippet)

### Potential Tracker

- [ ] [Potential tracker](02_data_structures/18_potential_tracker/potential_tracker.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Potential_Tracker/potential_tracker.sublime-snippet)

### Wavelet Structures

- [ ] [Wavelet matrix](02_data_structures/19_wavelet_structures/wavelet_matrix.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Wavelet_Structures/wavelet_matrix.sublime-snippet)
- [ ] [Wavelet tree](02_data_structures/19_wavelet_structures/wavelet_tree.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Wavelet_Structures/wavelet_tree.sublime-snippet)

### Kd Tree

- [ ] [K-d tree minmax](02_data_structures/20_kd_tree/kdtree_minmax.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Kd_Tree/kdtree_minmax.sublime-snippet)

### Multidimentional Array

- [ ] [K-d array](02_data_structures/21_multidimentional_array/kdarray.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Multidimentional_Array/kdarray.sublime-snippet)
- [ ] [K-d sum](02_data_structures/21_multidimentional_array/kdsum.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Multidimentional_Array/kdsum.sublime-snippet)

### Range MEX Query Solver

- [ ] [Range MEX query solver offline](02_data_structures/22_range_mex_query_solver/range_mex_query_solver_offline.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Range_Mex_Query_Solver/range_mex_query_solver_offline.sublime-snippet)
- [ ] [Range MEX query solver online](02_data_structures/22_range_mex_query_solver/range_mex_query_solver_online.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Range_Mex_Query_Solver/range_mex_query_solver_online.sublime-snippet)

### Range Mode Query

- [ ] [Range mode query solver online](02_data_structures/23_range_mode_query/range_mode_query_solver_online.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Range_Mode_Query/range_mode_query_solver_online.sublime-snippet)

### Range Inversion Query Solver

- [ ] [Range inversion query solver offline](02_data_structures/24_range_inversion_query_solver/range_inversion_query_solver_offline.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Range_Inversion_Query_Solver/range_inversion_query_solver_offline.sublime-snippet)

### Distinct Value Query solver

- [ ] [Distinct value count query solve online cubic root](02_data_structures/25_distinct_value_query_solver/distinct_value_count_query_solve_online_cubic_root.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Distinct_Value_Query_solver/distinct_value_count_query_solve_online_cubic_root.sublime-snippet)
- [ ] [Distinct value query solver offline](02_data_structures/25_distinct_value_query_solver/distinct_value_query_solver_offline.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Distinct_Value_Query_solver/distinct_value_query_solver_offline.sublime-snippet)
- [ ] [Distinct value query solver online](02_data_structures/25_distinct_value_query_solver/distinct_value_query_solver_online.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Distinct_Value_Query_solver/distinct_value_query_solver_online.sublime-snippet)

### Value Range Query Solver

- [ ] [Value range query solver online sqrt](02_data_structures/26_value_range_query_solver/value_range_query_solver_online_sqrt.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Value_Range_Query_Solver/value_range_query_solver_online_sqrt.sublime-snippet)

### Value Trackers

- [ ] [Range choose sum tracker](02_data_structures/27_value_trackers/range_choose_sum_tracker.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Value_Trackers/range_choose_sum_tracker.sublime-snippet)
- [ ] [Sorted range sum tracker](02_data_structures/27_value_trackers/sorted_range_sum_tracker.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Value_Trackers/sorted_range_sum_tracker.sublime-snippet)

### Sequence Update Processor

- [ ] [Arithmetic sequence update processor](02_data_structures/28_sequence_update_processor/arithmetic_sequence_update_processor.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Sequence_Update_Processor/arithmetic_sequence_update_processor.sublime-snippet)
- [ ] [Polynomial sequence update processor](02_data_structures/28_sequence_update_processor/polynomial_sequence_update_processor.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Sequence_Update_Processor/polynomial_sequence_update_processor.sublime-snippet)

### Data Structure Enhancer

- [ ] [Data structure deletion enabler offline](02_data_structures/29_data_structure_enhancer/data_structure_deletion_enabler_offline.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Data_Structure_Enhancer/data_structure_deletion_enabler_offline.sublime-snippet)
- [ ] [Data structure insertion enabler online](02_data_structures/29_data_structure_enhancer/data_structure_insertion_enabler_online.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Data_Structure_Enhancer/data_structure_insertion_enabler_online.sublime-snippet)
- [ ] [Data structure multidimensional priority queue like deletion enabler online](02_data_structures/29_data_structure_enhancer/data_structure_multidimensional_priority_queue_like_deletion_enabler_online.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Data_Structure_Enhancer/data_structure_multidimensional_priority_queue_like_deletion_enabler_online.sublime-snippet)
- [ ] [Data structure priority queue like deletion enabler online](02_data_structures/29_data_structure_enhancer/data_structure_priority_queue_like_deletion_enabler_online.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Data_Structure_Enhancer/data_structure_priority_queue_like_deletion_enabler_online.sublime-snippet)
- [ ] [Data structure queue like deletion enabler online](02_data_structures/29_data_structure_enhancer/data_structure_queue_like_deletion_enabler_online.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Data_Structure_Enhancer/data_structure_queue_like_deletion_enabler_online.sublime-snippet)

### Unital Sorter

- [ ] [Unital sorter](02_data_structures/30_unital_sorter/unital_sorter.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Unital_Sorter/unital_sorter.sublime-snippet)

### Link Cut Trees

- [ ] [Link cut trees](02_data_structures/31_link_cut_trees/link_cut_trees.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Link_Cut_Trees/link_cut_trees.sublime-snippet)

### Cut Join Tree

- [ ] [Cut join tree](02_data_structures/32_cut_join_tree/cut_join_tree.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Cut_Join_Tree/cut_join_tree.sublime-snippet)

### Top Tree

- [ ] [Static top tree](02_data_structures/33_top_tree/static_top_tree.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/Top_Tree/static_top_tree.sublime-snippet)

### PQ Tree

- [ ] [PQ tree](02_data_structures/34_pq_tree/pq_tree.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Data_Structure/PQ_Tree/pq_tree.sublime-snippet)

## 3. Grid

Grid moves, BFS, and Dijkstra: graph search on the most common input shape.

- [ ] [Direction vectors](03_grid/direction_vectors.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Grid/direction_vectors.sublime-snippet)
- [ ] [Grid BFS forest](03_grid/grid_bfs_forest.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Grid/grid_bfs_forest.sublime-snippet)
- [ ] [Grid dijkstra](03_grid/grid_dijkstra.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Grid/grid_dijkstra.sublime-snippet)
- [ ] [Grid path](03_grid/grid_path.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Grid/grid_path.sublime-snippet)

## 4. Graph Theory

Shortest paths, spanning trees, connectivity, then trees (LCA, HLD, centroids), then special graphs.

- [ ] [Edge path into vertex path](04_graphs/edge_path_into_vertex_path.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/edge_path_into_vertex_path.sublime-snippet)
- [ ] [Find all cycle masks](04_graphs/find_all_cycle_masks.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/find_all_cycle_masks.sublime-snippet)
- [ ] [Graph](04_graphs/graph.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/graph.sublime-snippet)

### Shortest Path Algorithms

- [ ] [Successive shortest path solver](04_graphs/01_shortest_path_algorithms/successive_shortest_path_solver.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Shortest_Path_Algorithms/successive_shortest_path_solver.sublime-snippet)

### Shortest Path Algorithms / Bellman Ford

- [ ] [Bellman ford](04_graphs/01_shortest_path_algorithms/bellman_ford/bellman_ford.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Shortest_Path_Algorithms/Bellman_Ford/bellman_ford.sublime-snippet)

### Shortest Path Algorithms / Dial

- [ ] [Dial](04_graphs/01_shortest_path_algorithms/dial/dial.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Shortest_Path_Algorithms/Dial/dial.sublime-snippet)

### Shortest Path Algorithms / Dijkstra

- [ ] [Dijkstra](04_graphs/01_shortest_path_algorithms/dijkstra/dijkstra.h) (Python: [`Dijkstra.py`](https://github.com/lamng3/competitive-programming-notebook/blob/main/python/graphs/shortest_path/Dijkstra.py)) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Shortest_Path_Algorithms/Dijkstra/dijkstra.sublime-snippet)
- [ ] [Dijkstra dense](04_graphs/01_shortest_path_algorithms/dijkstra/dijkstra_dense.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Shortest_Path_Algorithms/Dijkstra/dijkstra_dense.sublime-snippet)

### Shortest Path Algorithms / Floyd Warshall

- [ ] [Floyd warshall](04_graphs/01_shortest_path_algorithms/floyd_warshall/floyd_warshall.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Shortest_Path_Algorithms/Floyd_Warshall/floyd_warshall.sublime-snippet)

### Shortest Path Algorithms / Minimum Mean Weight Cycle

- [ ] [Minimum mean weight cycle](04_graphs/01_shortest_path_algorithms/minimum_mean_weight_cycle/minimum_mean_weight_cycle.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Shortest_Path_Algorithms/Minimum_Mean_Weight_Cycle/minimum_mean_weight_cycle.sublime-snippet)

### Shortest Path Algorithms / Shortest Path Faster Algorithm

- [ ] [SPFA](04_graphs/01_shortest_path_algorithms/shortest_path_faster_algorithm/spfa.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Shortest_Path_Algorithms/Shortest_Path_Faster_Algorithm/spfa.sublime-snippet)

### Spanning Forest Algorithms

- [ ] [BFS forest](04_graphs/02_spanning_forest_algorithms/bfs_forest.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Spanning_Forest_Algorithms/bfs_forest.sublime-snippet)
- [ ] [Complement spanning forest](04_graphs/02_spanning_forest_algorithms/complement_spanning_forest.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Spanning_Forest_Algorithms/complement_spanning_forest.sublime-snippet)
- [ ] [Count spanning forest](04_graphs/02_spanning_forest_algorithms/count_spanning_forest.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Spanning_Forest_Algorithms/count_spanning_forest.sublime-snippet)
- [ ] [DFS forest](04_graphs/02_spanning_forest_algorithms/dfs_forest.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Spanning_Forest_Algorithms/dfs_forest.sublime-snippet)
- [ ] [Lexicographical BFS forest](04_graphs/02_spanning_forest_algorithms/lexicographical_bfs_forest.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Spanning_Forest_Algorithms/lexicographical_bfs_forest.sublime-snippet)
- [ ] [Minimum spanning arborescence](04_graphs/02_spanning_forest_algorithms/minimum_spanning_arborescence.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Spanning_Forest_Algorithms/minimum_spanning_arborescence.sublime-snippet)
- [ ] [Minimum spanning forest](04_graphs/02_spanning_forest_algorithms/minimum_spanning_forest.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Spanning_Forest_Algorithms/minimum_spanning_forest.sublime-snippet)
- [ ] [Minimum steiner tree](04_graphs/02_spanning_forest_algorithms/minimum_steiner_tree.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Spanning_Forest_Algorithms/minimum_steiner_tree.sublime-snippet)

### DFS Based

- [ ] [Find dominators](04_graphs/03_dfs_based/find_dominators.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/DFS_Based/find_dominators.sublime-snippet)
- [ ] [Greedy coloring](04_graphs/03_dfs_based/greedy_coloring.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/DFS_Based/greedy_coloring.sublime-snippet)
- [ ] [Reachable even cycle finder](04_graphs/03_dfs_based/reachable_even_cycle_finder.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/DFS_Based/reachable_even_cycle_finder.sublime-snippet)
- [ ] [Topological sorter](04_graphs/03_dfs_based/topological_sorter.h) (Python: [`TopoSort.py`](https://github.com/lamng3/competitive-programming-notebook/blob/main/python/graphs/topological_sort/TopoSort.py)) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/DFS_Based/topological_sorter.sublime-snippet)

### Connectivity

- [ ] [Biconnected components](04_graphs/04_connectivity/biconnected_components.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Connectivity/biconnected_components.sublime-snippet)
- [ ] [Bipolar orientation](04_graphs/04_connectivity/bipolar_orientation.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Connectivity/bipolar_orientation.sublime-snippet)
- [ ] [Ear decomposition](04_graphs/04_connectivity/ear_decomposition.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Connectivity/ear_decomposition.sublime-snippet)
- [ ] [Recover two sat](04_graphs/04_connectivity/recover_two_sat.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Connectivity/recover_two_sat.sublime-snippet)
- [ ] [Strong augmentation](04_graphs/04_connectivity/strong_augmentation.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Connectivity/strong_augmentation.sublime-snippet)
- [ ] [Strongly connected components](04_graphs/04_connectivity/strongly_connected_components.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Connectivity/strongly_connected_components.sublime-snippet)
- [ ] [Strongly connected components offline incremental](04_graphs/04_connectivity/strongly_connected_components_offline_incremental.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Connectivity/strongly_connected_components_offline_incremental.sublime-snippet)
- [ ] [Two sat solver](04_graphs/04_connectivity/two_sat_solver.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Connectivity/two_sat_solver.sublime-snippet)

### Euler Walk

- [ ] [Euler walk](04_graphs/05_euler_walk/euler_walk.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Euler_Walk/euler_walk.sublime-snippet)

### Forest Algorithms

- [ ] [Almost uniformly partitionable](04_graphs/06_forest_algorithms/almost_uniformly_partitionable.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Forest_Algorithms/almost_uniformly_partitionable.sublime-snippet)
- [ ] [Binary lifting](04_graphs/06_forest_algorithms/binary_lifting.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Forest_Algorithms/binary_lifting.sublime-snippet)
- [ ] [Centroid decomposition](04_graphs/06_forest_algorithms/centroid_decomposition.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Forest_Algorithms/centroid_decomposition.sublime-snippet)
- [ ] [Centroid processor](04_graphs/06_forest_algorithms/centroid_processor.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Forest_Algorithms/centroid_processor.sublime-snippet)
- [ ] [Compressed tree](04_graphs/06_forest_algorithms/compressed_tree.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Forest_Algorithms/compressed_tree.sublime-snippet)
- [ ] [Forest path query solver commutative group](04_graphs/06_forest_algorithms/forest_path_query_solver_commutative_group.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Forest_Algorithms/forest_path_query_solver_commutative_group.sublime-snippet)
- [ ] [Forest query solver](04_graphs/06_forest_algorithms/forest_query_solver.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Forest_Algorithms/forest_query_solver.sublime-snippet)
- [ ] [Heavy light decomposition](04_graphs/06_forest_algorithms/heavy_light_decomposition.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Forest_Algorithms/heavy_light_decomposition.sublime-snippet)
- [ ] [LCA solver](04_graphs/06_forest_algorithms/lca_solver.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Forest_Algorithms/lca_solver.sublime-snippet)
- [ ] [LCA solver offline](04_graphs/06_forest_algorithms/lca_solver_offline.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Forest_Algorithms/lca_solver_offline.sublime-snippet)
- [ ] [Precalc directional heights](04_graphs/06_forest_algorithms/precalc_directional_heights.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Forest_Algorithms/precalc_directional_heights.sublime-snippet)
- [ ] [Prufer code](04_graphs/06_forest_algorithms/prufer_code.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Forest_Algorithms/prufer_code.sublime-snippet)
- [ ] [Rerooter](04_graphs/06_forest_algorithms/rerooter.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Forest_Algorithms/rerooter.sublime-snippet)
- [ ] [Shallowest decomposition](04_graphs/06_forest_algorithms/shallowest_decomposition.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Forest_Algorithms/shallowest_decomposition.sublime-snippet)
- [ ] [Skew binary lifting](04_graphs/06_forest_algorithms/skew_binary_lifting.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Forest_Algorithms/skew_binary_lifting.sublime-snippet)
- [ ] [Small to large on forest](04_graphs/06_forest_algorithms/small_to_large_on_forest.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Forest_Algorithms/small_to_large_on_forest.sublime-snippet)
- [ ] [Static path minmax processor](04_graphs/06_forest_algorithms/static_path_minmax_processor.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Forest_Algorithms/static_path_minmax_processor.sublime-snippet)
- [ ] [Tree hasher](04_graphs/06_forest_algorithms/tree_hasher.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Forest_Algorithms/tree_hasher.sublime-snippet)
- [ ] [Weighted binary lifting](04_graphs/06_forest_algorithms/weighted_binary_lifting.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Forest_Algorithms/weighted_binary_lifting.sublime-snippet)

### Clique

- [ ] [Count cliques](04_graphs/07_clique/count_cliques.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Clique/count_cliques.sublime-snippet)
- [ ] [Count cliques weighted](04_graphs/07_clique/count_cliques_weighted.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Clique/count_cliques_weighted.sublime-snippet)
- [ ] [Enumerate maximal cliques](04_graphs/07_clique/enumerate_maximal_cliques.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Clique/enumerate_maximal_cliques.sublime-snippet)
- [ ] [Enumerate maximal cliques large](04_graphs/07_clique/enumerate_maximal_cliques_large.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Clique/enumerate_maximal_cliques_large.sublime-snippet)
- [ ] [Find a maximum clique](04_graphs/07_clique/find_a_maximum_clique.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Clique/find_a_maximum_clique.sublime-snippet)
- [ ] [Find a maximum clique large](04_graphs/07_clique/find_a_maximum_clique_large.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Clique/find_a_maximum_clique_large.sublime-snippet)

### Sqrt Trick

- [ ] [Count 4 cycles](04_graphs/08_sqrt_trick/count_4_cycles.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Sqrt_Trick/count_4_cycles.sublime-snippet)
- [ ] [Find 3 cycles](04_graphs/08_sqrt_trick/find_3_cycles.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Sqrt_Trick/find_3_cycles.sublime-snippet)
- [ ] [Find 4 cycles](04_graphs/08_sqrt_trick/find_4_cycles.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Sqrt_Trick/find_4_cycles.sublime-snippet)

### Special Graphs

- [ ] [Admissible graph](04_graphs/09_special_graphs/admissible_graph.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Special_Graphs/admissible_graph.sublime-snippet)
- [ ] [Find maximal cycles in tournament graphs](04_graphs/09_special_graphs/find_maximal_cycles_in_tournament_graphs.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Special_Graphs/find_maximal_cycles_in_tournament_graphs.sublime-snippet)
- [ ] [Functional graph processor](04_graphs/09_special_graphs/functional_graph_processor.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Special_Graphs/functional_graph_processor.sublime-snippet)
- [ ] [Maximum independent set on cactus](04_graphs/09_special_graphs/maximum_independent_set_on_cactus.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Special_Graphs/maximum_independent_set_on_cactus.sublime-snippet)
- [ ] [Recognize chordal graphs](04_graphs/09_special_graphs/recognize_chordal_graphs.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Special_Graphs/recognize_chordal_graphs.sublime-snippet)
- [ ] [Recognize cographs](04_graphs/09_special_graphs/recognize_cographs.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Special_Graphs/recognize_cographs.sublime-snippet)

### Graph Decomposition

- [ ] [Decompose into paths of length 2](04_graphs/10_graph_decomposition/decompose_into_paths_of_length_2.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Graph_Decomposition/decompose_into_paths_of_length_2.sublime-snippet)

### Chromatic Polynomial

- [ ] [Chromatic polynomial functional graph](04_graphs/11_chromatic_polynomial/chromatic_polynomial_functional_graph.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Chromatic_Polynomial/chromatic_polynomial_functional_graph.sublime-snippet)

### Tree Decomposition

- [ ] [Is tree decomposition of](04_graphs/12_tree_decomposition/is_tree_decomposition_of.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Tree_Decomposition/is_tree_decomposition_of.sublime-snippet)
- [ ] [Maximum independent set on tree decomposition](04_graphs/12_tree_decomposition/maximum_independent_set_on_tree_decomposition.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Tree_Decomposition/maximum_independent_set_on_tree_decomposition.sublime-snippet)
- [ ] [Tree decomposition cactus halin graph](04_graphs/12_tree_decomposition/tree_decomposition_cactus_halin_graph.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Tree_Decomposition/tree_decomposition_cactus_halin_graph.sublime-snippet)
- [ ] [Tree decomposition chordal graph](04_graphs/12_tree_decomposition/tree_decomposition_chordal_graph.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Tree_Decomposition/tree_decomposition_chordal_graph.sublime-snippet)
- [ ] [Tree decomposition halin graph](04_graphs/12_tree_decomposition/tree_decomposition_halin_graph.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Graph_Theory/Tree_Decomposition/tree_decomposition_halin_graph.sublime-snippet)

## 5. Dynamic Programming

Knapsack, then the optimizations: divide and conquer, Knuth, monotone queue, SMAWK, Lagrange.

### Knapsack

- [ ] [Knapsack optimizer](05_dynamic_programming/01_knapsack/knapsack_optimizer.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Dynamic_Programming/Knapsack/knapsack_optimizer.sublime-snippet)
- [ ] [Subset sum optimizer](05_dynamic_programming/01_knapsack/subset_sum_optimizer.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Dynamic_Programming/Knapsack/subset_sum_optimizer.sublime-snippet)
- [ ] [Subset sum processor](05_dynamic_programming/01_knapsack/subset_sum_processor.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Dynamic_Programming/Knapsack/subset_sum_processor.sublime-snippet)

- [ ] [Count rectangles within grid](05_dynamic_programming/count_rectangles_within_grid.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Dynamic_Programming/count_rectangles_within_grid.sublime-snippet)
- [ ] [Divide and conquer optimization](05_dynamic_programming/divide_and_conquer_optimization.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Dynamic_Programming/divide_and_conquer_optimization.sublime-snippet)
- [ ] [Knuth optimization](05_dynamic_programming/knuth_optimization.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Dynamic_Programming/knuth_optimization.sublime-snippet)
- [ ] [Lagrange optimization](05_dynamic_programming/lagrange_optimization.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Dynamic_Programming/lagrange_optimization.sublime-snippet)
- [ ] [Monotone queue optimization](05_dynamic_programming/monotone_queue_optimization.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Dynamic_Programming/monotone_queue_optimization.sublime-snippet)
- [ ] [Smawk](05_dynamic_programming/smawk.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Dynamic_Programming/smawk.sublime-snippet)
- [ ] [Span with subarray](05_dynamic_programming/span_with_subarray.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Dynamic_Programming/span_with_subarray.sublime-snippet)

## 6. String

Hashing and tries, then prefix structures (suffix array, automata), then palindromes and Lyndon words.

### Hash

- [x] Hash — ours: [`rollinghash.h`](https://github.com/lamng3/competitive-programming-notebook/blob/main/notebook/strings/rolling_hash/rollinghash.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Hash/hash.sublime-snippet)
- [ ] [Hash bidirectional](06_strings/01_hash/hash_bidirectional.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Hash/hash_bidirectional.sublime-snippet)
- [ ] [Substring hasher](06_strings/01_hash/substring_hasher.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Hash/substring_hasher.sublime-snippet)

### Trie

- [ ] [Binary trie](06_strings/02_trie/binary_trie.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Trie/binary_trie.sublime-snippet)
- [ ] [Trie](06_strings/02_trie/trie.h) (Python: [`Trie.py`](https://github.com/lamng3/competitive-programming-notebook/blob/main/python/strings/trie/Trie.py)) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Trie/trie.sublime-snippet)

### Longest Common Subsequence

- [ ] [Circular longest common subsequence](06_strings/03_longest_common_subsequence/circular_longest_common_subsequence.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Longest_Common_Subsequence/circular_longest_common_subsequence.sublime-snippet)
- [ ] [Longest common subsequence](06_strings/03_longest_common_subsequence/longest_common_subsequence.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Longest_Common_Subsequence/longest_common_subsequence.sublime-snippet)
- [ ] [Longest common subsequence lengths](06_strings/03_longest_common_subsequence/longest_common_subsequence_lengths.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Longest_Common_Subsequence/longest_common_subsequence_lengths.sublime-snippet)

### Manacher

- [ ] [Manacher](06_strings/04_manacher/manacher.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Manacher/manacher.sublime-snippet)

### Suffix Array

- [ ] [Suffix array](06_strings/05_suffix_array/suffix_array.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Suffix_Array/suffix_array.sublime-snippet)
- [ ] [Suffix array slow](06_strings/05_suffix_array/suffix_array_slow.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Suffix_Array/suffix_array_slow.sublime-snippet)

### Suffix Automaton

- [ ] [Suffix automaton](06_strings/06_suffix_automaton/suffix_automaton.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Suffix_Automaton/suffix_automaton.sublime-snippet)

### Suffix Tree

- [ ] [Suffix tree](06_strings/07_suffix_tree/suffix_tree.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Suffix_Tree/suffix_tree.sublime-snippet)

### Aho Corasic Automaton

- [ ] [Aho corasic automaton fixed](06_strings/08_aho_corasic_automaton/aho_corasic_automaton_fixed.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Aho_Corasic_Automaton/aho_corasic_automaton_fixed.sublime-snippet)
- [ ] [Aho corasic automaton unfixed](06_strings/08_aho_corasic_automaton/aho_corasic_automaton_unfixed.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Aho_Corasic_Automaton/aho_corasic_automaton_unfixed.sublime-snippet)

### Palindrome Automaton

- [ ] [Palindrome automaton](06_strings/09_palindrome_automaton/palindrome_automaton.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Palindrome_Automaton/palindrome_automaton.sublime-snippet)

### Lyndon

- [ ] [Lyndon factorization](06_strings/10_lyndon/lyndon_factorization.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Lyndon/lyndon_factorization.sublime-snippet)
- [ ] [Minimal rotation](06_strings/10_lyndon/minimal_rotation.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Lyndon/minimal_rotation.sublime-snippet)

### Main Lorentz

- [ ] [Main lorentz](06_strings/11_main_lorentz/main_lorentz.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Main_Lorentz/main_lorentz.sublime-snippet)

### Matching With Wildcards

- [ ] [Matching with wildcards](06_strings/12_matching_with_wildcards/matching_with_wildcards.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Matching_With_Wildcards/matching_with_wildcards.sublime-snippet)
- [ ] [Matching with wildcards randomized](06_strings/12_matching_with_wildcards/matching_with_wildcards_randomized.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Matching_With_Wildcards/matching_with_wildcards_randomized.sublime-snippet)

### Burrows Wheeler Transform

- [ ] [Burrows wheeler transform](06_strings/13_burrows_wheeler_transform/burrows_wheeler_transform.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Burrows_Wheeler_Transform/burrows_wheeler_transform.sublime-snippet)

### Finite Automaton

- [ ] [Deterministic finite automaton](06_strings/14_finite_automaton/deterministic_finite_automaton.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Finite_Automaton/deterministic_finite_automaton.sublime-snippet)

### Autocorrelation

- [ ] [Autocorrelation free variable count](06_strings/15_autocorrelation/autocorrelation_free_variable_count.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Autocorrelation/autocorrelation_free_variable_count.sublime-snippet)
- [ ] [Autocorrelation membership test](06_strings/15_autocorrelation/autocorrelation_membership_test.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Autocorrelation/autocorrelation_membership_test.sublime-snippet)
- [ ] [Autocorrelation to string](06_strings/15_autocorrelation/autocorrelation_to_string.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Autocorrelation/autocorrelation_to_string.sublime-snippet)
- [ ] [Enumerate autocorrelations](06_strings/15_autocorrelation/enumerate_autocorrelations.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Autocorrelation/enumerate_autocorrelations.sublime-snippet)
- [ ] [String to autocorrelation](06_strings/15_autocorrelation/string_to_autocorrelation.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Autocorrelation/string_to_autocorrelation.sublime-snippet)

### Composite String Comparator

- [ ] [Composite string comparator](06_strings/16_composite_string_comparator/composite_string_comparator.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Composite_String_Comparator/composite_string_comparator.sublime-snippet)

### String Processor

- [ ] [String processor](06_strings/17_string_processor/string_processor.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/String_Processor/string_processor.sublime-snippet)

### Utility

- [ ] [Count common substrings](06_strings/18_utility/count_common_substrings.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Utility/count_common_substrings.sublime-snippet)
- [ ] [Count distinct substrings](06_strings/18_utility/count_distinct_substrings.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Utility/count_distinct_substrings.sublime-snippet)
- [ ] [Distinct substring count query solver offline](06_strings/18_utility/distinct_substring_count_query_solver_offline.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Utility/distinct_substring_count_query_solver_offline.sublime-snippet)
- [ ] [Longest common substring](06_strings/18_utility/longest_common_substring.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/String/Utility/longest_common_substring.sublime-snippet)

## 7. Number Theory

Modular arithmetic, Euclid and CRT, factorization, then multiplicative prefix sums.

- [ ] [Barret reduction](07_number_theory/barret_reduction.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/barret_reduction.sublime-snippet)
- [ ] [Diophantine](07_number_theory/diophantine.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/diophantine.sublime-snippet)
- [ ] [Dirichlet convolution formulae](07_number_theory/dirichlet_convolution_formulae.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/dirichlet_convolution_formulae.sublime-snippet)
- [ ] [Divisor count function prefix sum](07_number_theory/divisor_count_function_prefix_sum.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/divisor_count_function_prefix_sum.sublime-snippet)
- [ ] [Divisor processor](07_number_theory/divisor_processor.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/divisor_processor.sublime-snippet)
- [ ] [Extended euclidean](07_number_theory/extended_euclidean.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/extended_euclidean.sublime-snippet)
- [ ] [Factorize](07_number_theory/factorize.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/factorize.sublime-snippet)
- [ ] [Find first residue](07_number_theory/find_first_residue.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/find_first_residue.sublime-snippet)
- [ ] [Floor sum](07_number_theory/floor_sum.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/floor_sum.sublime-snippet)
- [ ] [Floor sum weighted](07_number_theory/floor_sum_weighted.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/floor_sum_weighted.sublime-snippet)
- [ ] [Harmonic loop](07_number_theory/harmonic_loop.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/harmonic_loop.sublime-snippet)
- [ ] [Inverse linear congruential generator](07_number_theory/inverse_linear_congruential_generator.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/inverse_linear_congruential_generator.sublime-snippet)
- [ ] [Jacobi symbol](07_number_theory/jacobi_symbol.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/jacobi_symbol.sublime-snippet)
- [ ] [Number theory](07_number_theory/number_theory.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/number_theory.sublime-snippet)
- [ ] [Pollard rho](07_number_theory/pollard_rho.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/pollard_rho.sublime-snippet)
- [ ] [Solve EGZ](07_number_theory/solve_egz.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/solve_EGZ.sublime-snippet)

### Modular

- [ ] [Mod sqrt](07_number_theory/01_modular/mod_sqrt.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/Modular/mod_sqrt.sublime-snippet)
- [ ] [Modular fixed](07_number_theory/01_modular/modular_fixed.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/Modular/modular_fixed.sublime-snippet)
- [ ] [Modular unfixed](07_number_theory/01_modular/modular_unfixed.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/Modular/modular_unfixed.sublime-snippet)
- [ ] [Montgomery modular fixed](07_number_theory/01_modular/montgomery_modular_fixed.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/Modular/montgomery_modular_fixed.sublime-snippet)
- [ ] [Montgomery modular unfixed](07_number_theory/01_modular/montgomery_modular_unfixed.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/Modular/montgomery_modular_unfixed.sublime-snippet)

### Chinese Remainder Theorem

- [ ] [Chinese remainder theorem coprime fixed width](07_number_theory/02_chinese_remainder_theorem/chinese_remainder_theorem_coprime_fixed_width.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/Chinese_Remainder_Theorem/chinese_remainder_theorem_coprime_fixed_width.sublime-snippet)
- [ ] [Chinese remainder theorem linear](07_number_theory/02_chinese_remainder_theorem/chinese_remainder_theorem_linear.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/Chinese_Remainder_Theorem/chinese_remainder_theorem_linear.sublime-snippet)

### Integer Decomposition

- [ ] [Solve fermat three triangle](07_number_theory/03_integer_decomposition/solve_fermat_three_triangle.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/Integer_Decomposition/solve_fermat_three_triangle.sublime-snippet)
- [ ] [Solve fermat two square](07_number_theory/03_integer_decomposition/solve_fermat_two_square.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/Integer_Decomposition/solve_fermat_two_square.sublime-snippet)
- [ ] [Solve lagrange four square](07_number_theory/03_integer_decomposition/solve_lagrange_four_square.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/Integer_Decomposition/solve_lagrange_four_square.sublime-snippet)
- [ ] [Solve legendre three square](07_number_theory/03_integer_decomposition/solve_legendre_three_square.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/Integer_Decomposition/solve_legendre_three_square.sublime-snippet)

### Multiplicative Prefix Sum

- [ ] [Count primes](07_number_theory/04_multiplicative_prefix_sum/count_primes.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/Multiplicative_Prefix_Sum/count_primes.sublime-snippet)
- [ ] [Meissel lehmer](07_number_theory/04_multiplicative_prefix_sum/meissel_lehmer.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/Multiplicative_Prefix_Sum/meissel_lehmer.sublime-snippet)
- [ ] [Min25 sieve](07_number_theory/04_multiplicative_prefix_sum/min25_sieve.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/Multiplicative_Prefix_Sum/min25_sieve.sublime-snippet)
- [ ] [Min25 sieve wrong](07_number_theory/04_multiplicative_prefix_sum/min25_sieve_wrong.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/Multiplicative_Prefix_Sum/min25_sieve_wrong.sublime-snippet)
- [ ] [Xudyh sieve](07_number_theory/04_multiplicative_prefix_sum/xudyh_sieve.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Number_Theory/Multiplicative_Prefix_Sum/xudyh_sieve.sublime-snippet)

## 8. Continued Fraction and Farey Sequence

Best rational approximations: a short follow-on to number theory.

- [ ] [Continued fraction](08_number_theory_continued_fractions/continued_fraction.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Continued_Fraction_and_Farey_Sequence/continued_fraction.sublime-snippet)
- [ ] [Farey sequence](08_number_theory_continued_fractions/farey_sequence.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Continued_Fraction_and_Farey_Sequence/farey_sequence.sublime-snippet)

## 9. Combinatorial

Counting, LIS, permutations, then flows and matchings, matroids, and Young tableaux.

- [ ] [Bidirectional ballot sequence count](09_combinatorics/bidirectional_ballot_sequence_count.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/bidirectional_ballot_sequence_count.sublime-snippet)
- [ ] [Combinatorics](09_combinatorics/combinatorics.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/combinatorics.sublime-snippet)
- [ ] [Compute sum of non intersecting tuples of paths](09_combinatorics/compute_sum_of_non_intersecting_tuples_of_paths.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/compute_sum_of_non_intersecting_tuples_of_paths.sublime-snippet)
- [ ] [Enumerate partitions](09_combinatorics/enumerate_partitions.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/enumerate_partitions.sublime-snippet)
- [ ] [Enumerate polyominos](09_combinatorics/enumerate_polyominos.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/enumerate_polyominos.sublime-snippet)
- [ ] [Q combinatorics](09_combinatorics/q_combinatorics.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/q_combinatorics.sublime-snippet)

### Permutation

- [ ] [Count inversions](09_combinatorics/01_permutation/count_inversions.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Permutation/count_inversions.sublime-snippet)
- [ ] [Permutation](09_combinatorics/01_permutation/permutation.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Permutation/permutation.sublime-snippet)

### Longest Monotone Subsequence

- [ ] [Longest increasing bisubsequence](09_combinatorics/02_longest_monotone_subsequence/longest_increasing_bisubsequence.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Longest_Monotone_Subsequence/longest_increasing_bisubsequence.sublime-snippet)
- [ ] [Longest increasing subsequence](09_combinatorics/02_longest_monotone_subsequence/longest_increasing_subsequence.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Longest_Monotone_Subsequence/longest_increasing_subsequence.sublime-snippet)
- [ ] [Longest increasing subsequence processor](09_combinatorics/02_longest_monotone_subsequence/longest_increasing_subsequence_processor.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Longest_Monotone_Subsequence/longest_increasing_subsequence_processor.sublime-snippet)

### Flow Matching And Cut

- [ ] [Blossom maximum unweighted matching](09_combinatorics/03_flow_matching_and_cut/blossom_maximum_unweighted_matching.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Flow_Matching_And_Cut/blossom_maximum_unweighted_matching.sublime-snippet)
- [ ] [Dinic maximum flow](09_combinatorics/03_flow_matching_and_cut/dinic_maximum_flow.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Flow_Matching_And_Cut/dinic_maximum_flow.sublime-snippet)
- [ ] [Flow decomposition](09_combinatorics/03_flow_matching_and_cut/flow_decomposition.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Flow_Matching_And_Cut/flow_decomposition.sublime-snippet)
- [ ] [Global min cut](09_combinatorics/03_flow_matching_and_cut/global_min_cut.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Flow_Matching_And_Cut/global_min_cut.sublime-snippet)
- [ ] [Gomory hu](09_combinatorics/03_flow_matching_and_cut/gomory_hu.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Flow_Matching_And_Cut/gomory_hu.sublime-snippet)
- [ ] [Hopcroft karp algorithm](09_combinatorics/03_flow_matching_and_cut/hopcroft_karp_algorithm.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Flow_Matching_And_Cut/hopcroft_karp_algorithm.sublime-snippet)
- [ ] [Hungarian weighted bipartite matching](09_combinatorics/03_flow_matching_and_cut/hungarian_weighted_bipartite_matching.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Flow_Matching_And_Cut/hungarian_weighted_bipartite_matching.sublime-snippet)
- [ ] [Kuhn algorithm](09_combinatorics/03_flow_matching_and_cut/kuhn_algorithm.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Flow_Matching_And_Cut/kuhn_algorithm.sublime-snippet)
- [ ] [Maximum antichain](09_combinatorics/03_flow_matching_and_cut/maximum_antichain.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Flow_Matching_And_Cut/maximum_antichain.sublime-snippet)
- [ ] [Maximum density subset](09_combinatorics/03_flow_matching_and_cut/maximum_density_subset.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Flow_Matching_And_Cut/maximum_density_subset.sublime-snippet)
- [ ] [Maximum weight matching](09_combinatorics/03_flow_matching_and_cut/maximum_weight_matching.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Flow_Matching_And_Cut/maximum_weight_matching.sublime-snippet)
- [ ] [Maximum weight matching short](09_combinatorics/03_flow_matching_and_cut/maximum_weight_matching_short.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Flow_Matching_And_Cut/maximum_weight_matching_short.sublime-snippet)
- [ ] [Minimum path cover](09_combinatorics/03_flow_matching_and_cut/minimum_path_cover.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Flow_Matching_And_Cut/minimum_path_cover.sublime-snippet)
- [ ] [Network simplex](09_combinatorics/03_flow_matching_and_cut/network_simplex.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Flow_Matching_And_Cut/network_simplex.sublime-snippet)
- [ ] [Positive bipartite two sat](09_combinatorics/03_flow_matching_and_cut/positive_bipartite_two_sat.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Flow_Matching_And_Cut/positive_bipartite_two_sat.sublime-snippet)
- [ ] [Push relabel](09_combinatorics/03_flow_matching_and_cut/push_relabel.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Flow_Matching_And_Cut/push_relabel.sublime-snippet)
- [ ] [Spanning tree polytope separation oracle](09_combinatorics/03_flow_matching_and_cut/spanning_tree_polytope_separation_oracle.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Flow_Matching_And_Cut/spanning_tree_polytope_separation_oracle.sublime-snippet)

### Flow Matching And Cut / Minimum Cost Maximum Flow

- [ ] [Minimum cost maximum flow johnson](09_combinatorics/03_flow_matching_and_cut/minimum_cost_maximum_flow/minimum_cost_maximum_flow_johnson.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Flow_Matching_And_Cut/Minimum_Cost_Maximum_Flow/minimum_cost_maximum_flow_johnson.sublime-snippet)
- [ ] [Minimum cost maximum flow push relabel](09_combinatorics/03_flow_matching_and_cut/minimum_cost_maximum_flow/minimum_cost_maximum_flow_push_relabel.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Flow_Matching_And_Cut/Minimum_Cost_Maximum_Flow/minimum_cost_maximum_flow_push_relabel.sublime-snippet)
- [ ] [Minimum cost maximum flow SPFA](09_combinatorics/03_flow_matching_and_cut/minimum_cost_maximum_flow/minimum_cost_maximum_flow_spfa.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Flow_Matching_And_Cut/Minimum_Cost_Maximum_Flow/minimum_cost_maximum_flow_spfa.sublime-snippet)

### Flow Matching And Cut / Fundamentals

- [ ] [Flow network](09_combinatorics/03_flow_matching_and_cut/fundamentals/flow_network.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Flow_Matching_And_Cut/_Fundamentals/flow_network.sublime-snippet)
- [ ] [Flow network weighted](09_combinatorics/03_flow_matching_and_cut/fundamentals/flow_network_weighted.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Flow_Matching_And_Cut/_Fundamentals/flow_network_weighted.sublime-snippet)
- [ ] [Flow network with demand](09_combinatorics/03_flow_matching_and_cut/fundamentals/flow_network_with_demand.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Flow_Matching_And_Cut/_Fundamentals/flow_network_with_demand.sublime-snippet)
- [ ] [Maximum bipartite matching solver](09_combinatorics/03_flow_matching_and_cut/fundamentals/maximum_bipartite_matching_solver.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Flow_Matching_And_Cut/_Fundamentals/maximum_bipartite_matching_solver.sublime-snippet)

### Linear Programming

- [ ] [Linear programming solver simplex](09_combinatorics/04_linear_programming/linear_programming_solver_simplex.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Linear_Programming/linear_programming_solver_simplex.sublime-snippet)

### Matroid

- [ ] [Matroid intersection](09_combinatorics/05_matroid/matroid_intersection.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Matroid/matroid_intersection.sublime-snippet)
- [ ] [Matroid intersection weighted bellman ford](09_combinatorics/05_matroid/matroid_intersection_weighted_bellman_ford.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Matroid/matroid_intersection_weighted_bellman_ford.sublime-snippet)
- [ ] [Matroid intersection weighted SPFA](09_combinatorics/05_matroid/matroid_intersection_weighted_spfa.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Matroid/matroid_intersection_weighted_spfa.sublime-snippet)

### Matroid / Matroid Generators

- [ ] [GF2 linear matroid](09_combinatorics/05_matroid/matroid_generators/gf2_linear_matroid.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Matroid/Matroid_Generators/GF2_linear_matroid.sublime-snippet)
- [ ] [Colorful matroid](09_combinatorics/05_matroid/matroid_generators/colorful_matroid.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Matroid/Matroid_Generators/colorful_matroid.sublime-snippet)
- [ ] [Graphic matroid](09_combinatorics/05_matroid/matroid_generators/graphic_matroid.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Matroid/Matroid_Generators/graphic_matroid.sublime-snippet)
- [ ] [Partition matroid](09_combinatorics/05_matroid/matroid_generators/partition_matroid.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Matroid/Matroid_Generators/partition_matroid.sublime-snippet)
- [ ] [Rigidity matroid](09_combinatorics/05_matroid/matroid_generators/rigidity_matroid.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Matroid/Matroid_Generators/rigidity_matroid.sublime-snippet)

### Submodularity

- [ ] [Check antisubmodularity](09_combinatorics/06_submodularity/check_antisubmodularity.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Submodularity/check_antisubmodularity.sublime-snippet)
- [ ] [Graph representable monge function optimization](09_combinatorics/06_submodularity/graph_representable_monge_function_optimization.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Submodularity/graph_representable_monge_function_optimization.sublime-snippet)
- [ ] [Graph representable submodular function optimization](09_combinatorics/06_submodularity/graph_representable_submodular_function_optimization.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Submodularity/graph_representable_submodular_function_optimization.sublime-snippet)

### Young Tableau

- [ ] [RSK inverse mapping](09_combinatorics/07_young_tableau/rsk_inverse_mapping.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Young_Tableau/RSK_inverse_mapping.sublime-snippet)
- [ ] [RSK mapping](09_combinatorics/07_young_tableau/rsk_mapping.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Young_Tableau/RSK_mapping.sublime-snippet)
- [ ] [RSK mapping fast](09_combinatorics/07_young_tableau/rsk_mapping_fast.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Young_Tableau/RSK_mapping_fast.sublime-snippet)
- [ ] [Count young tableaux](09_combinatorics/07_young_tableau/count_young_tableaux.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Young_Tableau/count_young_tableaux.sublime-snippet)
- [ ] [Longest k increasing subsequence nk log n nk²](09_combinatorics/07_young_tableau/longest_k_increasing_subsequence_nklogn_nk2.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Young_Tableau/longest_k_increasing_subsequence_nklogn_nk2.sublime-snippet)
- [ ] [Longest k increasing subsequence nr](09_combinatorics/07_young_tableau/longest_k_increasing_subsequence_nr.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Young_Tableau/longest_k_increasing_subsequence_nr.sublime-snippet)

### Block Minmax Processor

- [ ] [Block minmax processor](09_combinatorics/08_block_minmax_processor/block_minmax_processor.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Block_Minmax_Processor/block_minmax_processor.sublime-snippet)
- [ ] [Block minmax processor 2D](09_combinatorics/08_block_minmax_processor/block_minmax_processor_2d.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Block_Minmax_Processor/block_minmax_processor_2d.sublime-snippet)

### Edge Coloring

- [ ] [Edge coloring bipartite](09_combinatorics/09_edge_coloring/edge_coloring_bipartite.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Edge_Coloring/edge_coloring_bipartite.sublime-snippet)
- [ ] [Edge coloring vizing](09_combinatorics/09_edge_coloring/edge_coloring_vizing.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Combinatorial/Edge_Coloring/edge_coloring_vizing.sublime-snippet)

## 10. Linear Algebra

Matrices, Gaussian elimination (also over GF2), and linear recurrences.

### Matrix

- [ ] [Characteristic polynomial](10_linear_algebra/01_matrix/characteristic_polynomial.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Linear_Algebra/Matrix/characteristic_polynomial.sublime-snippet)
- [ ] [Characteristic polynomial commutative ring](10_linear_algebra/01_matrix/characteristic_polynomial_commutative_ring.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Linear_Algebra/Matrix/characteristic_polynomial_commutative_ring.sublime-snippet)
- [ ] [Determinant commutative ring](10_linear_algebra/01_matrix/determinant_commutative_ring.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Linear_Algebra/Matrix/determinant_commutative_ring.sublime-snippet)
- [ ] [Determinant linear polynomial](10_linear_algebra/01_matrix/determinant_linear_polynomial.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Linear_Algebra/Matrix/determinant_linear_polynomial.sublime-snippet)
- [ ] [Determinant polynomial](10_linear_algebra/01_matrix/determinant_polynomial.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Linear_Algebra/Matrix/determinant_polynomial.sublime-snippet)
- [ ] [Matrix](10_linear_algebra/01_matrix/matrix.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Linear_Algebra/Matrix/matrix.sublime-snippet)
- [ ] [Matrix AND OR base](10_linear_algebra/01_matrix/matrix_and_or_base.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Linear_Algebra/Matrix/matrix_AND_OR_base.sublime-snippet)
- [ ] [Matrix OR AND](10_linear_algebra/01_matrix/matrix_or_and.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Linear_Algebra/Matrix/matrix_OR_AND.sublime-snippet)
- [ ] [Matrix Z2](10_linear_algebra/01_matrix/matrix_z2.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Linear_Algebra/Matrix/matrix_Z2.sublime-snippet)
- [ ] [Matrix fixed](10_linear_algebra/01_matrix/matrix_fixed.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Linear_Algebra/Matrix/matrix_fixed.sublime-snippet)
- [ ] [Matrix inverse tracker](10_linear_algebra/01_matrix/matrix_inverse_tracker.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Linear_Algebra/Matrix/matrix_inverse_tracker.sublime-snippet)
- [ ] [Sparse determinant](10_linear_algebra/01_matrix/sparse_determinant.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Linear_Algebra/Matrix/sparse_determinant.sublime-snippet)
- [ ] [Sparse minimal polynomial](10_linear_algebra/01_matrix/sparse_minimal_polynomial.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Linear_Algebra/Matrix/sparse_minimal_polynomial.sublime-snippet)
- [ ] [Tridiagonal matrix determinant](10_linear_algebra/01_matrix/tridiagonal_matrix_determinant.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Linear_Algebra/Matrix/tridiagonal_matrix_determinant.sublime-snippet)
- [ ] [Tridiagonal matrix equation solver](10_linear_algebra/01_matrix/tridiagonal_matrix_equation_solver.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Linear_Algebra/Matrix/tridiagonal_matrix_equation_solver.sublime-snippet)

### Linear Equation Solver

- [ ] [Linear equation solver](10_linear_algebra/02_linear_equation_solver/linear_equation_solver.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Linear_Algebra/Linear_Equation_Solver/linear_equation_solver.sublime-snippet)
- [ ] [Linear equation solver GF2](10_linear_algebra/02_linear_equation_solver/linear_equation_solver_gf2.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Linear_Algebra/Linear_Equation_Solver/linear_equation_solver_GF2.sublime-snippet)
- [ ] [Pick subset with given xor](10_linear_algebra/02_linear_equation_solver/pick_subset_with_given_xor.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Linear_Algebra/Linear_Equation_Solver/pick_subset_with_given_xor.sublime-snippet)

### Linear Recurrence Solver

- [ ] [Fibonacci](10_linear_algebra/03_linear_recurrence_solver/fibonacci.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Linear_Algebra/Linear_Recurrence_Solver/fibonacci.sublime-snippet)
- [ ] [Linear recurrence solver](10_linear_algebra/03_linear_recurrence_solver/linear_recurrence_solver.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Linear_Algebra/Linear_Recurrence_Solver/linear_recurrence_solver.sublime-snippet)
- [ ] [Linear recurrence solver bostan mori](10_linear_algebra/03_linear_recurrence_solver/linear_recurrence_solver_bostan_mori.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Linear_Algebra/Linear_Recurrence_Solver/linear_recurrence_solver_bostan_mori.sublime-snippet)
- [ ] [Linear recurrence solver modular exponentiation](10_linear_algebra/03_linear_recurrence_solver/linear_recurrence_solver_modular_exponentiation.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Linear_Algebra/Linear_Recurrence_Solver/linear_recurrence_solver_modular_exponentiation.sublime-snippet)

## 11. Power Series

FFT and NTT first; everything else in this section multiplies polynomials with them.

### Transformations

- [ ] [Chirp z transform](11_power_series/01_transformations/chirp_z_transform.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/Transformations/chirp_z_transform.sublime-snippet)
- [ ] [Fast fourier transform](11_power_series/01_transformations/fast_fourier_transform.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/Transformations/fast_fourier_transform.sublime-snippet)
- [ ] [Fast fourier transform multidimensional](11_power_series/01_transformations/fast_fourier_transform_multidimensional.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/Transformations/fast_fourier_transform_multidimensional.sublime-snippet)
- [ ] [Number theoric transform](11_power_series/01_transformations/number_theoric_transform.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/Transformations/number_theoric_transform.sublime-snippet)

- [ ] [Chebyshev eval](11_power_series/chebyshev_eval.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/chebyshev_eval.sublime-snippet)
- [ ] [Interpolate range naive](11_power_series/interpolate_range_naive.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/interpolate_range_naive.sublime-snippet)
- [ ] [Polynomial shift sampling](11_power_series/polynomial_shift_sampling.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/polynomial_shift_sampling.sublime-snippet)
- [ ] [Power series](11_power_series/power_series.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/power_series.sublime-snippet)
- [ ] [Power series composition](11_power_series/power_series_composition.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/power_series_composition.sublime-snippet)
- [ ] [Power series compositional inverse](11_power_series/power_series_compositional_inverse.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/power_series_compositional_inverse.sublime-snippet)
- [ ] [Power series naive](11_power_series/power_series_naive.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/power_series_naive.sublime-snippet)
- [ ] [Power series online](11_power_series/power_series_online.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/power_series_online.sublime-snippet)
- [ ] [Power series sqrt](11_power_series/power_series_sqrt.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/power_series_sqrt.sublime-snippet)
- [ ] [Rational polynomial single term extraction](11_power_series/rational_polynomial_single_term_extraction.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/rational_polynomial_single_term_extraction.sublime-snippet)
- [ ] [Reduce quadratic GF2 polynomial](11_power_series/reduce_quadratic_gf2_polynomial.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/reduce_quadratic_GF2_polynomial.sublime-snippet)
- [ ] [Sequential polynomial](11_power_series/sequential_polynomial.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/sequential_polynomial.sublime-snippet)
- [ ] [Subproduct tree](11_power_series/subproduct_tree.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/subproduct_tree.sublime-snippet)
- [ ] [Taylor shift](11_power_series/taylor_shift.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/taylor_shift.sublime-snippet)
- [ ] [Touchard polynomial](11_power_series/touchard_polynomial.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/touchard_polynomial.sublime-snippet)

### Convolutions

- [ ] [Convolve subset](11_power_series/02_convolutions/convolve_subset.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/Convolutions/convolve_subset.sublime-snippet)

### Power Sum

- [ ] [Bernoulli number](11_power_series/03_power_sum/bernoulli_number.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/Power_Sum/bernoulli_number.sublime-snippet)
- [ ] [Power sum](11_power_series/03_power_sum/power_sum.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/Power_Sum/power_sum.sublime-snippet)
- [ ] [Power sum prefix evaluation](11_power_series/03_power_sum/power_sum_prefix_evaluation.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/Power_Sum/power_sum_prefix_evaluation.sublime-snippet)

### Bell Number

- [ ] [Bell number](11_power_series/04_bell_number/bell_number.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/Bell_Number/bell_number.sublime-snippet)

### Set Power Series

- [ ] [Exponential set power series](11_power_series/05_set_power_series/exponential_set_power_series.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/Set_Power_Series/exponential_set_power_series.sublime-snippet)
- [ ] [Logarithm set power series](11_power_series/05_set_power_series/logarithm_set_power_series.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Power_Series/Set_Power_Series/logarithm_set_power_series.sublime-snippet)

## 12. Abstract Algebra

Groups, rings, and finite fields: the structures behind modular arithmetic and hashing.

- [ ] [Cosets](12_abstract_algebra/cosets.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Abstract_Algebra/cosets.sublime-snippet)
- [ ] [Division ring](12_abstract_algebra/division_ring.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Abstract_Algebra/division_ring.sublime-snippet)
- [ ] [Elliptic curve](12_abstract_algebra/elliptic_curve.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Abstract_Algebra/elliptic_curve.sublime-snippet)
- [ ] [Field of fraction](12_abstract_algebra/field_of_fraction.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Abstract_Algebra/field_of_fraction.sublime-snippet)
- [ ] [Find a commutative group basis](12_abstract_algebra/find_a_commutative_group_basis.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Abstract_Algebra/find_a_commutative_group_basis.sublime-snippet)
- [ ] [Find the order of all group elements](12_abstract_algebra/find_the_order_of_all_group_elements.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Abstract_Algebra/find_the_order_of_all_group_elements.sublime-snippet)
- [ ] [Group](12_abstract_algebra/group.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Abstract_Algebra/group.sublime-snippet)
- [ ] [Group generator](12_abstract_algebra/group_generator.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Abstract_Algebra/group_generator.sublime-snippet)
- [ ] [Monoid](12_abstract_algebra/monoid.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Abstract_Algebra/monoid.sublime-snippet)
- [ ] [Nimber product](12_abstract_algebra/nimber_product.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Abstract_Algebra/nimber_product.sublime-snippet)
- [ ] [Quotient group](12_abstract_algebra/quotient_group.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Abstract_Algebra/quotient_group.sublime-snippet)
- [ ] [Ring](12_abstract_algebra/ring.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Abstract_Algebra/ring.sublime-snippet)
- [ ] [Test closedness](12_abstract_algebra/test_closedness.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Abstract_Algebra/test_closedness.sublime-snippet)
- [ ] [Test commutative group isomorphism](12_abstract_algebra/test_commutative_group_isomorphism.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Abstract_Algebra/test_commutative_group_isomorphism.sublime-snippet)
- [ ] [Test commutative group nilpotency](12_abstract_algebra/test_commutative_group_nilpotency.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Abstract_Algebra/test_commutative_group_nilpotency.sublime-snippet)
- [ ] [Test direct product](12_abstract_algebra/test_direct_product.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Abstract_Algebra/test_direct_product.sublime-snippet)
- [ ] [Test group axioms](12_abstract_algebra/test_group_axioms.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Abstract_Algebra/test_group_axioms.sublime-snippet)
- [ ] [Test group commutativity](12_abstract_algebra/test_group_commutativity.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Abstract_Algebra/test_group_commutativity.sublime-snippet)
- [ ] [Test normal subgroup](12_abstract_algebra/test_normal_subgroup.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Abstract_Algebra/test_normal_subgroup.sublime-snippet)

### Finite Field

- [ ] [Factorizer over finite field](12_abstract_algebra/01_finite_field/factorizer_over_finite_field.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Abstract_Algebra/Finite_Field/factorizer_over_finite_field.sublime-snippet)
- [ ] [Finite field char 2 small](12_abstract_algebra/01_finite_field/finite_field_char2_small.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Abstract_Algebra/Finite_Field/finite_field_char2_small.sublime-snippet)
- [ ] [Irreducibility finite field](12_abstract_algebra/01_finite_field/irreducibility_finite_field.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Abstract_Algebra/Finite_Field/irreducibility_finite_field.sublime-snippet)

### Lambda Operations

- [ ] [Lambda arithmetic monoid action](12_abstract_algebra/02_lambda_operations/lambda_arithmetic_monoid_action.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Abstract_Algebra/Lambda_Operations/lambda_arithmetic_monoid_action.sublime-snippet)

## 13. Geometry

Points and lines first, then polygons, circles, convex hulls, sweeps, and triangulations.

### Point

- [ ] [Point](13_geometry/01_point/point.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Point/point.sublime-snippet)
- [ ] [Point3](13_geometry/01_point/point3.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Point/point3.sublime-snippet)

### Line

- [ ] [Find closed lines intersections](13_geometry/02_line/find_closed_lines_intersections.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Line/find_closed_lines_intersections.sublime-snippet)
- [ ] [Line](13_geometry/02_line/line.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Line/line.sublime-snippet)
- [ ] [Line3](13_geometry/02_line/line3.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Line/line3.sublime-snippet)
- [ ] [Line intersection](13_geometry/02_line/line_intersection.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Line/line_intersection.sublime-snippet)
- [ ] [Line to line distance](13_geometry/02_line/line_to_line_distance.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Line/line_to_line_distance.sublime-snippet)

### Polygon

- [ ] [Point in polygon](13_geometry/03_polygon/point_in_polygon.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Polygon/point_in_polygon.sublime-snippet)
- [ ] [Polygon cut](13_geometry/03_polygon/polygon_cut.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Polygon/polygon_cut.sublime-snippet)
- [ ] [Segment in polygon](13_geometry/03_polygon/segment_in_polygon.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Polygon/segment_in_polygon.sublime-snippet)

### Convex Polygon

- [ ] [Convex polygon](13_geometry/04_convex_polygon/convex_polygon.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Convex_Polygon/convex_polygon.sublime-snippet)
- [ ] [Convex polygon diameter](13_geometry/04_convex_polygon/convex_polygon_diameter.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Convex_Polygon/convex_polygon_diameter.sublime-snippet)
- [ ] [Convex polygon extreme point](13_geometry/04_convex_polygon/convex_polygon_extreme_point.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Convex_Polygon/convex_polygon_extreme_point.sublime-snippet)
- [ ] [Convex polygon locate](13_geometry/04_convex_polygon/convex_polygon_locate.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Convex_Polygon/convex_polygon_locate.sublime-snippet)
- [ ] [Convex polyhedra](13_geometry/04_convex_polygon/convex_polyhedra.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Convex_Polygon/convex_polyhedra.sublime-snippet)
- [ ] [Count convex polygon](13_geometry/04_convex_polygon/count_convex_polygon.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Convex_Polygon/count_convex_polygon.sublime-snippet)
- [ ] [Find convex polygon point inclusion relations](13_geometry/04_convex_polygon/find_convex_polygon_point_inclusion_relations.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Convex_Polygon/find_convex_polygon_point_inclusion_relations.sublime-snippet)
- [ ] [Half planes intersection](13_geometry/04_convex_polygon/half_planes_intersection.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Convex_Polygon/half_planes_intersection.sublime-snippet)

### Circle

- [ ] [Circle](13_geometry/05_circle/circle.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Circle/circle.sublime-snippet)
- [ ] [Circle common tangents](13_geometry/05_circle/circle_common_tangents.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Circle/circle_common_tangents.sublime-snippet)
- [ ] [Circle intersection](13_geometry/05_circle/circle_intersection.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Circle/circle_intersection.sublime-snippet)
- [ ] [Circle polygon intersection](13_geometry/05_circle/circle_polygon_intersection.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Circle/circle_polygon_intersection.sublime-snippet)
- [ ] [Find circle point inclusion relations](13_geometry/05_circle/find_circle_point_inclusion_relations.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Circle/find_circle_point_inclusion_relations.sublime-snippet)
- [ ] [Minimum enclosing circle](13_geometry/05_circle/minimum_enclosing_circle.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Circle/minimum_enclosing_circle.sublime-snippet)
- [ ] [Radical axis](13_geometry/05_circle/radical_axis.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Circle/radical_axis.sublime-snippet)

### Norm

- [ ] [Find a closest pair](13_geometry/06_norm/find_a_closest_pair.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Norm/find_a_closest_pair.sublime-snippet)
- [ ] [Find a furthest pair L1](13_geometry/06_norm/find_a_furthest_pair_l1.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Norm/find_a_furthest_pair_L1.sublime-snippet)
- [ ] [Find a furthest pair L2](13_geometry/06_norm/find_a_furthest_pair_l2.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Norm/find_a_furthest_pair_L2.sublime-snippet)
- [ ] [Find a furthest pair L∞](13_geometry/06_norm/find_a_furthest_pair_linf.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Norm/find_a_furthest_pair_Linf.sublime-snippet)
- [ ] [Rectilinear minimum spanning tree](13_geometry/06_norm/rectilinear_minimum_spanning_tree.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Norm/rectilinear_minimum_spanning_tree.sublime-snippet)

### Sweepline

- [ ] [Radial sweepline grouper](13_geometry/07_sweepline/radial_sweepline_grouper.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Sweepline/radial_sweepline_grouper.sublime-snippet)
- [ ] [Radial sweepline sorter](13_geometry/07_sweepline/radial_sweepline_sorter.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Sweepline/radial_sweepline_sorter.sublime-snippet)

### Decomposition

- [ ] [Delaunay triangulation](13_geometry/08_decomposition/delaunay_triangulation.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Decomposition/delaunay_triangulation.sublime-snippet)
- [ ] [Quad edge](13_geometry/08_decomposition/quad_edge.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Decomposition/quad_edge.sublime-snippet)
- [ ] [Trapzoidal decomposition](13_geometry/08_decomposition/trapzoidal_decomposition.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Decomposition/trapzoidal_decomposition.sublime-snippet)
- [ ] [Triangular decomposition](13_geometry/08_decomposition/triangular_decomposition.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/Decomposition/triangular_decomposition.sublime-snippet)

- [ ] [Triangle centers](13_geometry/triangle_centers.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Geometry/triangle_centers.sublime-snippet)

## 14. Succinct Structures

Bit-packed rank and select.

- [ ] [Succinct dictionary](14_succinct_structures/succinct_dictionary.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Succinct_Structures/succinct_dictionary.sublime-snippet)

## 15. Heuristic Algorithms

Simulated annealing and randomized search, for when nothing exact fits.

- [ ] [Hamiltonian path of random graph](15_heuristics/hamiltonian_path_of_random_graph.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Heuristic_Algorithms/hamiltonian_path_of_random_graph.sublime-snippet)
- [ ] [Simulated annealing](15_heuristics/simulated_annealing.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Heuristic_Algorithms/simulated_annealing.sublime-snippet)

## 16. Random Generators

Random trees, graphs, and polygons, for stress-testing everything above.

- [ ] [Generate chordal graph](16_random_generators/generate_chordal_graph.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Random_Generators/generate_chordal_graph.sublime-snippet)
- [ ] [Generate colinear points](16_random_generators/generate_colinear_points.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Random_Generators/generate_colinear_points.sublime-snippet)
- [ ] [Generate edge cactus](16_random_generators/generate_edge_cactus.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Random_Generators/generate_edge_cactus.sublime-snippet)
- [ ] [Generate graph](16_random_generators/generate_graph.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Random_Generators/generate_graph.sublime-snippet)
- [ ] [Generate parallel planar graph](16_random_generators/generate_parallel_planar_graph.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Random_Generators/generate_parallel_planar_graph.sublime-snippet)
- [ ] [Generate planar graph](16_random_generators/generate_planar_graph.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Random_Generators/generate_planar_graph.sublime-snippet)
- [ ] [Generate simple graph](16_random_generators/generate_simple_graph.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Random_Generators/generate_simple_graph.sublime-snippet)
- [ ] [Generate simple polygon](16_random_generators/generate_simple_polygon.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Random_Generators/generate_simple_polygon.sublime-snippet)
- [ ] [Generate simply connected bipartite graph](16_random_generators/generate_simply_connected_bipartite_graph.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Random_Generators/generate_simply_connected_bipartite_graph.sublime-snippet)
- [ ] [Generate simply connected graph](16_random_generators/generate_simply_connected_graph.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Random_Generators/generate_simply_connected_graph.sublime-snippet)
- [ ] [Generate tree](16_random_generators/generate_tree.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Random_Generators/generate_tree.sublime-snippet)

## 17. Miscellaneous

Fast IO, big integers, bit tricks, and other utilities.

- [ ] [Bigint](17_miscellaneous/bigint.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Miscellaneous/bigint.sublime-snippet)
- [ ] [Bitset64](17_miscellaneous/bitset64.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Miscellaneous/bitset64.sublime-snippet)
- [ ] [Bitset augmentation](17_miscellaneous/bitset_augmentation.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Miscellaneous/bitset_augmentation.sublime-snippet)
- [ ] [De bruijn bit magic](17_miscellaneous/de_bruijn_bit_magic.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Miscellaneous/de_bruijn_bit_magic.sublime-snippet)
- [ ] [Fast IO](17_miscellaneous/fastio.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Miscellaneous/fastio.sublime-snippet)
- [ ] [Floored root](17_miscellaneous/floored_root.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Miscellaneous/floored_root.sublime-snippet)
- [ ] [Hilbert curve 2D](17_miscellaneous/hilbert_curve_2d.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Miscellaneous/hilbert_curve_2d.sublime-snippet)
- [ ] [Int128 augmentation](17_miscellaneous/int128_augmentation.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Miscellaneous/int128_augmentation.sublime-snippet)
- [ ] [Logging allocator](17_miscellaneous/logging_allocator.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Miscellaneous/logging_allocator.sublime-snippet)
- [ ] [MEX](17_miscellaneous/mex.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Miscellaneous/mex.sublime-snippet)
- [ ] [Next bit permutation](17_miscellaneous/next_bit_permutation.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Miscellaneous/next_bit_permutation.sublime-snippet)
- [ ] [PBDS](17_miscellaneous/pbds.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Miscellaneous/pbds.sublime-snippet)
- [ ] [PNG parser](17_miscellaneous/png_parser.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Miscellaneous/png_parser.sublime-snippet)
- [ ] [Random](17_miscellaneous/random.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Miscellaneous/random.sublime-snippet)
- [ ] [State evolver](17_miscellaneous/state_evolver.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Miscellaneous/state_evolver.sublime-snippet)
- [ ] [Timer](17_miscellaneous/timer.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Miscellaneous/timer.sublime-snippet)
- [ ] [Trygub number](17_miscellaneous/trygub_number.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Miscellaneous/trygub_number.sublime-snippet)
- [ ] [Type name](17_miscellaneous/type_name.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Miscellaneous/type_name.sublime-snippet)
- [x] Value compressor — ours: [`CoordinateCompression.h`](https://github.com/lamng3/competitive-programming-notebook/blob/main/notebook/utils/CoordinateCompression.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Miscellaneous/value_compressor.sublime-snippet)
- [ ] [Y combinator](17_miscellaneous/y_combinator.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Miscellaneous/y_combinator.sublime-snippet)

## 18. Network Communication

Communication problems, where two programs talk through a limited channel.

- [ ] [Network communication manager](18_network_communication/network_communication_manager.h) · [reference](https://github.com/fextivity/CP-aeren/blob/main/Library/Network_Communication/network_communication_manager.sublime-snippet)
