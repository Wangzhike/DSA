#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import unittest
from countInversions import countInversions


class TestCountInversions(unittest.TestCase):
    def test_basic(self):
        self.ul = [1, 5, 4, 8, 10, 2, 6, 9, 12, 11, 3, 7]
        self.ol = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
        self.inversions = countInversions(self.ul)
        self.assertEqual(self.inversions, 22)
        self.assertListEqual(self.ol, self.ul)

    def test_easy(self):
        self.ul = [1, 3, 4, 2]
        self.ol = [1, 2, 3, 4]
        self.inversions = 0
        self.inversions = countInversions(self.ul)
        self.assertEqual(self.inversions, 2)
        self.assertListEqual(self.ol, self.ul)


if __name__ == '__main__':
    unittest.main()
