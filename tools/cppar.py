#!/usr/bin/env python3
"""Check and time the parallel algorithms in notebook/parallel/, from any directory.

Usage:
    cppar prefix_sums                    time every version against the sequential one, on 1, 2, 4, ... threads
    cppar prefix_sums --lg 22            at n = 2^22 instead of the benchmark's default size
    cppar prefix_sums --threads 1 4 8    on these thread counts
    cppar prefix_sums --csv              CSV instead of a table
    cppar prefix_sums --check            check every version on many sizes, built with sanitizers
    cppar prefix_sums --check --tsan     the same with ThreadSanitizer, to look for data races
    cppar --list                         the benchmarks there are
    cppar --new list_ranking             start a new one from the template
    cppar play.cpp                       build any file with ParlayLib (-O3) and run it; later arguments go to it
    cppar play.cpp --check               the same, built with sanitizers

A benchmark is notebook/parallel/<name>/bench.cpp: a main() that registers a
sequential reference and parallel versions with tools/parbench.h. The first
run fetches ParlayLib into third_party/parlaylib. Builds are cached in .cppar/.
"""

import hashlib
import os
import platform
import subprocess
import sys

REPO_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PAR_DIR = os.path.join(REPO_ROOT, "notebook", "parallel")
TOOLS = os.path.join(REPO_ROOT, "tools")
PARLAY = os.path.join(REPO_ROOT, "third_party", "parlaylib")
CACHE = os.path.join(REPO_ROOT, ".cppar")

FLAGS = {
    "bench": ["-O3", "-DNDEBUG"],
    "check": ["-O1", "-g", "-fsanitize=address,undefined"],
    "tsan": ["-O1", "-g", "-fsanitize=thread"],
}

BENCH_TEMPLATE = """\
// {title}: a sequential version against parallel ones.
//   cppar {name}            time them, on 1 thread up to every core
//   cppar {name} --check    check them on many sizes
#include <parbench.h>
#include <parlay/primitives.h>
#include "{header}"

using ll = long long;
using Input = parlay::sequence<ll>;   // Change these to fit the problem:
using Output = parlay::sequence<ll>;  // a graph, a tree, a batch of updates, ...

int main(int argc, char** argv) {{
    parbench::Bench<Input, Output> b("{title}");
    b.default_size(24);
    b.input([](size_t n, uint64_t seed) {{
        return parlay::tabulate(n, [&](size_t i) {{ return ll(parlay::hash64(i + seed * n) % 100); }});
    }});
    b.sequential("sequential", [](const Input& in) {{
        // The plain sequential algorithm: the answers to match and the time to beat.
        return Output(in);
    }});
    b.parallel("mine", [](const Input& in) {{ return {function}(in); }});
    return b.run(argc, argv);
}}
"""

HEADER_TEMPLATE = """\
#pragma once
#include <bits/stdc++.h>
#include <parlay/parallel.h>
#include <parlay/sequence.h>
using namespace std;

// {title}: what it computes, and the work and depth to aim for.
// Check: cppar {name} --check. Time: cppar {name}.

parlay::sequence<long long> {function}(const parlay::sequence<long long>& in) {{
    // TODO: write it, then delete this line and the next.
    throw logic_error("not written yet");
}}
"""


def benchmarks():
    if not os.path.isdir(PAR_DIR):
        return []
    return sorted(d for d in os.listdir(PAR_DIR) if os.path.isfile(os.path.join(PAR_DIR, d, "bench.cpp")))


def ensure_parlaylib():
    if os.path.isdir(PARLAY):
        return True
    print("Fetching ParlayLib into third_party/parlaylib ...", file=sys.stderr)
    url = "https://github.com/cmuparlay/parlaylib.git"
    return subprocess.run(["git", "clone", "--quiet", "--depth", "1", url, PARLAY]).returncode == 0


def build(name, mode):
    """Build notebook/parallel/<name>/bench.cpp for mode, unless the cached build is newer than its sources."""
    folder = os.path.join(PAR_DIR, name)
    sources = [os.path.join(TOOLS, "parbench.h")]
    for root, _, files in os.walk(folder):
        sources += [os.path.join(root, f) for f in files if f.endswith((".h", ".cpp"))]
    exe = os.path.join(CACHE, f"{name}-{mode}")
    if os.path.exists(exe) and os.path.getmtime(exe) >= max(os.path.getmtime(s) for s in sources):
        return exe
    os.makedirs(CACHE, exist_ok=True)
    cxx = os.environ.get("CXX", "c++")
    cmd = [cxx, "-std=c++17", "-pthread", "-Wall", *FLAGS[mode],
           "-I", TOOLS, "-I", os.path.join(PARLAY, "include"), os.path.join(folder, "bench.cpp"), "-o", exe]
    print(f"Building {name} ({mode}) ...", file=sys.stderr)
    if subprocess.run(cmd).returncode != 0:
        return None
    return exe


