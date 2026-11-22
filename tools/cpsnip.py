#!/usr/bin/env python3
"""Paste a snippet, yours or KACTL's, into a solution.

Usage:
    cpsnip                          list the C++ snippets in notebook/
    cpsnip seg                      list the ones whose names contain "seg"
    cpsnip FenwickTree              print it and copy it to the clipboard, to paste anywhere
    cpsnip FenwickTree --into 2179  paste it into 2179.cpp, above class Solution (or preprocess, solve, main)
    cpsnip DSU EulerTour --into A   several at once
    cpsnip FenwickTree --py         the Python version, from python/
    cpsnip --kactl                  list KACTL's snippets (the KTH library), and use them with --kactl too
    cpsnip HLD --kactl --into 2179  KACTL's heavy-light decomposition, with the segment tree it uses

Names match without case: a whole name first, then part of one. --into takes a
file, the file without .cpp (or .py), or a LeetCode number in contests/leetcode/solve/.
Snippets that a snippet includes come along, once each. Lines the file already
has are left out: #pragma once, <bits/stdc++.h>, using namespace std, and
constants like MOD and INF when the file defines them the same way. KACTL is
cloned into third_party/kactl the first time; its code uses rep, all, sz, ll,
pii, and vi, so a short prelude defines the ones the file lacks.
"""

import argparse
import os
import re
import shutil
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LEETCODE = os.path.join(REPO, "contests", "leetcode", "solve")
KACTL = os.path.join(REPO, "third_party", "kactl")
SKIP_DIRS = {"tests", "parallel", "__pycache__", "contest"}

PRELUDE_MARK = "// KACTL shorthands"
PRELUDE = PRELUDE_MARK + """
#ifndef rep
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#endif
#ifndef all
#define all(x) begin(x), end(x)
#endif
#ifndef sz
#define sz(x) (int)(x).size()
#endif
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;"""

# Includes left out: KACTL's LazySegmentTree pulls in a bump allocator, a speed trick
# that replaces operator new and never frees memory. Ask for it by name to get it.
LEFT_OUT = {("data-structures/LazySegmentTree.h", "various/BumpAllocator.h")}

# A global constant, like const int MOD = 1e9+7;
CONSTANT = re.compile(r"(?P<def>(?:static\s+)?(?:const|constexpr)\s+[\w:<>, ]+?\s+(?P<name>\w+)\s*=[^;]+;)\s*(?://.*)?")
DOC_KEY = re.compile(r"^\s*\*\s*[A-Z][A-Za-z ]*:")
DOC_DROP = re.compile(r"^\s*\*\s*(Author|Date|License|Source|Status)\s*:")

CPP = {
    "root": os.path.join(REPO, "notebook"),
    "ext": ".h",
    "file_ext": ".cpp",
    "comment": "//",
    "drop": re.compile(r"#pragma once|#include\s*<bits/stdc\+\+\.h>|using namespace std;"),
    "local": re.compile(r'#include\s*"(?P<path>[^"]+)"'),
    "anchors": [r"class Solution\b", r"(void|int|signed)\s+(preprocess|solve|main)\s*\("],
}
LANGS = {
    "cpp": CPP,
    "kactl": {**CPP, "root": os.path.join(KACTL, "content")},
    "py": {
        "root": os.path.join(REPO, "python"),
        "ext": ".py",
        "file_ext": ".py",
        "comment": "#",
        "drop": re.compile(r"(?!)"),
        "local": re.compile(r"from\s+(?P<module>[\w.]+)\s+import\s+.+"),
        "anchors": [r"class Solution\b", r"def\s+(preprocess|solve|main)\s*\(", r"if __name__\b"],
    },
}


def ensure_kactl():
    if os.path.isdir(LANGS["kactl"]["root"]):
        return True
    print("Fetching KACTL into third_party/kactl ...", file=sys.stderr)
    url = "https://github.com/kth-competitive-programming/kactl.git"
    return subprocess.run(["git", "clone", "--quiet", "--depth", "1", url, KACTL]).returncode == 0


def snippets(lang):
    root, ext = LANGS[lang]["root"], LANGS[lang]["ext"]
    found = []
    for dirpath, dirs, files in os.walk(root):
        dirs[:] = sorted(d for d in dirs if d not in SKIP_DIRS and not d.startswith("."))
        if dirpath == root and lang == "py":
            files = []  # python/template.py and leetcode.py are templates, not snippets
        found += [os.path.join(dirpath, f) for f in sorted(files) if f.endswith(ext) and f != "__init__.py"]
    return found


