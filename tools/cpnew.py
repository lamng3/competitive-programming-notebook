#!/usr/bin/env python3
"""Create a .cpp (or .py) file from a template.

Usage:
    cpnew A                     -> ./A.cpp from contest.cpp
    cpnew A leetcode            -> ./A.cpp from leetcode.cpp
    cpnew codeforces/r900/A     -> codeforces/r900/A.cpp (dirs created)
    cpnew A -f                  -> overwrite if A.cpp exists
    cpnew A --py                -> ./A.py from python/template.py
    cpnew A leetcode --py       -> ./A.py from python/leetcode.py
"""

import os
import shutil
import sys

REPO_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TEMPLATES_DIR = os.path.join(REPO_ROOT, "templates")
DEFAULT_TEMPLATE = "contest"
EXT = ".cpp"


def resolve_template(name: str) -> str:
    """Return the path to the template file for `name`."""
    candidates = []
    if os.sep in name or name.startswith("."):
        candidates.append(os.path.abspath(name))
    else:
        candidates.append(os.path.join(TEMPLATES_DIR, name))
        candidates.append(os.path.join(os.getcwd(), name))
    for base in list(candidates):
        if not base.endswith(EXT):
            candidates.append(base + EXT)
    for path in candidates:
        if os.path.isfile(path):
            return path

    available = sorted(
        f[: -len(EXT)] for f in os.listdir(TEMPLATES_DIR)
        if f.endswith(EXT)
    )
    sys.exit(
        "Template not found: {}\nAvailable in {}: {}".format(
            name, TEMPLATES_DIR, ", ".join(available) or "(none)"
        )
    )


def main() -> None:
    global TEMPLATES_DIR, DEFAULT_TEMPLATE, EXT
    flags = [a for a in sys.argv[1:] if a.startswith("-")]
    args = [a for a in sys.argv[1:] if not a.startswith("-")]
    force = "-f" in flags or "--force" in flags
    if "--py" in flags:
        TEMPLATES_DIR = os.path.join(REPO_ROOT, "python")
        DEFAULT_TEMPLATE = "template"
        EXT = ".py"

    if not args or len(args) > 2:
        sys.exit(__doc__.strip())

    target = args[0]
    template = args[1] if len(args) > 1 else DEFAULT_TEMPLATE

    src = resolve_template(template)

    dest = target if target.endswith(EXT) else target + EXT
    dest = os.path.abspath(dest)

    if os.path.exists(dest) and not force:
        sys.exit("Refusing to overwrite existing file: {} (use -f)".format(dest))

    os.makedirs(os.path.dirname(dest), exist_ok=True)
    shutil.copyfile(src, dest)
    print("Created {} from {}".format(dest, os.path.basename(src)))


if __name__ == "__main__":
    main()
