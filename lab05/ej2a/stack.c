#include "stack.h"

#include <assert.h>
#include <stdlib.h>

struct _s_stack {
    stack_elem elem;
    stack next;
};

stack stack_empty() { return NULL; }

stack stack_push(stack s, stack_elem e) {
    stack new = malloc(sizeof(struct _s_stack));
    assert(new != NULL);
    new->elem = e;
    new->next = s;
    return new;
}

stack stack_pop(stack s) {
    assert(!stack_is_empty(s));
    stack next = s->next;
    free(s);
    return next;
}

unsigned stack_size(stack s) { return s == NULL ? 0 : 1 + stack_size(s->next); }

stack_elem stack_top(stack s) {
    assert(!stack_is_empty(s));
    return s->elem;
}

bool stack_is_empty(stack s) { return s == NULL; }

stack_elem* stack_to_array(stack s) {
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
    if (s != NULL) {
        stack_destroy(s->next);
        free(s);
    }
    return NULL;
}
