#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "bogo_sort.h"

void bogo_sort(void* arr, const size_t count, const size_t elemSize, const comparator_t comp, const shuffler_t shuffler) {
    void* buffer = malloc(elemSize);

    while (!is_sorted(arr, count, elemSize, comp)) {
        shuffler(arr, count, elemSize, buffer);
    }

    free(buffer);
}

void _reverse(char* lowPtr, char* highPtr, const size_t elemSize, void* buffer) {
    highPtr -= elemSize;

    while (lowPtr < highPtr) {
        swap(lowPtr, highPtr, elemSize, buffer);

        lowPtr += elemSize;
        highPtr -= elemSize;
    }
}

void _next_permutation(char* lowPtr, char* highPtr, const size_t elemSize, const comparator_t comp, void* buffer) {
    char* ptr1 = highPtr - elemSize;

    if (!(lowPtr == highPtr || lowPtr == ptr1)) {
        while (true) {
            char* ptr2 = ptr1;
            ptr1 -= elemSize;

            if (comp(ptr1, ptr2) < 0) {
                puts("TEST1\n");
                char* ptr3 = highPtr;

                do {
                    ptr3 -= elemSize;
                } while (!comp(ptr1, ptr3));

                swap(ptr1, ptr3, elemSize, buffer);
                _reverse(ptr2, highPtr, elemSize, buffer);
                break;
            }
            if (ptr1 == lowPtr) {
                puts("TEST2\n");
                _reverse(lowPtr, highPtr, elemSize, buffer);
                break;
            }
        }
    }
}

void permutation_sort(void* arr, const size_t count, const size_t elemSize, const comparator_t comp) {
    char* lowPtr = (char*)arr;
    char* highPtr = lowPtr + count * elemSize;
    void* buffer = malloc(elemSize);

    while (!is_sorted(arr, count, elemSize, comp)) {
        _next_permutation(lowPtr, highPtr, elemSize, comp, buffer);
    }

    free(buffer);
}