def machine():
    """The CPU's name and its hardware thread count."""
    name = platform.processor() or platform.machine()
    try:
        if platform.system() == "Darwin":
            name = subprocess.run(["sysctl", "-n", "machdep.cpu.brand_string"], capture_output=True, text=True).stdout.strip()
        elif os.path.exists("/proc/cpuinfo"):
            with open("/proc/cpuinfo") as f:
                for line in f:
                    if line.startswith("model name"):
                        name = line.split(":", 1)[1].strip()
                        break
    except OSError:
        pass
    return f"{name}, {os.cpu_count()} hardware threads"


def new(name):
    name = name.replace("-", "_")
    folder = os.path.join(PAR_DIR, name)
    if os.path.exists(folder):
        print(f"{os.path.relpath(folder, REPO_ROOT)} already exists", file=sys.stderr)
        return 1
    camel = "".join(w.capitalize() for w in name.split("_"))
    fields = {"name": name, "title": name.replace("_", " "), "header": camel + ".h", "function": name}
    os.makedirs(folder)
    with open(os.path.join(folder, "bench.cpp"), "w") as f:
        f.write(BENCH_TEMPLATE.format(**fields))
    with open(os.path.join(folder, camel + ".h"), "w") as f:
        f.write(HEADER_TEMPLATE.format(**fields))
    rel = os.path.relpath(folder, REPO_ROOT)
    print(f"Created {rel}/bench.cpp and {rel}/{camel}.h. Fill in the sequential version and the stub, then: cppar {name}")
    return 0


def play(path, rest):
    """Build any .cpp file with ParlayLib and run it, for trying things out."""
    path = os.path.abspath(path)
    if not os.path.isfile(path):
        print(f"No such file: {path}", file=sys.stderr)
        return 1
    mode = "tsan" if "--tsan" in rest else "check" if "--check" in rest else "bench"
    rest = [a for a in rest if a not in ("--check", "--tsan")]
    if not ensure_parlaylib():
        return 1
    stem = os.path.splitext(os.path.basename(path))[0]
    key = hashlib.md5(path.encode()).hexdigest()[:8]  # the same file always gets the same build
    exe = os.path.join(CACHE, "play", f"{stem}-{key}-{mode}")
    if not (os.path.exists(exe) and os.path.getmtime(exe) >= os.path.getmtime(path)):
        os.makedirs(os.path.dirname(exe), exist_ok=True)
        cxx = os.environ.get("CXX", "c++")
        cmd = [cxx, "-std=c++17", "-pthread", "-Wall", *FLAGS[mode],
               "-I", TOOLS, "-I", os.path.join(PARLAY, "include"), path, "-o", exe]
        if subprocess.run(cmd).returncode != 0:
            return 1
    return subprocess.run([exe, *rest]).returncode


def main():
    args = sys.argv[1:]
    if not args or args[0] in ("-h", "--help"):
        print(__doc__)
        return 0 if args else 2
    if args[0] == "--list":
        for b in benchmarks():
            print(b)
        return 0
    if args[0] == "--new":
        if len(args) != 2:
            print("usage: cppar --new <name>", file=sys.stderr)
            return 2
        return new(args[1])

    if args[0].endswith(".cpp"):
        return play(args[0], args[1:])

    name, rest = args[0].replace("-", "_"), args[1:]
    if name not in benchmarks():
        print(f"No benchmark named '{name}'. There are: {', '.join(benchmarks()) or 'none yet'}", file=sys.stderr)
        return 1
    mode = "tsan" if "--tsan" in rest else "check" if "--check" in rest else "bench"
    rest = [a for a in rest if a != "--tsan"]
    if mode == "tsan" and "--check" not in rest:
        rest.append("--check")

    if not ensure_parlaylib():
        return 1
    exe = build(name, mode)
    if exe is None:
        return 1
    if "--csv" not in rest:
        print(machine() + "\n")
        sys.stdout.flush()
    return subprocess.run([exe, *rest]).returncode


if __name__ == "__main__":
    sys.exit(main())
