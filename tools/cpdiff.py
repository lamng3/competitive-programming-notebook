#!/usr/bin/env python3
"""Compare a solution against a brute force on random tests, or against test files.

Usage:
    cpdiff A                    stress test: A.cpp vs A_brute.cpp on tests from A_gen.cpp (100 rounds)
    cpdiff A -n 1000            1000 rounds
    cpdiff A --seed 42          replay round 1 from seed 42 (seeds run 42, 43, ...)
    cpdiff A --brute naive --gen mygen    pick the brute force and generator by name
    cpdiff A --init             create A_brute.cpp and A_gen.cpp from templates/
    cpdiff A tests/             check every tests/X.in against tests/X.out (or .ans)
    cpdiff A 1.in 1.out         check one input against one expected output
    cpdiff A 1.in               check one input against the brute force

Options:
    --tl SEC      time limit per run, default 2 (the generator and brute get 5x that)
    --eps EPS     treat numbers within EPS (absolute or relative) as equal
    --exact       compare bytes instead of whitespace-separated tokens
    --keep-going  in file mode, keep checking after the first failure

A program is a .cpp (compiled with -O2 -DONLINE_JUDGE, cached by mtime) or a .py file.
The brute force defaults to A_brute, brute, or naive; the generator to A_gen or gen
(.cpp or .py, looked up next to A). The generator is run as `gen <seed>` and prints one test.
A failing test is saved to .cpdiff/A/ next to the solution as fail.in, fail.ans, fail.out.
"""

import os
import re
import shutil
import signal
import subprocess
import sys
import time

REPO_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TEMPLATES_DIR = os.path.join(REPO_ROOT, "templates")
CXX_FLAGS = ["-std=c++20", "-O2", "-DONLINE_JUDGE", "-w"]
INPUT_EXTS = (".in", ".inp")
ANSWER_EXTS = (".out", ".ans", ".ok", ".a")

RED, GREEN, YELLOW, DIM, BOLD, RESET = (
    ("\033[31m", "\033[32m", "\033[33m", "\033[2m", "\033[1m", "\033[0m")
    if sys.stdout.isatty() else ("",) * 6
)
TTY = sys.stdout.isatty()
CLEAR = "\r\033[K" if TTY else ""
SHOW_LINES = 25


def die(msg, code=2):
    print(f"{RED}{msg}{RESET}", file=sys.stderr)
    sys.exit(code)


# ---------- locating and building programs ----------

def find_program(name, base_dir):
    """Resolve `name` to an existing .cpp/.py path, trying it as given, then with extensions."""
    tries = [name] if os.path.isabs(name) else [name, os.path.join(base_dir, name)]
    for t in tries:
        for cand in (t, t + ".cpp", t + ".py"):
            if os.path.isfile(cand):
                return os.path.abspath(cand)
    return None


def find_role(stem, base_dir, names):
    """First existing program among `names` (with {stem} substituted) in base_dir."""
    for n in names:
        path = find_program(os.path.join(base_dir, n.format(stem=stem)), base_dir)
        if path:
            return path
    return None


class Program:
    def __init__(self, path, build_dir):
        self.path = path
        self.name = os.path.basename(path)
        stem, ext = os.path.splitext(self.name)
        self.is_py = ext == ".py"
        self.exe = None if self.is_py else os.path.join(build_dir, stem)

    def build(self):
        if self.is_py:
            return
        if os.path.exists(self.exe) and os.path.getmtime(self.exe) >= os.path.getmtime(self.path):
            return
        print(f"{DIM}compiling {self.name}...{RESET}", flush=True)
        cmd = ["g++", *CXX_FLAGS, self.path, "-o", self.exe]
        r = subprocess.run(cmd, capture_output=True, text=True)
        if r.returncode != 0:
            sys.stderr.write(r.stderr)
            die(f"Compilation failed: {self.path}")

    def cmd(self, *args):
        if self.is_py:
            return [sys.executable, self.path, *args]
        return [self.exe, *args]

    def run(self, stdin, tl, *args):
        """Return (verdict, stdout, stderr, seconds). verdict is OK, TLE, or RE <code>."""
        start = time.perf_counter()
        try:
            r = subprocess.run(self.cmd(*args), input=stdin, capture_output=True, timeout=tl,
                               cwd=os.path.dirname(self.path))
        except subprocess.TimeoutExpired as e:
            return "TLE", e.stdout or b"", e.stderr or b"", tl
        took = time.perf_counter() - start
        if r.returncode == 0:
            verdict = "OK"
        elif r.returncode < 0:
            try:
                verdict = f"RE ({signal.Signals(-r.returncode).name})"
            except ValueError:
                verdict = f"RE (signal {-r.returncode})"
        else:
            verdict = f"RE (exit {r.returncode})"
        return verdict, r.stdout, r.stderr, took


