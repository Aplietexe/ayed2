#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j = 0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

unsigned data_from_file(const char *path,
                        unsigned indexes[],
                        char letters[],
                        unsigned max_size) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Error opening %s\n", path);
        exit(EXIT_FAILURE);
    }

    unsigned i = 0;
    const char *pattern = "%u -> *%c*\n";
    int index;
    while (i < max_size && fscanf(file, pattern, &index, &letters[i]) == 2) {
        // not handling index > UINT_MAX, but it's 3AM so please don't do that
        if (index < 0) {  // also avoids INT_MAX < index <= UINT_MAX
            printf("Indices must be non-negative\n");
            exit(EXIT_FAILURE);
        }
        indexes[i] = index;
        i++;
    }

    if (!feof(file)) {
        printf("Error reading %s\n", path);
        exit(EXIT_FAILURE);
    }
    if (fclose(file)) {
        printf("Error closing %s\n", path);
        exit(EXIT_FAILURE);
    }

    return i;
}

char *get_path(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Use %s <path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    return argv[1];
}

int main(int argc, char *argv[]) {
    char *path = get_path(argc, argv);
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE] = {0};  // this initializes all values to 0
    unsigned length = data_from_file(path, indexes, letters, MAX_SIZE);

    for (unsigned i = 0; i < length; i++) {
        if (indexes[i] >= length) {
            printf("Index %u is too large\n", indexes[i]);
            exit(EXIT_FAILURE);
        }
        if (sorted[indexes[i]] != '\0') {
            printf("Index %u is duplicated\n", indexes[i]);
            exit(EXIT_FAILURE);
        }
        sorted[indexes[i]] = letters[i];
    }
    // something something pigeonhole

    dump(sorted, length);

    return EXIT_SUCCESS;
}
