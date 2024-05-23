#include "strfuncs.h"

#include <stdlib.h>

size_t string_length(const char* str) {
    size_t length = 0;
    while (str[length] != '\0') length++;
    return length;
}

char* string_filter(const char* str, char c) {
    char* filtered = malloc(string_length(str) + 1);
    size_t j = 0;
    for (size_t i = 0; str[i] != '\0'; i++)
        if (str[i] != c) {
            filtered[j] = str[i];
            j++;
        }
    filtered[j] = '\0';
    return filtered;
}

bool string_is_symmetric(const char* str) {
    size_t length = string_length(str);
    for (size_t i = 0; i < length / 2; i++)
        if (str[i] != str[length - i - 1]) {
            return false;
        }
    return true;
}
