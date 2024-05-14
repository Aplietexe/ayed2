#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>

typedef struct _list* list;
typedef int elem;

list empty_list(void);
/*
    Returns an empty list.
*/

list addl(elem e, list l);
/*
    Adds element e at the beginning of the list l.
*/

list list_destroy(list l);
/*
    Frees memory for l.
*/

bool is_empty(list l);
/*
    Returns whether the list l is empty.
*/

elem head(list l);
/*
    Returns the first element of the list l.
    PRE: !is_empty(l)
*/

list tail(list l);
/*
    Removes the first element of the list l.
    PRE: !is_empty(l)
*/

list addr(elem e, list l);
/*
    Adds element e at the end of the list l.
*/

int list_length(list l);
/*
    Returns the length of the list l.
*/

list concat(list l, list l0);
/*
    Concatenates the list l0 at the end of the list l.
*/

elem index(list l, int i);
/*
    Returns the element at the i-th position of the list l.
    PRE: 0 <= i < length(l)
*/

list take(list l, int n);
/*
    Leaves only the first n elements of the list l.
    PRE: 0 <= n
*/

list drop(list l, int n);
/*
    Removes the first n elements of the list l.
*/

list copy_list(list l);
/*
    Makes a copy of the list l.
*/

#endif
