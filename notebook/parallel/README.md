# Parallel algorithms

Parallel algorithms with [ParlayLib](https://github.com/cmuparlay/parlaylib), following [CMSC 858N](https://www.cs.umd.edu/~laxman/paralg-f26.html). Each folder is one problem: stubs to write, and a `bench.cpp` that checks and times them against a sequential version.

## Setup, once

Add this to `~/.zshrc`, then run `source ~/.zshrc`:

```zsh
cppar() { python3 "$CP_ROOT/tools/cppar.py" "$@"; }
```

## Write, check, time

Write the two scans in [`prefix_sums/`](prefix_sums/): [Hillis and Steele's](prefix_sums/HillisSteeleScan.h) and [Blelloch's](prefix_sums/BlellochScan.h). Then, from any folder:

```sh
cppar prefix_sums --check   # is it right?
cppar prefix_sums           # is it fast?
```

```text
| version           | 1 thread | 2 threads | 4 threads | 8 threads | 12 threads |
|:------------------|---------:|----------:|----------:|----------:|-----------:|
| loop (sequential) |  34.6 ms |           |           |           |            |
```

Each scan you write gets a row here, and a row in a second table of speedups over the loop. `--lg 22` times a smaller n, `--threads 1 8` other thread counts, and `--check --tsan` looks for data races.

## Try ParlayLib

```sh
cpnew play parlay   # play.cpp: ParlayLib included, empty main
cppar play.cpp      # build it and run it
```

Read the [reference](https://cmuparlay.github.io/parlaylib/), the headers in `third_party/parlaylib/include/parlay/`, and the algorithms in `third_party/parlaylib/examples/`.

## Add a problem

`cppar --new <name>` makes a folder with a `bench.cpp` and a stub. [`tools/parbench.h`](../../tools/parbench.h) explains the rest.
