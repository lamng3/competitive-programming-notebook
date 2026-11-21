# Parallel algorithms

Parallel algorithms with [ParlayLib](https://github.com/cmuparlay/parlaylib), following [CMSC 858N](https://www.cs.umd.edu/~laxman/paralg-f26.html). One folder per problem, one file per algorithm. Each file times its algorithm against a plain sequential version with `parbench::run`, which also checks the answers. The code is plain production C++: specific includes, `std::` names, and no aliases like `ll`.

## Setup, once

Add this to `~/.zshrc`, then run `source ~/.zshrc`:

```zsh
cppar() { python3 "$CP_ROOT/tools/cppar.py" "$@"; }
```

## Write, check, time

Fill in the `TODO` in [`prefix_sums/hillis_steele_scan.cpp`](prefix_sums/hillis_steele_scan.cpp) or [`prefix_sums/blelloch_scan.cpp`](prefix_sums/blelloch_scan.cpp). Then, from any folder:

```sh
cppar hillis_steele_scan --check   # compile errors, a crash with its line, or pass/fail on sizes 0 to 2^20
cppar hillis_steele_scan           # times and speedups on 1, 2, 4, 8, and 12 threads
cppar prefix_sums                  # every file in the folder
```

```text
| function | 1 thread | 2 threads | 4 threads | 8 threads | 12 threads |
|:---------|---------:|----------:|----------:|----------:|-----------:|
| loop     |  76.6 ms |   68.2 ms |   68.4 ms |   66.2 ms |    74.4 ms |
```

Your scan gets a row there once it is written, and a row in a second table of speedups over the loop.

In VS Code, ⇧⌘B runs the check on the open file, and compile errors show in the Problems panel.

## Try things

```sh
cppar prime_sieve                  # a file without parbench::run just runs
cpnew play parlay && cppar play.cpp
cppar --new prefix_sums/blocked_scan
```

The [ParlayLib reference](https://cmuparlay.github.io/parlaylib/) lists every function, and `third_party/parlaylib/examples/` has dozens of algorithms written with it.
