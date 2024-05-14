#include "pair.h"

pair_t pair_new(int x, int y) { return (pair_t){x, y}; }

int pair_first(pair_t p) { return p.fst; }

int pair_second(pair_t p) { return p.snd; }

pair_t pair_swapped(pair_t p) { return (pair_t){p.snd, p.fst}; }

pair_t pair_destroy(pair_t p) {
    (void)p;  // Avoid unused parameter warning
    return (pair_t){0, 0};
}
