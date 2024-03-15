#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 4

struct bound_data {
    bool is_upperbound;
    bool is_lowerbound;
    bool exists;
    unsigned int where;
};

struct bound_data check_bound(int value, int arr[], unsigned int length) {
    struct bound_data res = {true, true, false, -1};

    // no, I don't like unsigned in loops
    for (int i = 0, n = length; i < n; i++) {
        if (arr[i] == value) {
            res.exists = true;
            res.where = i;
        } else if (arr[i] < value) {
            res.is_lowerbound = false;
        } else {
            res.is_upperbound = false;
        }
    }
    return res;
}

int main(void) {
    int a[ARRAY_SIZE];
    int value;

    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("Enter a value for a[%d]: ", i);
        scanf("%d", &a[i]);
    }
    printf("Enter a value to check for: ");
    scanf("%d", &value);

    struct bound_data result = check_bound(value, a, ARRAY_SIZE);

    bool is_min = result.is_lowerbound && result.exists;
    bool is_max = result.is_upperbound && result.exists;

    if (is_min) {
        printf("%d is the minimum value in the array\n", value);
    } else if (result.is_lowerbound) {
        printf("%d is a lower bound of the array\n", value);
    }
    if (is_max) {
        printf("%d is the maximum value in the array\n", value);
    } else if (result.is_upperbound) {
        printf("%d is an upper bound of the array\n", value);
    }

    if (is_min || is_max) {
        printf("The value appears at index %d\n", result.where);
    }

    return EXIT_SUCCESS;
}
