#include "list.h"

#include <assert.h>
#include <stdlib.h>

struct _list {
    elem e;
    list next;
};

list empty_list(void) { return NULL; }

list addl(elem e, list l) {
    list new = malloc(sizeof(struct _list));
    new->e = e;
    new->next = l;
    return new;
}

list list_destroy(list l) {
    if (l == NULL) return l;
    list next = l->next;
    free(l);
    return list_destroy(next);
}

bool is_empty(list l) { return l == NULL; }

elem head(list l) {
    assert(!is_empty(l));
    return l->e;
}

list tail(list l) {
    assert(!is_empty(l));
    list next = l->next;
    free(l);
    return next;
}

list addr(elem e, list l) {
    if (is_empty(l)) return addl(e, l);
    l->next = addr(e, l->next);
    return l;
}

int list_length(list l) {
    if (is_empty(l)) return 0;
    return 1 + list_length(l->next);
}

list concat(list l, list l0) {
    if (is_empty(l)) return l0;
    l->next = concat(l->next, l0);
    return l;
}

static elem _index(list l, int i) {
    if (i == 0) return head(l);
    return _index(l->next, i - 1);
}

elem index(list l, int i) {
    assert(0 <= i && i < list_length(l));
    return _index(l, i);
}

list take(list l, int n) {
    assert(0 <= n);
    if (n == 0 || is_empty(l)) return list_destroy(l);
    l->next = take(l->next, n - 1);
    return l;
}

list drop(list l, int n) {
    assert(0 <= n);
    if (n == 0 || is_empty(l)) return l;
    return drop(tail(l), n - 1);
}

list copy_list(list l) {
    if (is_empty(l)) return l;
    return addl(head(l), copy_list(l->next));
}
