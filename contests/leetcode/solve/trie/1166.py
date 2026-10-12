from collections import defaultdict


class Node:
    def __init__(self):
        self.children = defaultdict(Node) # name -> node
        self.value = -1                   # -1 until a path is created here


class FileSystem:

    def __init__(self):
        self.root = Node()

    # follow names one by one; None if any is missing, and never creates
    def _walk(self, names: list) -> Node:
        node = self.root
        for name in names:
            node = node.children.get(name) # .get, so a failed walk adds nothing
            if node is None: return None
        return node

    def createPath(self, path: str, value: int) -> bool:
        names = [name for name in path.split("/") if name]
        if not names: return False
        par = self._walk(names[:-1])
        # parent missing, or the path already exists
        if par is None or names[-1] in par.children: return False
        par.children[names[-1]].value = value # [] creates the new node
        return True

    def get(self, path: str) -> int:
        node = self._walk([name for name in path.split("/") if name])
        return node.value if node is not None else -1

# Your FileSystem object will be instantiated and called as such:
# obj = FileSystem()
# param_1 = obj.createPath(path,value)
# param_2 = obj.get(path)