def name(path):
    return os.path.splitext(os.path.basename(path))[0]


def label(path, lang):
    return os.path.splitext(os.path.relpath(path, LANGS[lang]["root"]))[0]


def pick(query, paths, lang):
    """The snippet the query names, or None after saying which ones it could be."""
    q = query.lower().removesuffix(LANGS[lang]["ext"])
    scope = ""
    if "/" in q:
        scope, q = q.rsplit("/", 1)
    paths = [p for p in paths if scope in os.path.dirname(label(p, lang)).lower()]
    matches = [p for p in paths if name(p).lower() == q] or [p for p in paths if q in name(p).lower()]
    if len(matches) == 1:
        return matches[0]
    if not matches:
        print(f"No snippet matches {query!r}; run cpsnip to list them.", file=sys.stderr)
    else:
        print(f"{len(matches)} snippets match {query!r}; name one:", file=sys.stderr)
        for p in matches:
            print(f"  {label(p, lang)}", file=sys.stderr)
    return None


def show(paths, lang):
    if not paths:
        print(f"No snippets in {os.path.relpath(LANGS[lang]['root'], REPO)}.")
        return
    folders = {}
    for p in paths:
        folders.setdefault(os.path.dirname(label(p, lang)) or ".", []).append(name(p))
    width = max(len(f) for f in folders)
    for folder, names in folders.items():
        print(f"  {folder + ':':<{width + 1}}  {'  '.join(names)}")


def constants(text):
    """Each global constant's name -> its definition, with spaces removed."""
    return {m.group("name"): re.sub(r"\s+", "", m.group("def"))
            for m in (CONSTANT.fullmatch(line.strip()) for line in text.splitlines() if not line[:1].isspace()) if m}


def kactl_lines(text):
    """KACTL's source as its notebook prints it: exclude-line lines out, include-line lines in, /// comments off."""
    for line in text.splitlines():
        if "exclude-line" in line:
            continue
        if "include-line" in line:
            line = line.replace("// ", "", 1)
        had_comment = "///" in line
        line = line.split("///")[0].rstrip()
        if had_comment and not line:
            continue
        yield line


def code(path, lang, seen, blocks, existing, overrides=None, moved=None):
    """Appends path's code to blocks, after the snippets it pulls in; each file once.

    overrides maps a constant to the line defining it in a snippet that includes this one: that
    line takes the place of this file's definition, so its value wins and comes first (moved)."""
    overrides = overrides if overrides is not None else {}
    moved = moved if moved is not None else set()
    spec = LANGS[lang]
    seen.add(path)
    lines, in_doc, dropping, started = [], False, False, False
    have = constants(existing)
    text = open(path).read()
    source_lines = list(kactl_lines(text)) if lang == "kactl" else text.splitlines()
    mine = {}
    for line in source_lines if lang != "py" else []:
        m = CONSTANT.fullmatch(line.strip()) if not line[:1].isspace() else None
        if m:
            mine[m.group("name")] = line.strip()
    for line in source_lines:
        s = line.strip()
        if lang == "kactl":  # keep the Description, Time, and Usage of KACTL's header comment
            if not started and s:
                started, in_doc = True, s.startswith("/**")
            if in_doc:
                if DOC_KEY.match(line):
                    dropping = bool(DOC_DROP.match(line))
                if s.endswith("*/"):
                    in_doc = dropping = False
                elif dropping:
                    continue
                lines.append(line)
                continue
        if spec["drop"].fullmatch(s):
            continue
        m = CONSTANT.fullmatch(s) if lang != "py" and not line[:1].isspace() else None
        if m:
            const, definition = m.group("name"), re.sub(r"\s+", "", m.group("def"))
            if have.get(const) == definition:
                continue  # the file defines it the same way
            if const in overrides:
                if overrides[const] not in moved:
                    moved.add(overrides[const])
                    lines.append(overrides[const])
                continue
            if s in moved:
                continue  # already placed where an included snippet defined it
            if const in have:
                print(f"Note: {name(path)} defines {s} but the file has {const} already; "
                      f"rename or remove one of them.", file=sys.stderr)
        m = spec["local"].fullmatch(s)
        if m:
            rel = m.group("path") if lang != "py" else m.group("module").replace(".", "/") + ".py"
            dep = os.path.normpath(os.path.join(os.path.dirname(path), rel))
            pair = (os.path.relpath(path, spec["root"]), os.path.relpath(dep, spec["root"]))
            if pair in LEFT_OUT:
                print(f"Left out {pair[1]} (a bump allocator that never frees memory); "
                      f"add it with: cpsnip {name(dep)} --kactl", file=sys.stderr)
                continue
            if os.path.isfile(dep):
                if dep not in seen:
                    code(dep, lang, seen, blocks, existing, {**mine, **overrides}, moved)
                continue
        lines.append(line)
    rel = os.path.relpath(path, spec["root"])
    source = "kactl" if lang == "kactl" else "notebook"
    blocks.append((f"{spec['comment']} {source}: {rel}", "\n".join(lines).strip("\n")))


