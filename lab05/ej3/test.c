#include <assert.h>
#include <stdlib.h>

#include "stack.h"

void test_pop_last() {
    stack s = stack_empty();
    s = stack_push(s, 1);
    s = stack_pop(s);
    assert(stack_is_empty(s));
    stack_destroy(s);
}

void test_push_on_empty() {
    stack s = stack_empty();
    s = stack_push(s, 1);
    s = stack_pop(s);
    s = stack_push(s, 2);
    assert(stack_size(s) == 1);
    assert(stack_top(s) == 2);
    stack_destroy(s);
}

void test_null_array() {
    stack s = stack_empty();
    stack_elem* array = stack_to_array(s);
    assert(array == NULL);
    stack_destroy(s);
}

void test_array_order() {
    stack s = stack_empty();
    s = stack_push(s, 1);
    s = stack_push(s, 2);
    s = stack_push(s, 3);
    stack_elem* array = stack_to_array(s);
    assert(array[0] == 1);
    assert(array[1] == 2);
    assert(array[2] == 3);
    free(array);
}

int main(void) {
    test_pop_last();
    test_push_on_empty();
    test_null_array();
    test_array_order();
}
