#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import unittest
from heapSort import heapSort
from random import randint


class TestHeapSort(unittest.TestCase):
    def test_basic(self):
        self.ul = [4, 1, 3, 2, 16, 9, 10, 14, 8, 7]
        self.ol = [1, 2, 3, 4, 7, 8, 9, 10, 14, 16]
        heapSort(self.ul)
        self.assertListEqual(self.ol, self.ul)

    def test_randomData(self):
        self.ul = []
        for i in range(100):
            self.ul.append(randint(-1000, 3000))
        self.ol = sorted(self.ul)
        heapSort(self.ul)
        self.assertListEqual(self.ol, self.ul)


if __name__ == '__main__':
    unittest.main()
