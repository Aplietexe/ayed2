#include "stack.h"

#include <assert.h>
#include <stdlib.h>

struct _s_stack {
    stack_elem elem;
    stack next;
    int size;
};

bool invrep(stack s) {
    return s == NULL || (s->size > 0 &&
                         s->size == 1 + (s->next == NULL ? 0 : s->next->size) &&
                         invrep(s->next));
}

stack stack_empty() { return NULL; }

stack stack_push(stack s, stack_elem e) {
    assert(invrep(s));
    stack new = malloc(sizeof(struct _s_stack));
    assert(new != NULL);
    new->elem = e;
    new->next = s;
    new->size = 1 + stack_size(s);
    assert(invrep(new));
    return new;
}

stack stack_pop(stack s) {
    assert(invrep(s));
    assert(!stack_is_empty(s));
    stack next = s->next;
    free(s);
    assert(invrep(next));
    return next;
}

unsigned stack_size(stack s) {
    assert(invrep(s));
    return s == NULL ? 0 : s->size;
}

stack_elem stack_top(stack s) {
    assert(invrep(s));
    assert(!stack_is_empty(s));
    return s->elem;
}

bool stack_is_empty(stack s) {
    assert(invrep(s));
    return s == NULL;
}

stack_elem* stack_to_array(stack s) {
    assert(invrep(s));
    int size = stack_size(s);
    if (size == 0) return NULL;
    stack_elem* array = malloc(size * sizeof(stack_elem));
    assert(array != NULL);
    for (int i = size - 1; i >= 0; i--) {
        array[i] = stack_top(s);
        s = stack_pop(s);
    }
    return array;
}

stack stack_destroy(stack s) {
    assert(invrep(s));
    if (s != NULL) {
        stack_destroy(s->next);
        free(s);
    }
    return NULL;
}
