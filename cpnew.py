#!/usr/bin/env python3
"""Create a .cpp file from a template in the leetcode-setup repo.

Usage:
    cpnew A                     -> ./A.cpp from template0.cpp
    cpnew A template1           -> ./A.cpp from template1.cpp
    cpnew codeforces/r900/A     -> codeforces/r900/A.cpp (dirs created)
    cpnew A -f                  -> overwrite if A.cpp exists
"""

import os
import shutil
import sys

ROOT = os.path.dirname(os.path.abspath(__file__))
DEFAULT_TEMPLATE = "template0"


def resolve_template(name: str) -> str:
    """Return the path to the template file for `name`."""
    candidates = []
    if os.sep in name or name.startswith("."):
        candidates.append(os.path.abspath(name))
    else:
        candidates.append(os.path.join(ROOT, name))
        candidates.append(os.path.join(os.getcwd(), name))
    for base in list(candidates):
        if not base.endswith(".cpp"):
            candidates.append(base + ".cpp")
    for path in candidates:
        if os.path.isfile(path):
            return path

    available = sorted(
        f[:-4] for f in os.listdir(ROOT)
        if f.startswith("template") and f.endswith(".cpp")
    )
    sys.exit(
        "Template not found: {}\nAvailable in {}: {}".format(
            name, ROOT, ", ".join(available) or "(none)"
        )
    )


def main() -> None:
    args = [a for a in sys.argv[1:] if a not in ("-f", "--force")]
    force = len(args) != len(sys.argv) - 1

    if not args or len(args) > 2:
        sys.exit(__doc__.strip())

    target = args[0]
    template = args[1] if len(args) > 1 else DEFAULT_TEMPLATE

    src = resolve_template(template)

    dest = target if target.endswith(".cpp") else target + ".cpp"
    dest = os.path.abspath(dest)

    if os.path.exists(dest) and not force:
        sys.exit("Refusing to overwrite existing file: {} (use -f)".format(dest))

    os.makedirs(os.path.dirname(dest), exist_ok=True)
    shutil.copyfile(src, dest)
    print("Created {} from {}".format(dest, os.path.basename(src)))


if __name__ == "__main__":
    main()
