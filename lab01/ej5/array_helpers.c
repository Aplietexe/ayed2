#include "array_helpers.h"

#include <stdio.h>
#include <stdlib.h>

unsigned int array_from_file(int array[],
                             unsigned int max_size,
                             const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filepath);
        exit(EXIT_FAILURE);
    }

    unsigned int length;
    if (fscanf(file, "%u", &length) != 1) {
        printf("Error reading file %s\n", filepath);
        exit(EXIT_FAILURE);
    }
    if (length > max_size) {
        printf("Error: array length is greater than max size\n");
        exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < length; i++) {
        if (fscanf(file, "%d", &array[i]) != 1) {
            printf("Error reading file %s\n", filepath);
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);
    return length;
}

void array_dump(int a[], unsigned int length) {
    printf("[ ");
    if (length > 0) {  // this wouldn't be necessary if we used int for length
        for (unsigned int i = 0; i < length - 1; i++) {
            printf("%d, ", a[i]);
        }
        printf("%d ", a[length - 1]);
    }
    printf("]\n");
}

mybool array_is_sorted(int a[], unsigned int length) {
    for (unsigned int i = 1; i < length; i++) {
        if (a[i - 1] > a[i]) {
            return false;
        }
    }
    return true;
}
