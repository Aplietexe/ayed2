#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "data.h"

void print_data(data_t d) {
    printf(
        "NOMBRE: %s\n"
        "EDAD  : %d años\n"
        "ALTURA: %d cm\n\n",
        d.name,
        d.age,
        d.height);
}

int main(void) {
    data_t messi = {"Leo Messi", 36, 169};
    print_data(messi);

    printf(
        "name-size  : %lu bytes\n"
        "age-size   : %lu bytes\n"
        "height-size: %lu bytes\n"
        "data_t-size: %lu bytes\n",
        sizeof(messi.name),
        sizeof(messi.age),
        sizeof(messi.height),
        sizeof(messi));

    printf(
        "name-address: %p\n"
        "name-index: %lu\n"
        "age-address : %p\n"
        "age-index  : %lu\n"
        "height-address: %p\n"
        "height-index : %lu\n"
        "data_t-address: %p\n"
        "data_t-index: %lu\n",
        (void*)&messi.name,
        (uintptr_t)&messi.name,
        (void*)&messi.age,
        (uintptr_t)&messi.age,
        (void*)&messi.height,
        (uintptr_t)&messi.height,
        (void*)&messi,
        (uintptr_t)&messi);
    return EXIT_SUCCESS;
}
