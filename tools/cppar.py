#!/usr/bin/env python3
"""Build and run parallel code with ParlayLib, from any directory.

Usage:
    cppar hillis_steele_scan                  notebook/parallel/*/hillis_steele_scan.cpp on 1, 2, 4, ... threads
    cppar hillis_steele_scan --check          the same on sizes from 0 to 2^20, built with sanitizers
    cppar hillis_steele_scan --check --tsan   the same with ThreadSanitizer, to look for data races
    cppar hillis_steele_scan --lg 22          at n = 2^22 (or --n 1000)
    cppar hillis_steele_scan --threads 1 8    on these thread counts
    cppar prefix_sums                         every file in notebook/parallel/prefix_sums/
    cppar prime_sieve                         a file without parbench::run just runs once
    cppar path/to/file.cpp                    any .cpp file
    cppar --list                              the problems and their files
    cppar --new prefix_sums/blocked_scan      a new file from a template, in notebook/parallel/prefix_sums/
    cppar --new blocked_scan                  the same, run from inside notebook/parallel/prefix_sums/

A file times functions with parbench::run (tools/parbench.h): the first run is
the baseline, and every later one is checked against its answer. The first
use fetches ParlayLib into third_party/parlaylib. Builds are cached in .cppar/
until the file changes.
"""

import hashlib
import os
import platform
import subprocess
import sys

REPO_ROOT = os.path.dirname(os.path.dirname(os.path.realpath(__file__)))  # real, to compare with the current folder
PAR_DIR = os.path.join(REPO_ROOT, "notebook", "parallel")
TOOLS = os.path.join(REPO_ROOT, "tools")
PARLAY = os.path.join(REPO_ROOT, "third_party", "parlaylib")
CACHE = os.path.join(REPO_ROOT, ".cppar")
CHECK_SIZES = [0, 1, 2, 3, 4, 5, 7, 8, 9, 16, 17, 100, 1000, 1023, 1024, 4097, 65536, 100003, 1 << 20]

FLAGS = {
    "run": ["-O3", "-DNDEBUG"],
    "check": ["-O1", "-g", "-fno-omit-frame-pointer", "-fsanitize=address,undefined", "-fno-sanitize-recover=undefined"],
    "tsan": ["-O1", "-g", "-fsanitize=thread"],
}

TEMPLATE = """\
// {title}. Check: cppar {name} --check. Time: cppar {name}.
#include <cstddef>

#include <parlay/parallel.h>
#include <parlay/primitives.h>
#include <parlay/sequence.h>

#include <parbench.h>

parlay::sequence<long long> {name}_sequential(const parlay::sequence<long long>& a) {{
    return a;
}}

parlay::sequence<long long> {name}_parallel(const parlay::sequence<long long>& a) {{
    // TODO
    return {{}};
}}

int main() {{
    std::size_t n = parbench::n(1 << 24);
    auto a = parlay::tabulate(n, [](std::size_t i) {{
        return static_cast<long long>(parlay::hash64(i) % 100);
    }});

    parbench::run("sequential", [&] {{ return {name}_sequential(a); }});  // the baseline
    parbench::run("{label}", [&] {{ return {name}_parallel(a); }});
}}
"""


def problems():
    """{folder in notebook/parallel/, at any depth: [its .cpp files]}."""
    out = {}
    for root, dirs, files in os.walk(PAR_DIR):
        dirs[:] = sorted(d for d in dirs if not d.startswith("."))
        cpps = sorted(f for f in files if f.endswith(".cpp"))
        if cpps and root != PAR_DIR:
            out[os.path.relpath(root, PAR_DIR)] = [os.path.join(root, f) for f in cpps]
    return out


