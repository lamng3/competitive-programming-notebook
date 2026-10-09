#!/usr/bin/env python3
"""Run a library unit test by name, from any directory.

Usage:
    cpunit bloomfilter          run every test named bloomfilter (C++ and Python)
    cpunit bloomfilter --py     only the Python one
    cpunit cuckoofilter --cpp   only the C++ one
    cpunit --list               show every test that can be run

Finds notebook/**/tests/<name>_test.cpp and python/**/tests/test_<name>.py.
"""

import os
import subprocess
import sys
import tempfile

REPO_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SEARCH_DIRS = ["notebook", "python"]


def find_tests():
    """Return a list of (name, kind, path) for every test file in the repo."""
    found = []
    for top in SEARCH_DIRS:
        for root, _, files in os.walk(os.path.join(REPO_ROOT, top)):
            if os.path.basename(root) != "tests":
                continue
            for f in files:
                if f.endswith("_test.cpp"):
                    found.append((f[: -len("_test.cpp")].lower(), "cpp", os.path.join(root, f)))
                elif f.startswith("test_") and f.endswith(".py"):
                    found.append((f[len("test_"): -len(".py")].lower(), "py", os.path.join(root, f)))
    return sorted(found)


def run_cpp(path):
    with tempfile.TemporaryDirectory() as tmp:
        exe = os.path.join(tmp, "test")
        build = ["g++", "-std=c++17", "-fsanitize=address,undefined", "-Wall", "-Wextra", path, "-o", exe]
        if subprocess.run(build, cwd=os.path.dirname(path)).returncode != 0:
            return False
        return subprocess.run([exe], cwd=os.path.dirname(path)).returncode == 0


def run_py(path):
    module = os.path.basename(path)[: -len(".py")]
    cmd = [sys.executable, "-m", "unittest", "-v", module]
    return subprocess.run(cmd, cwd=os.path.dirname(path)).returncode == 0


def main():
    args = sys.argv[1:]
    tests = find_tests()

    if not args or args == ["--list"]:
        for name, kind, path in tests:
            print(f"{name:<16} {kind:<4} {os.path.relpath(path, REPO_ROOT)}")
        return 0

    only = "cpp" if "--cpp" in args else "py" if "--py" in args else None
    names = [a.lower() for a in args if not a.startswith("--")]
    if len(names) != 1:
        print(__doc__)
        return 2
    chosen = [t for t in tests if t[0] == names[0] and (only is None or t[1] == only)]
    if not chosen:
        print(f"No test named '{names[0]}'. Try: cpunit --list", file=sys.stderr)
        return 1

    ok = True
    for name, kind, path in chosen:
        print(f"=== {os.path.relpath(path, REPO_ROOT)}")
        passed = run_cpp(path) if kind == "cpp" else run_py(path)
        print(f"--- {'PASS' if passed else 'FAIL'}: {name} ({kind})\n")
        ok = ok and passed
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
