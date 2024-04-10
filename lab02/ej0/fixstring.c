#include "fixstring.h"

#include <assert.h>
#include <stdbool.h>

unsigned int fstring_length(fixstring s) {
    int i = 0;
    while (s[i] != '\0') i++;
    return i;
}

bool fstring_eq(fixstring s1, fixstring s2) {
    int i = 0;
    while (s1[i] == s2[i] && s1[i] != '\0') i++;
    return s1[i] == s2[i];
}

bool fstring_less_eq(fixstring s1, fixstring s2) {
    int i = 0;
    while (s1[i] == s2[i] && s1[i] != '\0') i++;
    return s1[i] <= s2[i];
}
