# 19. Parallel Algorithms

The first exercises from [CMSC 858N, Scalable Parallel Algorithms and Data Structures](https://www.cs.umd.edu/~laxman/paralg-f26.html): inclusive prefix sums three ways, written with [ParlayLib](https://github.com/cmuparlay/parlaylib), the library the course uses. Each stub starts empty. Write it, check it, time it, and when it is done, move it into `notebook/parallel/` and tick it in the [study list](../README.md#19-parallel-algorithms).

## Setup, once

```sh
python3 todo/19_parallel_algorithms/bench.py --setup   # clones ParlayLib into third_party/, which git ignores
```

## Check and time

```sh
cpunit todo_parallel                                  # each scan against std::partial_sum, on sizes 0 to 2^20
python3 todo/19_parallel_algorithms/bench.py          # n = 2^26, on 1, 2, 4, 8, and 12 threads
python3 todo/19_parallel_algorithms/bench.py --lg 22 --threads 1 8
```

`cpunit` builds with AddressSanitizer and UndefinedBehaviorSanitizer. To look for data races, build the test with `-fsanitize=thread` instead; the command is at the top of the test file.

The benchmark prints CSV: method, threads, n, median milliseconds, billions of elements per second, and speedup over a plain sequential loop. It times ParlayLib's own scan as well, and skips a scan that is not written yet or gives a wrong answer.

## Exercises

1. **[Hillis and Steele](scan_hillis_steele.h).** Before timing it, count its additions and compare with the loop's.
2. **[Blelloch](scan_blelloch.h).** Is it faster than the loop? If not, count how many times it reads and writes the whole array.
3. **[Blocked](scan_blocked.h).** Try block sizes from 2^8 to 2^20, and explain what goes wrong at each end.
4. **The limit.** Turn your best time into bytes moved per second and compare it with the machine's memory bandwidth. What limits a scan, and how many cores does it take to reach that limit?
5. **Smaller elements.** Change `ll` to `int` in `bench.cpp`. Which versions speed up, and why by that much?
6. **Filter.** Use your blocked scan to keep the multiples of 3, packed in order, and compare it with `parlay::filter`.

## Benchmarking well

- Check the answer on every run. The test and the benchmark both do.
- Warm up, then take the median of several runs. The benchmark runs each scan 9 times and reports the median of the last 7.
- Compare against the best sequential code, not against your parallel code on one thread. A version that is 3× faster than itself on one thread can be barely faster than the plain loop.
- Vary the thread count and the size, and write down the machine, compiler, and flags with the numbers.
- Turn times into bandwidth, bytes read and written per second, and compare with the machine's peak. Near the peak, more cores can't help, and only fewer passes over memory can.
- On a laptop, plug it in and close other programs. macOS doesn't let a program choose the core a thread runs on, so expect noise, especially once the performance cores are all busy.

## Numbers to beat

On an Apple M2 Pro (8 performance and 4 efficiency cores, 16 GB, Apple clang 15, `-O3`), at n = 2^26, which is 512 MiB per array:

- the sequential loop takes about 25 ms;
- ParlayLib's scan takes about 38 ms on 1 thread and 11 to 13 ms on 4 to 12 threads.

## Going further

- [ParlayLib's examples](https://github.com/cmuparlay/parlaylib/tree/master/examples): dozens of parallel algorithms written with ParlayLib. Read one after writing your own version.
- [PBBS](https://cmuparlay.github.io/pbbsbench/), the Problem Based Benchmark Suite: problems with inputs and checkers, from sorting to graph algorithms.
- [Stanford CS149, Assignment 1](https://github.com/stanford-cs149/asst1): threads and SIMD on a CPU. Check its README for what it needs.
- MIT 6.172, _Performance Engineering of Software Systems_, on MIT OpenCourseWare: lectures and assignments on making code fast, parallel code included.
- [Compiler Explorer](https://godbolt.org): the assembly a loop compiles to, for example whether it was vectorized.
- A Linux machine with many cores, such as a cloud instance rented by the hour: there `taskset` or `numactl` can pin threads to cores, and `perf stat` counts cache misses.