# ---------- comparing outputs ----------

def same_token(a, b, eps):
    if a == b:
        return True
    if eps is None:
        return False
    try:
        x, y = float(a), float(b)
    except ValueError:
        return False
    return abs(x - y) <= eps or abs(x - y) <= eps * max(abs(x), abs(y))


def compare(expected, got, exact, eps):
    """Return None if outputs match, else a short description of the first difference."""
    if exact:
        if expected == got:
            return None
        e, g = expected.decode(errors="replace").splitlines(), got.decode(errors="replace").splitlines()
        for i in range(max(len(e), len(g))):
            el = e[i] if i < len(e) else "<EOF>"
            gl = g[i] if i < len(g) else "<EOF>"
            if el != gl:
                return f"line {i + 1}: expected {el!r}, got {gl!r}"
        return "outputs differ in trailing whitespace or newlines"

    e_lines = expected.decode(errors="replace").split("\n")
    g_lines = got.decode(errors="replace").split("\n")
    e_tok = [(t, i + 1) for i, line in enumerate(e_lines) for t in line.split()]
    g_tok = [(t, i + 1) for i, line in enumerate(g_lines) for t in line.split()]
    for k in range(min(len(e_tok), len(g_tok))):
        if not same_token(e_tok[k][0], g_tok[k][0], eps):
            return (f"token {k + 1} (line {g_tok[k][1]}): "
                    f"expected {e_tok[k][0]!r}, got {g_tok[k][0]!r}")
    if len(e_tok) != len(g_tok):
        return f"expected {len(e_tok)} tokens, got {len(g_tok)}"
    return None


def show(title, data, color=""):
    text = data.decode(errors="replace").rstrip("\n")
    lines = text.split("\n") if text else ["<empty>"]
    print(f"{BOLD}{title}{RESET}")
    for line in lines[:SHOW_LINES]:
        print(f"  {color}{line}{RESET}")
    if len(lines) > SHOW_LINES:
        print(f"  {DIM}... {len(lines) - SHOW_LINES} more lines{RESET}")


def show_stderr(who, err):
    if err.strip():
        show(f"{who} stderr:", err, DIM)


# ---------- modes ----------

def init(stem, base_dir, force):
    made = []
    for suffix, template in (("_brute", "contest.cpp"), ("_gen", "gen.cpp")):
        dest = os.path.join(base_dir, f"{stem}{suffix}.cpp")
        if os.path.exists(dest) and not force:
            print(f"{YELLOW}exists, skipped:{RESET} {dest}")
            continue
        shutil.copyfile(os.path.join(TEMPLATES_DIR, template), dest)
        made.append(dest)
    for p in made:
        print(f"Created {p}")
    return 0


