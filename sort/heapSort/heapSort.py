#!/usr/bin/env python3
# -*- coding: utf-8 -*-


def parent(i):
    if 1 < i:
        return i // 2


def lc(i):
    if 0 < i:
        return 2 * i


def rc(i):
    if 0 < i:
        return 2 * i + 1


def exch(L, i, j):
    L[i] += L[j]
    L[j] = L[i] - L[j]
    L[i] -= L[j]


def heapSize(L):
    # heap contains all elements in list L except L[0],
    # so heap_size = len(L) - 1 to substract 1 representing
    # L[0] from len(L).
    return len(L) - 1


def swim(L, i):
    while 1 < i and L[parent(i)] < L[i]:
        exch(L, parent(i), i)
        i = parent(i)


def sink(L, i, heap_size=-1):
    # Set heap_size to a default value
    # if it is not be initialized.
    if heap_size == -1:
        heap_size = heapSize(L)
    while lc(i) <= heap_size:
        largest = i
        if lc(i) <= heap_size and L[i] < L[lc(i)]:
            largest = lc(i)
        if rc(i) <= heap_size and L[largest] < L[rc(i)]:
            largest = rc(i)
        if i != largest:
            exch(L, i, largest)
            i = largest
        else:
            return


def build_max_heap(L, heap_size=-1):
    # Set heap_size to a default value
    # if it is not be initialized.
    if heap_size == -1:
        heap_size = heapSize(L)
    # At the start of the for loop, i = |_heap_size/2_|.
    # Since the nodes i+1, i+2, ..., n are leaves, they
    # are each roots of a max-heap.
    for i in range(1, heap_size // 2 + 1)[::-1]:
        sink(L, i, heap_size)


def heapSort(L):
    # Insert None to index 0 to make original
    # items to elements in heap.
    L.insert(0, None)
    heap_size = heapSize(L)
    build_max_heap(L, heap_size)
    for i in range(2, heap_size + 1)[::-1]:
        exch(L, 1, i)
        heap_size -= 1
        sink(L, 1, heap_size)
    # Delete the None inserted at first
    L.pop(0)


if __name__ == '__main__':
    ul = [4, 1, 3, 2, 16, 9, 10, 14, 8, 7]
    print('Unsorted List: %s' % ul)
    heapSort(ul)
    print('Sorted List: %s' % ul)
