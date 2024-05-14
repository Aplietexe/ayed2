#include "pair.h"

pair_t pair_new(int x, int y) { return (pair_t){{x, y}}; }

int pair_first(pair_t p) { return p.values[0]; }

int pair_second(pair_t p) { return p.values[1]; }

pair_t pair_swapped(pair_t p) { return (pair_t){{p.values[1], p.values[0]}}; }

pair_t pair_destroy(pair_t p) {
    (void)p;  // Avoid unused parameter warning
    return (pair_t){{0, 0}};
}
