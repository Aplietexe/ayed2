#include "stack.h"

#include <assert.h>
#include <stdlib.h>

struct _s_stack {
    stack_elem* elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

bool invrep(stack s) {
    return s != NULL && s->size <= s->capacity &&
           (s->capacity == 0) == (s->elems == NULL);
}

stack stack_empty() {
    stack s = malloc(sizeof(struct _s_stack));
    assert(s != NULL);
    s->elems = NULL;
    s->size = 0;
    s->capacity = 0;
    return s;
}

stack stack_push(stack s, stack_elem e) {
    if (s->size == s->capacity) {
        s->capacity = s->capacity == 0 ? 1 : 2 * s->capacity;
        s->elems = realloc(s->elems, s->capacity * sizeof(stack_elem));
        assert(s->elems != NULL);
    }
    s->elems[s->size++] = e;
    return s;
}

stack stack_pop(stack s) {
    assert(!stack_is_empty(s));
    s->size--;
    return s;
}

unsigned stack_size(stack s) { return s->size; }

stack_elem stack_top(stack s) {
    assert(!stack_is_empty(s));
    return s->elems[s->size - 1];
}

bool stack_is_empty(stack s) { return s->size == 0; }

stack_elem* stack_to_array(stack s) {
    if (stack_is_empty(s)) return NULL;
    stack_elem* arr = malloc(s->size * sizeof(stack_elem));
    assert(arr != NULL);
    for (int i = 0; i < (int)s->size; i++) {
        arr[i] = s->elems[i];
    }
    stack_destroy(s);
    return arr;
}

stack stack_destroy(stack s) {
    free(s->elems);
    free(s);
    return NULL;
}