def resolve(arg):
    """The .cpp files an argument names: a path, a folder in notebook/parallel/ (with its subfolders), or a file's name."""
    if arg.endswith(".cpp"):
        return [os.path.abspath(arg)]
    name = arg.replace("-", "_").strip("/")
    found = problems()
    in_folder = [p for d, paths in found.items() if d == name or d.startswith(name + "/") for p in paths]
    return in_folder or [p for paths in found.values() for p in paths if os.path.basename(p) == name + ".cpp"]


def ensure_parlaylib():
    if os.path.isdir(PARLAY):
        return True
    print("Fetching ParlayLib into third_party/parlaylib ...", file=sys.stderr)
    url = "https://github.com/cmuparlay/parlaylib.git"
    return subprocess.run(["git", "clone", "--quiet", "--depth", "1", url, PARLAY]).returncode == 0


def build(path, mode):
    """Compile path for mode, unless the cached build is newer than it and parbench.h. Compiler errors print as usual."""
    stem = os.path.splitext(os.path.basename(path))[0]
    key = hashlib.md5(path.encode()).hexdigest()[:8]  # the same file always gets the same build
    exe = os.path.join(CACHE, f"{stem}-{key}-{mode}")
    newest = max(os.path.getmtime(path), os.path.getmtime(os.path.join(TOOLS, "parbench.h")))
    if os.path.exists(exe) and os.path.getmtime(exe) >= newest:
        return exe
    os.makedirs(CACHE, exist_ok=True)
    cxx = os.environ.get("CXX", "c++")
    cmd = [cxx, "-std=c++17", "-pthread", "-Wall", *FLAGS[mode],
           "-I", TOOLS, "-I", os.path.join(PARLAY, "include"), path, "-o", exe]
    print(f"Compiling {os.path.basename(path)} ...", file=sys.stderr)
    if subprocess.run(cmd).returncode != 0:
        print(f"\nCompile failed: fix the errors above in {path}", file=sys.stderr)
        return None
    return exe


def machine():
    name = platform.processor() or platform.machine()
    try:
        if platform.system() == "Darwin":
            name = subprocess.run(["sysctl", "-n", "machdep.cpu.brand_string"], capture_output=True, text=True).stdout.strip()
        elif os.path.exists("/proc/cpuinfo"):
            with open("/proc/cpuinfo") as f:
                name = next((l.split(":", 1)[1].strip() for l in f if l.startswith("model name")), name)
    except OSError:
        pass
    return f"{name}, {os.cpu_count()} hardware threads"


def table(head, rows, numbers=True):
    """Print a Markdown table: the first column left-aligned, the rest right-aligned if they hold numbers."""
    w = [max(3, len(h), *(len(r[j]) for r in rows if j < len(r))) for j, h in enumerate(head)]
    right = [numbers and j > 0 for j in range(len(head))]

    def line(r):
        cells = [(r[j] if j < len(r) else "").rjust(w[j]) if right[j] else (r[j] if j < len(r) else "").ljust(w[j])
                 for j in range(len(head))]
        print("| " + " | ".join(cells) + " |")

    line(head)
    print("|" + "|".join(("-" * (w[j] + 1) + ":") if right[j] else (":" + "-" * (w[j] + 1)) for j in range(len(head))) + "|")
    for r in rows:
        line(r)


def ms_text(ms):
    return f"{ms:.3f} ms" if ms < 1 else f"{ms:.2f} ms" if ms < 10 else f"{ms:.1f} ms" if ms < 100 else f"{ms:.0f} ms"


def size_text(n):
    s = f"{n:,}"
    return f"2^{n.bit_length() - 1} = {s}" if n and n & (n - 1) == 0 else s


def execute(exe, env):
    """Run the program, splitting parbench's lines from the program's own output."""
    proc = subprocess.run([exe], env=env, capture_output=True, text=True)
    results, other, n = [], [], None
    for line in proc.stdout.splitlines():
        if line.startswith("@parbench\t"):
            _, name, ms, status = (line.split("\t", 3) + [""])[:4]
            results.append((name, float(ms), status))
        elif line.startswith("@parbench-n\t"):
            n = int(line.split("\t")[1])
        else:
            other.append(line)
    return proc, results, other, n


