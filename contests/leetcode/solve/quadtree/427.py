from typing import List

"""
# Definition for a QuadTree node.
class Node:
    def __init__(self, val, isLeaf, topLeft, topRight, bottomLeft, bottomRight):
        self.val = val
        self.isLeaf = isLeaf
        self.topLeft = topLeft
        self.topRight = topRight
        self.bottomLeft = bottomLeft
        self.bottomRight = bottomRight
"""

class QuadTree:
    def __init__(self, grid: List[List[int]]):
        self.g = grid
        self.root = self.build(0, 0, len(grid) - 1, len(grid[0]) - 1)

    def build(self, r0, c0, r1, c1):
        if r0 == r1 and c0 == c1:
            return Node(self.g[r0][c0] == 1, True, None, None, None, None)

        rm, cm = (r0 + r1) // 2, (c0 + c1) // 2
        tl = self.build(r0, c0, rm, cm)
        tr = self.build(r0, cm + 1, rm, c1)
        bl = self.build(rm + 1, c0, r1, cm)
        br = self.build(rm + 1, cm + 1, r1, c1)

        # merge when 4 identical leaves
        if tl.isLeaf and tr.isLeaf and bl.isLeaf and br.isLeaf and tl.val == tr.val == bl.val == br.val:
            return Node(tl.val, True, None, None, None, None)
        return Node(False, False, tl, tr, bl, br)


class Solution:
    def construct(self, grid: List[List[int]]) -> 'Node':
        return QuadTree(grid).root
