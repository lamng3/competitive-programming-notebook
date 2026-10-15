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
cpbuild A                # sanitizers, warnings, and dbg(...) on
./solution < in.txt

cpgen 930                # fetch a LeetCode problem into a C++ stub
cptest 930               # run it against LeetCode's examples
```

## 📦 What's inside

<div align="center">

| Area | Contents |
|:--|:--|
| Contest solutions | **186**: LeetCode 122, Codeforces 50, USACO 7, OI 3, AtCoder 2, ICPC 2 |
| C++ notebook | **30** snippets: data structures, databases, graphs, math, strings, trees |
| Python notebook | **37** paste-ready snippets in the same categories |
| Unit tests | **38** across the C++ and Python libraries, run with `cpunit` |
| Interview problems | **13**, each with C++, Python, and tests |
| Templates | `contest`, `leetcode`, `minimal`, `oi` |
| Study list | 18 sections, from searching to network communication, ticked as the notebook gains each topic |

<sub>Counted from the files in this repository</sub>

</div>

`notebook/databases/` holds the structures behind real storage systems: a
Bloom filter, a count-min sketch, a cuckoo filter, a skip list, and eviction
policies.

<details>
<summary><b>Repository layout</b></summary>

```text
templates/    contest, leetcode, minimal, and oi starters
notebook/     C++ snippets to paste or include; notebook/databases/ for storage structures
python/       paste-ready Python snippets, same categories as notebook/
contests/     solutions by platform: leetcode, codeforces, atcoder, usaco, oi, icpc
interviews/   interview problems, one folder per question, each with C++, Python, and tests
todo/         a C++ study list in numbered sections, one stub per topic
tools/        cpnew, cpgen, cptest, cpunit
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

Copies a template into a new `.cpp` file in the current directory, or at the path you pass. It always loads templates from this repository, whatever directory you run it from. With no template argument it uses `templates/contest.cpp`; the others are `leetcode`, `minimal`, and `oi`.

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
