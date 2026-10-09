import random

LEVELS = 16

class Node:
    def __init__(self, value, level):
        self.value = value
        self.next = [None] * level # next[i] = next node at level i

class Skiplist:

    def __init__(self):
        self.head = Node(-1, LEVELS) # sentinel node

    def _toss(self):
        level = 1
        while random.random() < 0.5 and level < LEVELS:
            level += 1
        return level

    # last node with value < x at every level
    def _left(self, x):
        left, cur = [None] * LEVELS, self.head
        for i in reversed(range(LEVELS)):
            while cur.next[i] and cur.next[i].value < x:
                cur = cur.next[i]
            left[i] = cur
        return left

    def search(self, target: int) -> bool:
        node = self._left(target)[0].next[0]
        return node is not None and node.value == target

    def add(self, num: int) -> None:
        left = self._left(num)
        node = Node(num, self._toss())
        for i in range(len(node.next)):
            node.next[i] = left[i].next[i]
            left[i].next[i] = node

    def erase(self, num: int) -> bool:
        left = self._left(num)
        node = left[0].next[0]
        if node is None or node.value != num:
            return False
        for i in range(len(node.next)):
            if left[i].next[i] is node:
                left[i].next[i] = node.next[i]
        return True

# Your Skiplist object will be instantiated and called as such:
# obj = Skiplist()
# param_1 = obj.search(target)
# obj.add(num)
# param_3 = obj.erase(num)
