#!/usr/bin/env python3
# -*- coding: utf-8 -*-


def insertSort(ul, lo=0, hi=-1):
    j = lo + 1
    # set default value for hi
    if hi == -1:
        hi = len(ul)
    while j < hi:
        key = ul[j]
        i = j - 1
        # insert key into sortedList
        while lo <= i and key < ul[i]:
            # move item back
            ul[i+1] = ul[i]
            i = i - 1
        # find the insertion position
        ul[i+1] = key
        j = j + 1
    return ul
