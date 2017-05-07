#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import unittest
from mergeSort import mergeSort
from random import randint


class TestMergeSort(unittest.TestCase):
    def test_basic(self):
        self.ul = [54, 26, 93, 17, 77, 31, 44, 55, 20]
        self.ol = [17, 20, 26, 31, 44, 54, 55, 77, 93]
        mergeSort(self.ul)
        self.assertListEqual(self.ol, self.ul)

    def test_randomData(self):
        self.ul = []
        for i in range(100):
            self.ul.append(randint(-1000, 3000))
        self.ol = sorted(self.ul)
        mergeSort(self.ul)
        self.assertListEqual(self.ol, self.ul)

    def test_letters(self):
        self.ul = [c for c in 'ALGORITHMS']
        self.ol = [c for c in 'AGHILMORST']
        mergeSort(self.ul)
        self.assertListEqual(self.ul, self.ol)


if __name__ == '__main__':
    unittest.main()
