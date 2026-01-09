#!/usr/bin/env python3

import sys
import bst
import logging

log = logging.getLogger(__name__)


class AVL(bst.BST):
    def __init__(self, value=None):
        """
        Initializes an empty tree if `value` is None, else a root with the
        specified `value` and two empty children.
        """
        self.set_value(value)
        if not self.is_empty():
            self.cons(AVL(), AVL())

    def add(self, v):
        if self.is_empty():
            self.__init__(value=v)
            return self

        if v < self.value():
            self.cons(self.lc().add(v), self.rc())
        elif v > self.value():
            self.cons(self.lc(), self.rc().add(v))
        else:
            return self
        return self.balance()

    def delete(self, v):
        bst.BST.delete(self, v)
        return self.balance()

    def balance(self):
        """
        AVL-balances around the node rooted at `self`.  In other words, this
        method applies one of the following if necessary: slr, srr, dlr, drr.
        """
        if self.is_empty():
            return self

        left_height = self.lc().height()
        right_height = self.rc().height()
        balance_factor = left_height - right_height

        if balance_factor > 1:
            left_child = self.lc()
            left_left_height = left_child.lc().height()
            left_right_height = left_child.rc().height()
            left_child_balance_factor = left_left_height - left_right_height

            if left_child_balance_factor >= 0:
                return self.srr()
            return self.drr()

        if balance_factor < -1:
            right_child = self.rc()
            right_left_height = right_child.lc().height()
            right_right_height = right_child.rc().height()
            right_child_balance_factor = right_left_height - right_right_height

            if right_child_balance_factor <= 0:
                return self.slr()
            return self.dlr()

        return self

    def slr(self):
        """
        Performs a single-left rotate around the node rooted at `self`.
        """
        if self.is_empty() or self.rc().is_empty():
            return self

        old_root_value = self.value()
        left_subtree = self.lc()

        right_child = self.rc()
        new_root_value = right_child.value()
        right_child_left_subtree = right_child.lc()
        right_child_right_subtree = right_child.rc()

        new_left_subtree = AVL(old_root_value)
        new_left_subtree.cons(left_subtree, right_child_left_subtree)

        self.set_value(new_root_value)
        self.cons(new_left_subtree, right_child_right_subtree)
        return self

    def srr(self):
        """
        Performs a single-right rotate around the node rooted at `self`.
        """
        if self.is_empty() or self.lc().is_empty():
            return self

        old_root_value = self.value()
        right_subtree = self.rc()

        left_child = self.lc()
        new_root_value = left_child.value()
        left_child_left_subtree = left_child.lc()
        left_child_right_subtree = left_child.rc()

        new_right_subtree = AVL(old_root_value)
        new_right_subtree.cons(left_child_right_subtree, right_subtree)

        self.set_value(new_root_value)
        self.cons(left_child_left_subtree, new_right_subtree)
        return self

    def dlr(self):
        """
        Performs a double-left rotate around the node rooted at `self`.
        """
        if self.is_empty() or self.rc().is_empty():
            return self

        self.cons(self.lc(), self.rc().srr())
        return self.slr()

    def drr(self):
        """
        Performs a double-right rotate around the node rooted at `self`.
        """
        if self.is_empty() or self.lc().is_empty():
            return self
        self.cons(self.lc().slr(), self.rc())
        return self.srr()


if __name__ == "__main__":
    log.critical("module contains no main module")
    sys.exit(1)
