#!/usr/bin/env python3
# -*- coding: utf-8 -*-


def countInversions(ul, lo=0, hi=-1):
    # set default value for hi
    if hi == -1:
        hi = len(ul)
    if hi - lo <= 1:
        return 0
    inversions = 0
    mi = lo + (hi - lo) // 2
    inversions += countInversions(ul, lo, mi)
    inversions += countInversions(ul, mi, hi)

    # merge the two sorted sublist and
    # count inversions
    ol_l = ul[lo:mi]
    i = 0
    j = mi
    k = lo
    while lo + i < mi and j < hi:
        if ol_l[i] <= ul[j]:
            ul[k] = ol_l[i]
            i = i + 1
        else:  # when ul[j] < ol_l[i], inversions occur
            ul[k] = ul[j]
            j = j + 1
            inversions += mi - (lo + i)
        k = k + 1
    # if the ordered left sublist has extra items
    while lo + i < mi:
        ul[k] = ol_l[i]
        i = i + 1
        k = k + 1
    return inversions


if __name__ == '__main__':
    ul = [1, 3, 4, 2]
    print('unsorted list: %s' % ul)
    cnt = countInversions(ul)
    print('sorted list: %s and have %d inversions' % (ul, cnt))
