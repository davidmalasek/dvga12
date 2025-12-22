#!/usr/bin/env python3

import bt
import sys
import logging
from collections import deque

log = logging.getLogger(__name__)


class BST(bt.BT):
    def __init__(self, value=None):
        """
        Initializes an empty tree if `value` is None, else a root with the
        specified `value` and two empty children.
        """
        self.set_value(value)
        if not self.is_empty():
            self.cons(BST(), BST())

    def is_member(self, v):
        """
        Returns true if the value `v` is a member of the tree.
        """
        if self.is_empty():
            return False
        if v == self.value():
            return True
        if v < self.value():
            return self.lc().is_member(v)
        return self.rc().is_member(v)

    def size(self):
        """
        Returns the number of nodes in the tree.
        """
        if self.is_empty():
            return 0
        return 1 + self.lc().size() + self.rc().size()

    def height(self):
        """
        Returns the height of the tree.
        """
        if self.is_empty():
            return 0
        lh = self.lc().height()
        rh = self.rc().height()
        return 1 + max(lh, rh)

    def preorder(self):
        """
        Returns a list of all members in preorder.
        """
        if self.is_empty():
            return []
        return [self.value()] + self.lc().preorder() + self.rc().preorder()

    def inorder(self):
        """
        Returns a list of all members in inorder.
        """
        if self.is_empty():
            return []
        return self.lc().inorder() + [self.value()] + self.rc().inorder()

    def postorder(self):
        """
        Returns a list of all members in postorder.
        """
        if self.is_empty():
            return []
        return self.lc().postorder() + self.rc().postorder() + [self.value()]

    def bfs_order_star(self):
        """
        Returns a list of all members in breadth-first search* order, which
        means that empty nodes are denoted by "stars" (here the value None).

        For example, consider the following tree `t`:
                    10
              5           15
           *     *     *     20

        The output of t.bfs_order_star() should be:
        [ 10, 5, 15, None, None, None, 20 ]
        """
        if self.is_empty():
            return []

        result = []
        q = deque()
        q.append(self)
        last_value_index = -1

        while q:
            node = q.popleft()
            if node is None or node.is_empty():
                result.append(None)
            else:
                result.append(node.value())
                last_value_index = len(result) - 1
                q.append(node.lc())
                q.append(node.rc())

        if last_value_index >= 0:
            level = 0
            level_start = 0
            while True:
                level_end = level_start + (2**level) - 1
                if last_value_index <= level_end:
                    return result[: level_end + 1]
                level_start = level_end + 1
                level += 1

        return result[: last_value_index + 1]

    def add(self, v):
        """
        Adds the value `v` and returns the new (updated) tree.  If `v` is
        already a member, the same tree is returned without any modification.
        """
        if self.is_empty():
            self.__init__(value=v)
            return self
        if v < self.value():
            return self.cons(self.lc().add(v), self.rc())
        if v > self.value():
            return self.cons(self.lc(), self.rc().add(v))
        return self

    def find_max(self):
        node = self
        while not node.rc().is_empty():
            node = node.rc()
        return node.value()

    def find_min(self):
        node = self
        while not node.lc().is_empty():
            node = node.lc()
        return node.value()

    def delete(self, v):
        """
        Removes the value `v` from the tree and returns the new (updated) tree.
        If `v` is a non-member, the same tree is returned without modification.
        """
        if self.is_empty():
            return self

        if v < self.value():
            self.cons(self.lc().delete(v), self.rc())
            return self

        if v > self.value():
            self.cons(self.lc(), self.rc().delete(v))
            return self

        left_empty = self.lc().is_empty()
        right_empty = self.rc().is_empty()

        if left_empty and right_empty:
            self.__init__()
            return self

        if left_empty and not right_empty:
            child = self.rc()
            self.set_value(child.value())
            self.cons(child.lc(), child.rc())
            return self

        if right_empty and not left_empty:
            child = self.lc()
            self.set_value(child.value())
            self.cons(child.lc(), child.rc())
            return self

        min_val = self.rc().find_min()
        self.set_value(min_val)
        self.cons(self.lc(), self.rc().delete(min_val))
        return self


if __name__ == "__main__":
    log.critical("module contains no main module")
    sys.exit(1)