def paste_text(paths, lang, existing=""):
    seen, blocks = set(), []
    for p in paths:
        if p not in seen:
            code(p, lang, seen, blocks, existing)
    parts = []
    for mark, text in blocks:
        if mark in existing:
            print(f"Already in the file: {mark.split(': ', 1)[1]}", file=sys.stderr)
        else:
            parts.append(f"{mark}\n{text}")
    if parts and lang == "kactl" and PRELUDE_MARK not in existing:
        parts.insert(0, PRELUDE)
    return "\n\n".join(parts)


def find_target(arg, lang):
    ext = LANGS[lang]["file_ext"]
    for path in (arg, arg + ext, os.path.join(LEETCODE, arg + ext)):
        if os.path.isfile(path):
            return path
    return None


def copy_to_clipboard(text):
    for cmd in (["pbcopy"], ["wl-copy"], ["xclip", "-selection", "clipboard"]):
        if shutil.which(cmd[0]):
            return subprocess.run(cmd, input=text.encode()).returncode == 0
    return False


def main():
    ap = argparse.ArgumentParser(prog="cpsnip", description=__doc__.split("\n\n")[0],
                                 epilog=__doc__.split("\n", 1)[1], formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("names", nargs="*", help="snippet names (or part of one, to list the matches)")
    ap.add_argument("--into", metavar="FILE", help="paste into this file instead of printing")
    which = ap.add_mutually_exclusive_group()
    which.add_argument("--py", action="store_true", help="Python snippets, from python/")
    which.add_argument("--kactl", action="store_true", help="KACTL's snippets, from third_party/kactl")
    args = ap.parse_args()
    lang = "py" if args.py else "kactl" if args.kactl else "cpp"
    if lang == "kactl" and not ensure_kactl():
        print("Could not fetch KACTL (github.com/kth-competitive-programming/kactl).", file=sys.stderr)
        return 1
    paths = snippets(lang)

    if not args.names:
        if args.into:
            ap.error("name a snippet to paste")
        show(paths, lang)
        print("\ncpsnip <name> prints one and copies it; --into <file> pastes it into a solution.")
        return 0

    chosen = [pick(n, paths, lang) for n in args.names]
    if None in chosen:
        return 1

    if not args.into:
        text = paste_text(chosen, lang)
        print(text)
        if sys.stdout.isatty() and copy_to_clipboard(text + "\n"):
            print(f"\nCopied to the clipboard ({text.count(chr(10)) + 1} lines).", file=sys.stderr)
        return 0

    target = find_target(args.into, lang)
    if not target:
        ext = LANGS[lang]["file_ext"]
        print(f"No such file: {args.into} (tried {args.into}{ext} and contests/leetcode/solve/)", file=sys.stderr)
        return 1
    source = open(target).read()
    text = paste_text(chosen, lang, existing=source)
    if not text:
        return 0
    lines = source.split("\n")
    anchors = [re.compile(a) for a in LANGS[lang]["anchors"]]
    at = next((i for a in anchors for i, line in enumerate(lines) if a.match(line)), len(lines))
    where = f"above line {at + 1}" if at < len(lines) else "at the end"
    lines[at:at] = text.split("\n") + [""]
    open(target, "w").write("\n".join(lines))
    print(f"Pasted {', '.join(name(p) for p in chosen)} into {os.path.relpath(target)}, {where}.", file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
