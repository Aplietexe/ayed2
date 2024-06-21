#include <stdio.h>

#include "string.h"

int main() {
    string str = string_create("hello");
    string str2 = string_create("world");
    string str3 = string_clone(str);
    string_dump(str, stdout);
    printf("\n");
    string_dump(str2, stdout);
    printf("\n");
    string_dump(str3, stdout);
    printf("\n");
    printf("str == str2? %s\n", string_eq(str, str2) ? "true" : "false");
    printf("str == str3? %s\n", string_eq(str, str3) ? "true" : "false");
    printf("str < str2? %s\n", string_less(str, str2) ? "true" : "false");
    printf("str < str3? %s\n", string_less(str, str3) ? "true" : "false");
    printf("str2 < str3? %s\n", string_less(str2, str3) ? "true" : "false");
    string_destroy(str);
    string_destroy(str2);
    string_destroy(str3);

    return 0;
}
