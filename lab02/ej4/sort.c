#include "sort.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"
#include "sort_helpers.h"

static unsigned int min_pos_from(int a[], unsigned int i, unsigned int length) {
    unsigned int min_pos = i;
    for (unsigned int j = i + 1; j < length; ++j) {
        if (!goes_before(a[min_pos], a[j])) {
            min_pos = j;
        }
    }
    return (min_pos);
}

void selection_sort(int a[], unsigned int length) {
    for (unsigned int i = 0u; i < length; ++i) {
        unsigned int min_pos = min_pos_from(a, i, length);
        swap(a, i, min_pos);
    }
}

static void insert(int a[], unsigned int i) {
    for (int j = i; j >= 1 && goes_before(a[j], a[j - 1]); j--)
        swap(a, j, j - 1);
}

void insertion_sort(int a[], unsigned int length) {
    for (unsigned int i = 1u; i < length; ++i) {
        assert(array_is_sorted(a, i));
        insert(a, i);
    }
}

static unsigned int partition(int a[], unsigned int izq, unsigned int der) {
    /* Permutes elements of a[izq..der] and returns pivot such that:
     - izq <= pivot <= der
     - elements in a[izq,pivot) all 'go_before' (according to function
     goes_before) a[pivot]
     - a[pivot] 'goes_before' all the elements in a(pivot,der]
    */
    int l = izq + 1, r = der;
    while (l <= r) {
        bool l_before_piv = goes_before(a[izq], a[l]),
             piv_before_r = goes_before(a[r], a[izq]);  // Goodhart's law
        if (l_before_piv && piv_before_r) swap(a, l, r);
        if (!l_before_piv) l++;
        if (!piv_before_r) r--;
    }
    if ((int)izq != r) swap(a, izq, r);
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
