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
        if self.is_empty():
            return self

        if v < self.value():
            self.cons(self.lc().delete(v), self.rc())
            return self.balance()

        if v > self.value():
            self.cons(self.lc(), self.rc().delete(v))
            return self.balance()

        left_empty = self.lc().is_empty()
        right_empty = self.rc().is_empty()

        if left_empty and right_empty:
            self.__init__()
            return self
        if left_empty and not right_empty:
            child = self.rc()
            self.set_value(child.value())
            self.cons(child.lc(), child.rc())
            return self.balance()

        if right_empty and not left_empty:
            child = self.lc()
            self.set_value(child.value())
            self.cons(child.lc(), child.rc())
            return self.balance()

        min_val = self.rc().find_min()
        self.set_value(min_val)
        self.cons(self.lc(), self.rc().delete(min_val))
        return self.balance()

    def balance(self):
        """
        AVL-balances around the node rooted at `self`.  In other words, this
        method applies one of the following if necessary: slr, srr, dlr, drr.
        """
        if self.is_empty():
            return self

        lh = self.lc().height()
        rh = self.rc().height()
        bf = lh - rh

        if bf > 1:
            child = self.lc()
            clh = child.lc().height()
            crh = child.rc().height()
            child_bf = clh - crh

            if child_bf >= 0:
                return self.srr()
            else:
                return self.drr()

        if bf < -1:
            child = self.rc()
            clh = child.lc().height()
            crh = child.rc().height()
            child_bf = clh - crh
            if child_bf <= 0:
                return self.slr()
            else:
                return self.dlr()

        return self

    def slr(self):
        """
        Performs a single-left rotate around the node rooted at `self`.
        """
        if self.is_empty() or self.rc().is_empty():
            return self

        x_val = self.value()
        A = self.lc()
        Y = self.rc()
        B = Y.lc()
        C = Y.rc()

        y_val = Y.value()

        left_sub = AVL(x_val)
        left_sub.cons(A, B)

        self.set_value(y_val)
        self.cons(left_sub, C)
        return self

    def srr(self):
        """
        Performs a single-right rotate around the node rooted at `self`.
        """
        if self.is_empty() or self.lc().is_empty():
            return self

        y_val = self.value()
        Y = self.lc()
        A = Y.lc()
        B = Y.rc()
        x_val = Y.value()
        C = self.rc()

        right_sub = AVL(y_val)
        right_sub.cons(B, C)

        self.set_value(x_val)
        self.cons(A, right_sub)
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