def stress(sol, brute, gen, rounds, seed, tl, exact, eps, fail_dir):
    print(f"{BOLD}{sol.name}{RESET} vs {BOLD}{brute.name}{RESET} "
          f"on {BOLD}{gen.name}{RESET}, {rounds} rounds from seed {seed}")
    slow = 0.0
    for i in range(rounds):
        s = seed + i
        if TTY:
            print(f"{CLEAR}{DIM}round {i + 1}/{rounds}  seed {s}{RESET}", end="", flush=True)

        v, test, err, _ = gen.run(None, tl * 5, str(s))
        if v != "OK":
            print(CLEAR, end="")
            show_stderr(gen.name, err)
            die(f"Generator {v} on seed {s}", 1)

        v, ans, err_b, _ = brute.run(test, tl * 5)
        if v != "OK":
            print(CLEAR, end="")
            show("input:", test)
            show_stderr(brute.name, err_b)
            die(f"Brute force {v} on seed {s}", 1)

        v, out, err_s, took = sol.run(test, tl)
        slow = max(slow, took)
        problem = None if v != "OK" else compare(ans, out, exact, eps)
        if v == "OK" and problem is None:
            continue

        print(CLEAR, end="")
        save_failure(fail_dir, test, ans, out)
        print(f"{RED}{BOLD}{'WRONG ANSWER' if v == 'OK' else v}{RESET} on round {i + 1}, seed {s}")
        if problem:
            print(f"{RED}{problem}{RESET}")
        show("input:", test)
        show(f"expected ({brute.name}):", ans, GREEN)
        show(f"got ({sol.name}):", out, RED)
        show_stderr(sol.name, err_s)
        rel = os.path.relpath(fail_dir)
        print(f"{DIM}saved to {rel}/fail.in, fail.ans, fail.out; replay with --seed {s} -n 1{RESET}")
        return 1

    print(f"{CLEAR}{GREEN}{BOLD}All {rounds} rounds passed{RESET} "
          f"(seeds {seed}..{seed + rounds - 1}, slowest {slow * 1000:.0f} ms)")
    return 0


def save_failure(fail_dir, test, ans, out):
    os.makedirs(fail_dir, exist_ok=True)
    for name, data in (("fail.in", test), ("fail.ans", ans), ("fail.out", out)):
        with open(os.path.join(fail_dir, name), "wb") as f:
            f.write(data)


def collect_cases(paths):
    """Turn the positional file arguments into a list of (input_path, answer_path or None)."""
    if len(paths) == 1 and os.path.isdir(paths[0]):
        d = paths[0]
        cases = []
        for f in sorted(os.listdir(d), key=natural_key):
            stem, ext = os.path.splitext(f)
            if ext not in INPUT_EXTS:
                continue
            ans = next((os.path.join(d, stem + a) for a in ANSWER_EXTS
                        if os.path.isfile(os.path.join(d, stem + a))), None)
            cases.append((os.path.join(d, f), ans))
        if not cases:
            die(f"No {'/'.join(INPUT_EXTS)} files in {d}")
        return cases
    for p in paths:
        if not os.path.isfile(p):
            die(f"No such file: {p}")
    if len(paths) == 1:
        return [(paths[0], None)]
    if len(paths) == 2:
        return [(paths[0], paths[1])]
    die("Pass a directory, an input file, or an input and an answer file.")


def natural_key(s):
    return [int(t) if t.isdigit() else t for t in re.split(r"(\d+)", s)]


def check_files(sol, brute, cases, tl, exact, eps, keep_going):
    passed = 0
    for inp, ans_path in cases:
        label = os.path.relpath(inp)
        with open(inp, "rb") as f:
            test = f.read()
        if ans_path:
            with open(ans_path, "rb") as f:
                ans = f.read()
            ref = os.path.basename(ans_path)
        else:
            v, ans, err_b, _ = brute.run(test, tl * 5)
            if v != "OK":
                show_stderr(brute.name, err_b)
                die(f"Brute force {v} on {label}", 1)
            ref = brute.name

        v, out, err_s, took = sol.run(test, tl)
        problem = None if v != "OK" else compare(ans, out, exact, eps)
        if v == "OK" and problem is None:
            passed += 1
            print(f"{GREEN}OK{RESET}   {label}  {DIM}{took * 1000:.0f} ms{RESET}")
            continue

        print(f"{RED}{BOLD}{'WA' if v == 'OK' else v}{RESET}   {label}"
              + (f"  {RED}{problem}{RESET}" if problem else ""))
        show("input:", test)
        show(f"expected ({ref}):", ans, GREEN)
        show(f"got ({sol.name}):", out, RED)
        show_stderr(sol.name, err_s)
        if not keep_going:
            break

    total = len(cases)
    color = GREEN if passed == total else RED
    print(f"{color}{BOLD}{passed}/{total} passed{RESET}")
    return 0 if passed == total else 1


# ---------- argument parsing ----------