def progress(text):
    """A status line that rewrites itself, only in a terminal."""
    if sys.stderr.isatty():
        print("\r" + text.ljust(50), end="", file=sys.stderr, flush=True)


def crashed(proc, what):
    if proc.returncode == 0:
        return False
    print(f"\nThe program crashed {what} (exit code {proc.returncode}). What it printed:\n", file=sys.stderr)
    sys.stderr.write(proc.stdout + proc.stderr)
    return True


def sweep(path, exe, threads, n):
    names, ms, status, output, size = [], {}, {}, None, None
    for k, p in enumerate(threads):
        progress(f"Running on {p} thread{'s' if p > 1 else ''} ({k + 1} of {len(threads)}) ...")
        env = dict(os.environ, PARLAY_NUM_THREADS=str(p), PARBENCH_OUT="1")
        if n:
            env["PARBENCH_N"] = str(n)
        proc, results, other, size = execute(exe, env)
        if crashed(proc, f"on {p} threads"):
            return 1
        if output is None:
            output = other
        for name, t, s in results:
            if name not in ms:
                names.append(name)
                ms[name] = {}
            ms[name][p] = t
            if s and name not in status:
                status[name] = s if p == threads[0] else f"{s} (on {p} threads)"
    progress("")
    if sys.stderr.isatty():
        print("\r", end="", file=sys.stderr)

    if output:
        print("Output:\n" + "\n".join(output) + "\n")
    if not names:
        print("No parbench::run calls ran.")
        return 0
    base = names[0]
    head = ["function"] + [f"{p} thread" + ("s" if p > 1 else "") for p in threads]
    timed = [x for x in names if x not in status]
    print(f"{os.path.basename(path)} · n = {size_text(size) if size is not None else '?'} · median of 7 runs, after 2 warm-ups\n")
    print("Time per run\n")
    table(head, [[x] + [ms_text(ms[x][p]) if p in ms[x] else "" for p in threads] for x in timed])
    others = [x for x in timed if x != base]
    if base in timed and others:
        print(f"\nSpeedup over {base}, run alongside: above 1x is faster\n")
        rows = [[x] + [f"{ms[base][p] / ms[x][p]:.2f}x" if p in ms[x] and ms[x][p] > 0 else "" for p in threads]
                for x in others]
        table(head, rows)
    if status:
        print("\nNot timed\n")
        table(["function", "why"], [[x, status[x]] for x in names if x in status], numbers=False)
    return 0


def check(path, exe):
    first_problem, names = {}, []
    for k, n in enumerate(CHECK_SIZES):
        progress(f"Checking n = {n:,} ({k + 1} of {len(CHECK_SIZES)}) ...")
        env = dict(os.environ, PARBENCH_OUT="1", PARBENCH_CHECK="1", PARBENCH_N=str(n),
                   UBSAN_OPTIONS="print_stacktrace=1")  # undefined behavior stops the run and shows where
        proc, results, _, _ = execute(exe, env)
        if crashed(proc, f"at n = {n:,}"):
            return 1
        for name, _, s in results:
            if name not in names:
                names.append(name)
            if s and name not in first_problem:
                first_problem[name] = s if s == "not written yet" else f"FAIL at n = {n:,}: {s}"
    progress("")
    if sys.stderr.isatty():
        print("\r", end="", file=sys.stderr)
    if not names:
        print("No parbench::run calls ran.")
        return 0
    print(f"{os.path.basename(path)}: every function against {names[0]}, on {len(CHECK_SIZES)} sizes from 0 to 2^20\n")
    rows = [[names[0], "baseline"]] + [[x, first_problem.get(x, "pass")] for x in names[1:]]
    table(["function", "result"], rows, numbers=False)
    return 1 if first_problem else 0


