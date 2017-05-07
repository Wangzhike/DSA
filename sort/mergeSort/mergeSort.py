#!/usr/bin/env python3
# -*- coding: utf-8 -*-


def mergeSort(ul, lo=0, hi=-1):
    # set default value for hi
    if hi == -1:
        hi = len(ul)
    if hi <= lo + 1:
        return
    mi = lo + (hi - lo) // 2
    mergeSort(ul, lo, mi)
    mergeSort(ul, mi, hi)

    # merge the two sorted sublist
    ol_l = ul[lo:mi]
    i = 0
    j = mi
    k = lo
    while lo + i < mi and j < hi:
        if ol_l[i] <= ul[j]:
            ul[k] = ol_l[i]
            i = i + 1
        else:  # ul[j] < ol_l[i]
            ul[k] = ul[j]
            j = j + 1
        k = k + 1
    # if the ordered left sublist has extra items
    while lo + i < mi:
        ul[k] = ol_l[i]
        i = i + 1
        k = k + 1
