import time

# Each machine is a node of a tree and only knows its parent and children. Nodes talk
# by messages, and a send can fail. Compute the size of the tree.
#
# The root sends "count" down. Each node forwards it to its children; a leaf answers
# its parent with "1". A node that has heard from every child answers its parent with
# 1 + their sizes, and the root's answer is the size of the tree.
#
# Two things go wrong over a network, and each has a guard:
#   - a send fails: retry with exponential backoff, and stop at the first success
#   - a retried send arrives twice: count each child once (pending is a set)


class Node:

    def __init__(self, id: int, parent: int, children: list, send, sleep=time.sleep, retries: int = 3, delay: float = 0.01):
        self.id, self.parent, self.children = id, parent, list(children)
        self.send = send   # send(to, from, message); raises on failure
        self.sleep = sleep
        self.retries, self.delay = retries, delay
        self.pending = set(children)
        self.size = 1
        self.result = None # set on the root once the count finishes

    def send_with_retry(self, to: int, message: str) -> bool:
        wait = self.delay
        for _ in range(self.retries):
            try:
                self.send(to, self.id, message)
                return True # delivered: do not send it again
            except Exception:
                self.sleep(wait)
                wait *= 2
        return False

    def start(self) -> None: # called on the root
        self.receive(self.parent, "count")

    def receive(self, frm: int, message: str) -> None:
        if message == "count": # from the parent: pass it down
            if not self.children: self.reply()
            for c in self.children: self.send_with_retry(c, "count")
            return
        if frm not in self.pending: return # a duplicate, or a stranger
        self.pending.remove(frm)
        self.size += int(message)
        if not self.pending: self.reply()

    def reply(self) -> None:
        if self.parent == -1: self.result = self.size
        else: self.send_with_retry(self.parent, str(self.size))
