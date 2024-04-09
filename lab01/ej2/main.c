/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

void print_help() {
    /* Print the usage help of this program. */
    printf("I'm not updating this.\n");
}

unsigned int array_from_stdin(int array[], unsigned int max_size) {
    unsigned int length;
    if (scanf("%u", &length) != 1) {
        printf("Error reading from stdin\n");
        exit(EXIT_FAILURE);
    }
    if (length > max_size) {
        printf("Error: array length is greater than max size\n");
        exit(EXIT_FAILURE);
    }
    for (unsigned int i = 0; i < length; i++) {
        if (scanf("%d", &array[i]) != 1) {
            printf("Error reading from stdin\n");
            exit(EXIT_FAILURE);
        }
    }
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

int main() {
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];

    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_stdin(array, MAX_SIZE);

    /*dumping the array*/
    array_dump(array, length);

    return EXIT_SUCCESS;
}
