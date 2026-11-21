# Parallel algorithms

Parallel algorithms for multicore machines, written with [ParlayLib](https://github.com/cmuparlay/parlaylib), the library used in [CMSC 858N](https://www.cs.umd.edu/~laxman/paralg-f26.html). Each folder is one problem: the parallel versions to write, and a `bench.cpp` that registers them with a sequential reference. [`cppar`](../../tools/cppar.py) checks every version against the reference and times them all on several thread counts.

A version still to write is a stub that throws `logic_error("not written yet")` under a `TODO: write it` line. `cppar` reports it as not written yet, and the site's code library leaves it out until it is written.

## Running

```sh
cppar prefix_sums                     # time every version on 1, 2, 4, 8, and 12 threads, as a table
cppar prefix_sums --check             # check every version on sizes from 0 to 2^20, with sanitizers
cppar prefix_sums --check --tsan      # the same with ThreadSanitizer, to look for data races
cppar prefix_sums --lg 22             # at n = 2^22 instead of the default size
cppar prefix_sums --threads 1 8       # on these thread counts
```

The first run fetches ParlayLib into `third_party/parlaylib`, which git ignores. Each cell of the table is the median time per run and the speedup over the sequential reference.

## Learning ParlayLib

To try ParlayLib on its own, start an empty file from the `parlay` template and run it with `cppar`:

```sh
cpnew play parlay                     # play.cpp in this folder, with ParlayLib included and an empty main
cppar play.cpp                        # build it with ParlayLib and run it
PARLAY_NUM_THREADS=4 cppar play.cpp   # the same on 4 threads
```

The [reference documentation](https://cmuparlay.github.io/parlaylib/) lists every function. To read the code, start with `sequence.h`, `parallel.h`, and `primitives.h` in `third_party/parlaylib/include/parlay/`, and `third_party/parlaylib/examples/` has dozens of algorithms written with it.

## Prefix sums

Write [Hillis and Steele's scan](prefix_sums/HillisSteeleScan.h) and [Blelloch's](prefix_sums/BlellochScan.h), then:

1. **Hillis and Steele.** Before timing it, count its additions and compare with the loop's.
2. **Blelloch.** Is it faster than the loop? If not, count how many times it reads and writes the whole array.

On an Apple M2 Pro at n = 2^26, the sequential loop takes about 25 ms.

## Adding a problem

`cppar --new <name>` starts a folder with a `bench.cpp` and a stub. In `bench.cpp`, [`tools/parbench.h`](../../tools/parbench.h) takes an input generator, the sequential reference, and any number of parallel versions; its header comment shows how to time only part of a version, and how to check problems with many right answers.

## Benchmarking well

- Check the answer on every run. `cppar` does.
- Compare against the best sequential code, not against your parallel code on one thread.
- Turn times into bytes moved per second and compare with the machine's memory bandwidth. Near it, more cores can't help.
- On a laptop, plug it in and close other programs, and expect noise once the performance cores are all busy.
