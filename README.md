<div align="center">

# 🏆 Competitive Programming Notebook

**Templates, a snippet library, contest solutions, and command-line tools in C++ and Python**

[![Notes](https://img.shields.io/badge/notes-cp--docs-8b5cf6)](https://lamng3.github.io/cp-docs/)
[![C++20](https://img.shields.io/badge/C%2B%2B-20-3b82f6)](templates/contest.cpp)
[![Python](https://img.shields.io/badge/python-3-3b82f6)](python/)
[![LeetCode](https://img.shields.io/badge/LeetCode-lamng3-f59e0b)](https://leetcode.com/u/lamng3/)

[⚡ Quick start](#-quick-start) · [📦 What's inside](#-whats-inside) · [🛠 Tools](#-tools) · [⚙ Setup](#-setup) · [📖 Notes](https://lamng3.github.io/cp-docs/)

</div>

<p align="center"><b>Lam Nguyen</b></p>

<p align="center">
  <img src="assets/demo.gif" width="100%" alt="Demo of the notebook tools">
</p>

## ⚡ Quick start

After [setup](#-setup), from any directory:

```bash
cpnew A                  # ./A.cpp from the contest template
cpsnip DSU --into A      # paste a notebook snippet into A.cpp (--kactl for KACTL's)
cpbuild A                # sanitizers, warnings, and dbg(...) on
./solution < in.txt

cpdiff A --init          # A_brute.cpp and A_gen.cpp to fill in
cpdiff A -n 1000         # stress test A.cpp against the brute force

cppar hillis_steele_scan # time a parallel algorithm against a sequential one
cpnew play parlay        # play.cpp, an empty file with ParlayLib to try things in
cppar play.cpp           # build it with ParlayLib and run it

cpgen 930                # fetch a LeetCode problem into a C++ stub
cptest 930               # run it against LeetCode's examples
```

## 📦 What's inside

<div align="center">

| Area | Contents |
|:--|:--|
| Contest solutions | **187**: LeetCode 123, Codeforces 50, USACO 7, OI 3, AtCoder 2, ICPC 2 |
| C++ notebook | **30** snippets: data structures, databases, graphs, math, strings, trees |
| Python notebook | **37** paste-ready snippets in the same categories |
| Unit tests | **38** across the C++ and Python libraries, run with `cpunit` |
| Interview problems | **13**, each with C++, Python, and tests |
| Templates | `contest`, `leetcode`, `minimal`, `oi`, `parlay`, plus `gen` for random tests |
| LeetCode map | **140** handpicked problems for the USACO Guide's Platinum and Advanced modules, in [`contests/leetcode`](contests/leetcode) |

<sub>Counted from the files in this repository</sub>

</div>

`notebook/databases/` holds the structures behind real storage systems: a
Bloom filter, a count-min sketch, a cuckoo filter, a skip list, and eviction
policies.

`notebook/parallel/` holds parallel algorithms written with
[ParlayLib](https://github.com/cmuparlay/parlaylib), one folder per problem and
one file per algorithm, checked and timed by `cppar`. Prefix sums comes first,
with Hillis and Steele's scan and Blelloch's to write; see
[its README](notebook/parallel/README.md).

<details>
<summary><b>Repository layout</b></summary>

```text
templates/    contest, leetcode, minimal, oi, and parlay starters; gen for cpdiff generators
notebook/     C++ snippets to paste or include; databases/ for storage structures, parallel/ for parallel algorithms
python/       paste-ready Python snippets, same categories as notebook/
contests/     solutions by platform: leetcode, codeforces, atcoder, usaco, oi, icpc
interviews/   interview problems, one folder per question, each with C++, Python, and tests
tools/        cpnew, cpgen, cptest, cpunit, cpdiff, cppar, cpsnip
```

</details>

## 🛠 Tools

<details>
<summary><b><code>cpbuild &lt;file.cpp&gt;</code>: build with sanitizers and debug output</b></summary>

Debug compilation with sanitizers and warnings. Passes `-DLOCAL`, which turns on `dbg` in the contest template.

```
cpbuild A
./solution < in.txt
```

The contest template (`templates/contest.cpp`, what `cpnew` copies by default) prints debug output to the terminal when built with `cpbuild`.

```cpp
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    dbg(n, a);          // [n, a]: 3, [1, 2, 3]
    cerr << a << '\n';  // [1, 2, 3]
}
```

`dbg` prints numbers, strings, pairs, and containers: `vector`, `set`, `map`, and nested containers. On the judge `LOCAL` is off, so each `dbg(...)` compiles away and can stay in the submitted file.

`cerr.tie(0)` sits next to `cin.tie(0)`. After `cin.tie(0)`, the Mac C++ library drops `cerr` unless it is untied from `cout`, so a plain `cerr` line shows up while the program is still running.

</details>

<details>
<summary><b><code>cpnew &lt;file&gt; [template]</code>: start a solution from a template</b></summary>

Copies a template into a new `.cpp` file in the current directory, or at the path you pass. It always loads templates from this repository, whatever directory you run it from. With no template argument it uses `templates/contest.cpp`; the others are `leetcode`, `minimal`, `oi`, and `parlay`, an empty file with ParlayLib included, to run with `cppar`.

```
cpnew A                              # ./A.cpp from templates/contest.cpp
cpnew A leetcode                     # ./A.cpp from templates/leetcode.cpp
cpnew contests/codeforces/r900/A     # creates missing directories
cpnew A -f                           # overwrite if A.cpp exists
cpnew A --py                         # ./A.py from python/template.py
cpnew A leetcode --py                # ./A.py from python/leetcode.py
```

</details>

<details>
<summary><b><code>cpsnip [name...] [--into file] [--kactl|--py]</code>: paste a snippet into a solution</b></summary>

Pastes a data structure or algorithm into a solution, so you can use it right away. It draws on two libraries: this repository's `notebook/`, the default, and [KACTL](https://github.com/kth-competitive-programming/kactl), the KTH team's notebook, with `--kactl` (cloned into `third_party/kactl` the first time). `--py` uses the Python snippets in `python/`.

```
cpsnip                              # list the notebook's snippets
cpsnip seg                          # the ones whose names contain "seg"
cpsnip DSU --into A                 # paste notebook/graphs/dsu/DSU.h into A.cpp
cpsnip FenwickTree --into 2179      # into contests/leetcode/solve/2179.cpp, above class Solution
cpsnip FenwickTree                  # print it and copy it, to paste into LeetCode's editor
cpsnip --kactl                      # list KACTL's snippets
cpsnip HLD --kactl --into 2179      # KACTL's heavy-light decomposition, with the segment tree it uses
```

- The paste goes above `class Solution`, or above `preprocess`, `solve`, or `main` in the contest templates. A snippet brings the snippets it includes, and one already in the file is not pasted again.
- The file keeps its own `<bits/stdc++.h>`, `using namespace std`, `MOD`, and `INF`, and the snippet's copies are left out. When a snippet defines one of them differently (KACTL's `MinCostMaxFlow` has `const ll INF`), cpsnip says so: rename or remove one.
- KACTL's code uses `rep`, `all`, `sz`, `ll`, `pii`, and `vi`, so a short prelude defines whichever the file lacks. Its header comment stays, with what each function takes and how fast it runs. Its `LazySegmentTree` comes without the bump allocator it normally includes, which never frees memory (`cpsnip BumpAllocator --kactl` adds it).
- A few KACTL snippets are templates to fill in, like `MoQueries` and `DivideAndConquerDP`. A few need GCC, like `OrderStatisticTree` and `HashMap` with `<bits/extc++.h>`: Codeforces has it, the Mac's clang doesn't.

</details>

<details>
<summary><b><code>cpgen &lt;problem&gt; [contest] [--weekly|--biweekly] [--upsolve]</code>: fetch a LeetCode problem</b></summary>

Fetches a LeetCode problem and generates a `.cpp` file with the template and the method stub.

```
cpgen 930                              # -> contests/leetcode/solve/930.cpp
cpgen 930 496 --weekly                 # -> contests/leetcode/solve/weekly/496/930.cpp
cpgen 930 150 --biweekly               # -> contests/leetcode/solve/biweekly/150/930.cpp
cpgen 930 --upsolve                    # -> contests/leetcode/upsolve/930.cpp
cpgen 3891 496 --weekly --upsolve      # -> contests/leetcode/upsolve/weekly/496/3891.cpp
```

TreeNode and ListNode definitions are generated when the problem needs them.

</details>

<details>
<summary><b><code>cptest &lt;problem&gt; [test] [--anyorder]</code>: run LeetCode's examples</b></summary>

- The first run fetches and caches the example test cases; it does not compile or run.
- Later runs compile and test against the cached examples, with `dbg(...)` output under each result.
- It looks for `<number>.cpp` in the current directory first, then in `contests/leetcode/solve/`.
- "Any order" problems are detected from the problem description; `--anyorder` forces it.
- Tree and list inputs are serialized for TreeNode and ListNode problems.

```
cptest 930              # fetch (first time) or run all tests
cptest 930 1            # run test 1 only
cptest 930 --anyorder   # order-independent comparison
cptest 930 --add "[1,0,1]" "2" --expect "3"   # add a custom test case
cptest 930 --refetch    # re-fetch test cases from LeetCode

# Contest / upsolve workflow
cd contests/leetcode/solve/weekly/496 && cptest 930
cd contests/leetcode/upsolve/weekly/496 && cptest 930
```

Test cases are cached in `contests/leetcode/tests/<number>.json`, shared between solve and upsolve.

</details>

<details>
<summary><b><code>cpdiff &lt;file&gt; [tests...]</code>: stress test against a brute force or test files</b></summary>

Runs a solution against a slow but obviously correct brute force on random tests, and stops at the first test where they disagree. The workflow follows [VNOI's guide to generating tests](https://wiki.vnoi.info/algo/skill/sinh-test-new): a generator, a brute force, and the solution, compared every round.

```
cpdiff A --init              # create A_brute.cpp (contest template) and A_gen.cpp (templates/gen.cpp)
cpdiff A                     # 100 rounds: A_gen.cpp -> A_brute.cpp vs A.cpp
cpdiff A -n 1000             # 1000 rounds
cpdiff A --seed 27 -n 1      # replay the failing round
cpdiff A --brute naive --gen mygen   # choose files by name (.cpp or .py)
cpdiff A tests/              # every tests/X.in against tests/X.out (or .ans)
cpdiff A 1.in 1.out          # one input against one expected output
cpdiff A 1.in                # one input against the brute force
cpdiff A tests/ --eps 1e-6   # numbers within 1e-6 count as equal
cpdiff A --gen A_max --no-brute -n 10 --tl 1   # timing: max-size tests, no brute force
```

- The brute force is found next to the solution as `A_brute`, `brute`, or `naive`; the generator as `A_gen` or `gen`. Each can be `.cpp` or `.py`.
- The generator runs as `gen <seed>` and prints one test (or writes exactly one file). Seeds go up by one per round, so any round can be replayed. `templates/gen.cpp` has `rnd`, `rnd_vec`, `rnd_perm`, `rnd_str`, and trees: `rnd_tree`, `rnd_tree_prufer` (uniformly random), and `special_tree` (path, star, binary, broom).
- OI-style file I/O works unchanged. A program with `freopen("comnet.inp", "r", stdin)` and `freopen("comnet.out", "w", stdout)` gets the test in `comnet.inp` and is judged on `comnet.out`. `ifstream`/`ofstream` and names built from `#define TASK "comnet"` or `const string NAME` are detected too. Each program runs in its own folder, so the solution's `.out` and the brute's `.ans` never collide.
- `--no-brute` is the timing check: run the solution alone on large generated tests and report crashes, TLE, and the slowest seed.
- Output is compared token by token, so spacing and trailing newlines do not matter. `--exact` compares bytes.
- `--tl 2` is the time limit per run in seconds. TLE and runtime errors (with the signal name) are reported like wrong answers.
- C++ is built with `-O2 -DONLINE_JUDGE -include fstream` into `.cpdiff/A/` and rebuilt only when the source changes. A failing test is saved there as `fail.in`, `fail.ans` (brute), and `fail.out` (solution).

```
WRONG ANSWER on round 6, seed 500621391
token 1 (line 1): expected '-8', got '0'
input:
  2
  -8 -8
expected (A_brute.cpp):
  -8
got (A.cpp):
  0
saved to .cpdiff/A/fail.in, fail.ans, fail.out; replay with --seed 500621391 -n 1
```

</details>

<details>
<summary><b><code>cppar &lt;name&gt; [--check] [--lg L] [--threads P ...]</code>: check and time parallel algorithms</b></summary>

Builds a file in `notebook/parallel/` with [ParlayLib](https://github.com/cmuparlay/parlaylib) and runs it on 1, 2, 4, ... threads. Every function the file times with `parbench::run` is checked against the first, and the results print as tables. See [`notebook/parallel/`](notebook/parallel/README.md).

```
cppar hillis_steele_scan              # times and speedups on 1 to 12 threads
cppar hillis_steele_scan --check      # compile errors, crashes, or pass/fail on sizes 0 to 2^20
cppar prefix_sums                     # every file in notebook/parallel/prefix_sums/
cppar play.cpp                        # any file; one without parbench::run just runs
cppar --new prefix_sums/blocked_scan  # a new file from the template, from any folder
cppar --new blocked_scan              # the same, run from inside notebook/parallel/prefix_sums/
```

</details>

<details>
<summary><b><code>cpunit &lt;name&gt; [--cpp|--py]</code>: run a library unit test</b></summary>

Finds `notebook/**/tests/<name>_test.cpp` and `python/**/tests/test_<name>.py`, builds C++ with sanitizers, runs Python with `unittest`, and exits nonzero on failure.

```
cpunit --list              # every test that can be run
cpunit bloomfilter         # C++ and Python tests for bloomfilter
cpunit bloomfilter --py    # only the Python one
```

</details>

## ⚙ Setup

The tools are shell functions, so they work from every directory once your shell loads them. They call the scripts in this repository through `CP_ROOT` and do not depend on the current directory.

Clone the repository, add the block below to `~/.zshrc` with `CP_ROOT` set to where you cloned it, then run `source ~/.zshrc` or open a new terminal.

<details>
<summary><b>Shell functions for <code>~/.zshrc</code></b></summary>

```zsh
# Competitive programming tools. Work from any directory.
export CP_ROOT="$HOME/path/to/competitive-programming-notebook"

cpbuild() {
    local src="$1"
    if [[ -z $src ]]; then
        echo "usage: cpbuild <file>[.cpp] [extra g++ flags...]" >&2
        return 2
    fi
    [[ -f $src ]] || [[ ! -f $src.cpp ]] || src="$src.cpp"
    if [[ ! -f $src ]]; then
        echo "No such file: $1 (tried $1 and $1.cpp)" >&2
        return 1
    fi
    shift
    g++ -std=c++20 -DLOCAL -Wall -Wextra -Wshadow -fsanitize=address -fsanitize=undefined "$src" "$@" -o solution \
        && echo "Compiled $src -> solution"
}
cpnew() {
    python3 "$CP_ROOT/tools/cpnew.py" "$@"
}
cpgen() {
    python3 "$CP_ROOT/tools/cpgen.py" "$@"
}
cptest() {
    python3 "$CP_ROOT/tools/cptest.py" "$@"
}
cpunit() {
    python3 "$CP_ROOT/tools/cpunit.py" "$@"
}
cppar() {
    python3 "$CP_ROOT/tools/cppar.py" "$@"
}
cpsnip() {
    python3 "$CP_ROOT/tools/cpsnip.py" "$@"
}
cpdiff() {
    python3 "$CP_ROOT/tools/cpdiff.py" "$@"
}
cprun() {
    if [[ -x ./solution ]]; then
        ./solution "$@"
    elif [[ -e ./solution ]]; then
        echo "./solution exists but is not executable (chmod +x ./solution)" >&2
        return 126
    else
        echo "No ./solution in $PWD - build one first with: cpbuild <file>.cpp" >&2
        return 127
    fi
}
```

`cprun` runs the last build, `./solution`, with any arguments you pass.

</details>
