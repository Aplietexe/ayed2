#include "sort.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"
#include "sort_helpers.h"

static unsigned int partition(int a[], unsigned int izq, unsigned int der) {
    /* Permutes elements of a[izq..der] and returns pivot such that:
     - izq <= pivot <= der
     - elements in a[izq,pivot) all 'go_before' (according to function
     goes_before) a[pivot]
     - a[pivot] 'goes_before' all the elements in a(pivot,der]
    */
    int l = izq + 1, r = der;
    while (l <= r) {
        if (goes_before(a[izq], a[l]) && goes_before(a[r], a[izq]))
            swap(a, l, r);
        if (!goes_before(a[izq], a[l])) l++;
        if (!goes_before(a[r], a[izq])) r--;
    }
    swap(a, izq, r);
    return r;
}

static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
    if (izq >= der) return;
    int pivot = partition(a, izq, der);
    // quick fix. the real fix is not to use unsigned to begin with
    quick_sort_rec(a, izq, pivot == 0 ? 0 : pivot - 1);
    quick_sort_rec(a, pivot + 1, der);
}

void quick_sort(int a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}
