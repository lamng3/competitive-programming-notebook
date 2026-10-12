# cd(pwd, path, links): the absolute directory after `cd path` from pwd, where links
# maps an absolute directory to the absolute directory it points at (a symlink).
#   - path may be absolute ("/a/b") or relative ("../c"); "" stays in pwd
#   - "." stays, ".." goes up (and stays at "/" from the root)
#   - after every step, the path so far is resolved through links, so a link in the
#     middle of the path is followed before the next name is applied
#   - a chain of links that loops raises ValueError, like ELOOP from a real shell


def resolve(path: str, links: dict) -> str:
    seen = set()
    while path in links:
        if path in seen: raise ValueError("symlink loop at " + path)
        seen.add(path)
        path = links[path]
    return path


def cd(pwd: str, path: str, links: dict = None) -> str:
    links = links or {}
    st = [] if path.startswith("/") else [name for name in pwd.split("/") if name]
    for name in path.split("/"):
        if name == "" or name == ".": continue
        if name == "..":
            if st: st.pop()
            continue
        st.append(name)
        cur = "/" + "/".join(st)
        target = resolve(cur, links)
        if target != cur: st = [x for x in target.split("/") if x]
    return "/" + "/".join(st)
