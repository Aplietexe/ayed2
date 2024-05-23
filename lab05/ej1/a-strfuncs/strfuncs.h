#ifndef _STRFUNCTS_H_
#define _STRFUNCTS_H_

#include <stdbool.h>
#include <stdlib.h>

size_t string_length(const char* str);
/* returns the length of the string 'str' */

char* string_filter(const char* str, char c);
/* returns a new string with all ocurrences of 'c' removed from 'str' */

bool string_is_symmetric(const char* str);
/* returns true if 'str' is symmetric, false otherwise */

#endif