def parse_args(argv):
    opts = {"n": 100, "seed": None, "tl": 2.0, "eps": None, "exact": False, "brute": None,
            "gen": None, "init": False, "force": False, "keep_going": False}
    takes_value = {"-n": "n", "--seed": "seed", "--tl": "tl", "--eps": "eps",
                   "--brute": "brute", "--gen": "gen"}
    flags = {"--exact": "exact", "--init": "init", "-f": "force", "--force": "force",
             "--keep-going": "keep_going"}
    pos = []
    it = iter(argv)
    for a in it:
        if a in ("-h", "--help"):
            print(__doc__.strip())
            sys.exit(0)
        if a in takes_value:
            val = next(it, None)
            if val is None:
                die(f"{a} needs a value")
            opts[takes_value[a]] = val
        elif a in flags:
            opts[flags[a]] = True
        elif a.startswith("-") and a != "-":
            die(f"Unknown option {a}\n\n{__doc__.strip()}")
        else:
            pos.append(a)
    try:
        opts["n"] = int(opts["n"])
        opts["tl"] = float(opts["tl"])
        if opts["seed"] is not None:
            opts["seed"] = int(opts["seed"])
        if opts["eps"] is not None:
            opts["eps"] = float(opts["eps"])
    except ValueError as e:
        die(f"Bad option value: {e}")
    return opts, pos


def main():
    opts, pos = parse_args(sys.argv[1:])
    if not pos:
        print(__doc__.strip())
        return 2

    target = pos[0]
    stem = os.path.splitext(os.path.basename(target))[0]
    base_dir = os.path.dirname(os.path.abspath(target if os.path.splitext(target)[1] else target + ".cpp"))

    if opts["init"]:
        return init(stem, base_dir, opts["force"])

    sol_path = find_program(target, os.getcwd())
    if not sol_path:
        die(f"No such solution: {target} (tried {target}, {target}.cpp, {target}.py)")
    base_dir = os.path.dirname(sol_path)
    stem = os.path.splitext(os.path.basename(sol_path))[0]

    work = os.path.join(base_dir, ".cpdiff", stem)
    os.makedirs(work, exist_ok=True)

    def pick(role, explicit, defaults):
        if explicit:
            path = find_program(explicit, base_dir)
            if not path:
                die(f"No such {role}: {explicit}")
            return path
        return find_role(stem, base_dir, defaults)

    brute_path = pick("brute force", opts["brute"], ["{stem}_brute", "{stem}brute", "brute", "naive"])
    files = pos[1:]
    if files:
        cases = collect_cases(files)
        if any(a is None for _, a in cases) and not brute_path:
            die(f"Some inputs have no answer file and there is no brute force "
                f"({stem}_brute.cpp or brute.cpp) to produce one.")
        sol = Program(sol_path, work)
        brute = Program(brute_path, work) if brute_path else None
        for p in (sol, brute):
            if p:
                p.build()
        return check_files(sol, brute, cases, opts["tl"], opts["exact"], opts["eps"], opts["keep_going"])

    gen_path = pick("generator", opts["gen"], ["{stem}_gen", "{stem}gen", "gen"])
    missing = [r for r, p in (("brute force", brute_path), ("generator", gen_path)) if not p]
    if missing:
        die(f"Missing {' and '.join(missing)} next to {os.path.basename(sol_path)}.\n"
            f"Looked for {stem}_brute / brute / naive and {stem}_gen / gen (.cpp or .py).\n"
            f"Create both with: cpdiff {target} --init")
    if os.path.samefile(brute_path, sol_path):
        die("The brute force and the solution are the same file.")

    sol, brute, gen = (Program(p, work) for p in (sol_path, brute_path, gen_path))
    for p in (gen, brute, sol):
        p.build()
    seed = opts["seed"] if opts["seed"] is not None else int(time.time() * 1000) % 10**9
    return stress(sol, brute, gen, opts["n"], seed, opts["tl"], opts["exact"], opts["eps"], work)


if __name__ == "__main__":
    try:
        sys.exit(main())
    except KeyboardInterrupt:
        print(f"\n{YELLOW}interrupted{RESET}")
        sys.exit(130)