def new(arg):
    """A file from TEMPLATE. <folder>/<name> goes in that folder of notebook/parallel/. A bare name goes in the
    current folder when that is inside notebook/parallel/, and in a new folder of its own otherwise."""
    arg = arg.replace("-", "_")
    if arg.endswith(".cpp"):
        arg = arg[:-4]
    folder, name = os.path.split(arg)
    if not name.isidentifier():
        print(f"{name or arg} can't name the C++ functions in the file: use letters, digits, and _, "
              "not starting with a digit", file=sys.stderr)
        return 2
    here = os.path.realpath(os.getcwd())
    if folder:
        folder = os.path.normpath(os.path.join(PAR_DIR, folder))
    elif here.startswith(PAR_DIR + os.sep):
        folder = here
    else:
        folder = os.path.join(PAR_DIR, name)
    if not folder.startswith(PAR_DIR + os.sep):
        print(f"{arg} would be outside notebook/parallel/", file=sys.stderr)
        return 2
    path = os.path.join(folder, name + ".cpp")
    if os.path.exists(path):
        print(f"{os.path.relpath(path, REPO_ROOT)} already exists", file=sys.stderr)
        return 1
    os.makedirs(folder, exist_ok=True)
    with open(path, "w") as f:
        f.write(TEMPLATE.format(name=name, title=name.replace("_", " ").capitalize(), label=name.replace("_", "-")))
    print(f"Created {os.path.relpath(path, REPO_ROOT)}. Write the functions, then: cppar {name} --check")
    return 0


def main():
    args = sys.argv[1:]
    if not args or args[0] in ("-h", "--help"):
        print(__doc__)
        return 0 if args else 2
    if args[0] == "--list":
        for d, paths in problems().items():
            print(f"{d}: {', '.join(os.path.basename(p)[:-4] for p in paths)}")
        return 0
    if args[0] == "--new":
        if len(args) != 2:
            print("usage: cppar --new [<folder>/]<name>", file=sys.stderr)
            return 2
        return new(args[1])

    paths, rest = resolve(args[0]), args[1:]
    if not paths or not all(os.path.isfile(p) for p in paths):
        known = ", ".join(f"{d}/{os.path.basename(p)[:-4]}" for d, ps in problems().items() for p in ps)
        print(f"Nothing named {args[0]}. In notebook/parallel/: {known or 'nothing yet'}", file=sys.stderr)
        return 1
    threads, n, i = [], None, 0
    flags = set()
    while i < len(rest):
        a = rest[i]
        if a in ("--check", "--tsan"):
            flags.add(a)
        elif a in ("--lg", "--n") and i + 1 < len(rest):
            n = (1 << int(rest[i + 1])) if a == "--lg" else int(rest[i + 1])
            i += 1
        elif a == "--threads":
            while i + 1 < len(rest) and rest[i + 1].isdigit():
                threads.append(int(rest[i + 1]))
                i += 1
        else:
            print(f"Unknown option {a}\n{__doc__}", file=sys.stderr)
            return 2
        i += 1

    if not ensure_parlaylib():
        return 1
    mode = "tsan" if "--tsan" in flags else "check" if "--check" in flags else "run"
    if not threads:
        p, top = 1, os.cpu_count() or 1
        while p < top:
            threads.append(p)
            p *= 2
        threads.append(top)
    print(machine() + "\n", flush=True)
    status = 0
    for k, path in enumerate(paths):
        if k:
            print("\n" + "-" * 60 + "\n", flush=True)
        status = max(status, run_file(path, mode, threads, n))
    return status


def run_file(path, mode, threads, n):
    exe = build(path, mode)
    if exe is None:
        return 1
    with open(path) as f:
        uses_parbench = "parbench::run" in f.read()
    if not uses_parbench:
        return subprocess.run([exe]).returncode  # a plain program: run it once, as it is
    if mode != "run":
        return check(path, exe)
    return sweep(path, exe, threads, n)


if __name__ == "__main__":
    sys.exit(main())
