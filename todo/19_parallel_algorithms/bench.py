#!/usr/bin/env python3
"""Time the scans in this folder on several thread counts.

Usage, from anywhere:
    python3 todo/19_parallel_algorithms/bench.py                    n = 2^26, on 1, 2, 4, 8, 12 threads
    python3 todo/19_parallel_algorithms/bench.py --lg 22 --threads 1 8
    python3 todo/19_parallel_algorithms/bench.py --setup            only fetch ParlayLib

Clones ParlayLib into third_party/parlaylib the first time (cpunit needs it
too), builds bench.cpp with -O3, and runs it once per thread count.
"""

import argparse
import os
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
REPO_ROOT = os.path.dirname(os.path.dirname(HERE))
PARLAY = os.path.join(REPO_ROOT, "third_party", "parlaylib")


def main():
    ap = argparse.ArgumentParser(description="Time the parallel scans.")
    ap.add_argument("--lg", type=int, default=26, help="n = 2^lg elements (default 26)")
    ap.add_argument("--threads", type=int, nargs="+", default=[1, 2, 4, 8, 12])
    ap.add_argument("--setup", action="store_true", help="only fetch ParlayLib")
    args = ap.parse_args()

    if not os.path.isdir(PARLAY):
        url = "https://github.com/cmuparlay/parlaylib.git"
        if subprocess.run(["git", "clone", "--depth", "1", url, PARLAY]).returncode != 0:
            return 1
    if args.setup:
        return 0

    with tempfile.TemporaryDirectory() as tmp:
        exe = os.path.join(tmp, "bench")
        cxx = os.environ.get("CXX", "c++")
        build = [cxx, "-O3", "-std=c++17", "-pthread", "-Wall", "-I", os.path.join(PARLAY, "include"),
                 os.path.join(HERE, "bench.cpp"), "-o", exe]
        if subprocess.run(build).returncode != 0:
            return 1
        print("method,threads,n,ms,Gelem/s,speedup", flush=True)
        for p in args.threads:
            env = dict(os.environ, PARLAY_NUM_THREADS=str(p))
            if subprocess.run([exe, str(args.lg)], env=env).returncode != 0:
                return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
