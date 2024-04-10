#include "sort.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"

static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
    if (izq >= der) return;
    int pivot = partition(a, izq, der);
    // quick fix. the real fix is not to use unsigned to begin with
    quick_sort_rec(a, izq, pivot == 0 ? 0 : pivot - 1);
    quick_sort_rec(a, pivot + 1, der);
}

void quick_sort(int a[], unsigned int length) {
    quick_sort_rec(a, 0u, (length == 0u) ? 0u : length - 1u);
}
