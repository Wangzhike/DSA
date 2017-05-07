#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import unittest
from insertSort import insertSort
from random import randint


class TestInsertSort(unittest.TestCase):
    def test_basic(self):
        self.ul = [5, 2, 4, 6, 1, 3]
        self.ol = [1, 2, 3, 4, 5, 6]
        self.ul = insertSort(self.ul)
        for i in range(0, len(self.ul)):
            self.assertEqual(self.ol[i], self.ul[i])

    def test_randomData(self):
        self.ul = []
        for i in range(100):
            self.ul.append(randint(-1000, 1000))
        self.ol = sorted(self.ul)
        self.ul = insertSort(self.ul)
        self.assertListEqual(self.ol, self.ul)


if __name__ == '__main__':
    unittest.main()
