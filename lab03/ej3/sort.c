/*
  @file sort.c
  @brief sort functions implementation
*/

#include "sort.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"
#include "player.h"

bool goes_before(player_t x, player_t y) { return x.rank < y.rank; }

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    // modified because goes_before is irreflexive
    while (i < length && !goes_before(atp[i], atp[i - 1u])) {
        i++;
    }
    return (i == length);
}

void swap(player_t a[], unsigned i, unsigned j) {
    player_t aux = a[i];
    a[i] = a[j];
    a[j] = aux;
}

static unsigned partition(player_t a[], unsigned izq, unsigned der) {
    int l = izq + 1, r = der;
    while (l <= r) {
        bool l_before_piv = goes_before(a[izq], a[l]),
             piv_before_r = goes_before(a[r], a[izq]);
        if (l_before_piv && piv_before_r) swap(a, l, r);
        if (!l_before_piv) l++;
        if (!piv_before_r) r--;
    }
    if ((int)izq != r) swap(a, izq, r);
    return r;
}

static void quick_sort_rec(player_t a[], unsigned izq, unsigned der) {
    if (izq >= der) return;
    int pivot = partition(a, izq, der);
    // quick fix. the real fix is not to use unsigned to begin with
    quick_sort_rec(a, izq, pivot == 0 ? 0 : pivot - 1);
    quick_sort_rec(a, pivot + 1, der);
}

void sort(player_t a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}
