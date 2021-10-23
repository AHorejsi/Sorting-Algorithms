#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "insertion_sort.h"

char* linear_search(char* lowPtr, char* highPtr, const size_t elemSize, const comparator_t comp) {
    char* ptr = lowPtr;

    while (ptr != highPtr) {
        if (comp(highPtr, ptr) < 0) {
            break;
        }

        ptr += elemSize;    
    }

    return ptr;
}

char* _do_binary_search(char* lowPtr, char* highPtr, void* key, const size_t elemSize, const comparator_t comp) {
    highPtr -= elemSize;

    while (lowPtr <= highPtr) {
        size_t size = highPtr - lowPtr;
        size_t midpoint = size / 2 / elemSize;

        char* midPtr = lowPtr + midpoint * elemSize;
        int comparison = comp(midPtr, key);

        if (comparison < 0) {
            lowPtr = midPtr + elemSize;
        }
        else if (comparison > 0) {
            highPtr = midPtr - elemSize;
        }
        else {
            return midPtr;
        }
    }

    return lowPtr;
}

char* binary_search(char* lowPtr, char* highPtr, const size_t elemSize, const comparator_t comp) {
    return _do_binary_search(lowPtr, highPtr, highPtr, elemSize, comp);
}

char* exponential_search(char* lowPtr, char* highPtr, const size_t elemSize, const comparator_t comp) {
    if (0 == comp(lowPtr, highPtr)) {
        return lowPtr;
    }

    size_t index = 1;
    size_t count = (highPtr - lowPtr) / elemSize;

    while (index < count && comp(lowPtr + index * elemSize, highPtr) <= 0) {
        index += index;
    }

    return _do_binary_search(lowPtr + (index / 2) * elemSize, lowPtr + minimum(index, count) * elemSize, highPtr, elemSize, comp);
}

void insertion_sort(void* arr, const size_t count, const size_t elemSize, const comparator_t comp, const searcher_t searcher) {
    char* lowPtr = (char*)arr;
    char* highPtr = lowPtr + count * elemSize;
    void* buffer = malloc(elemSize);

    for (char* ptr1 = lowPtr + elemSize; ptr1 != highPtr; ptr1 += elemSize) {
        char* sortedPosition = searcher(lowPtr, ptr1, elemSize, comp);

        for (char* ptr2 = ptr1; ptr2 != sortedPosition; ptr2 -= elemSize) {
            swap(ptr2, ptr2 - elemSize, elemSize, buffer);
        }
    }

    free(buffer);
}

void shell_sort(void* arr, const size_t count, const size_t elemSize, const comparator_t comp) {
    char* lowPtr = (char*)arr;
    char* highPtr = lowPtr + elemSize * count;
    void* temp = malloc(elemSize);

    for (size_t gap = count / 2; gap > 0; gap /= 2) {
        size_t gapJump = elemSize * gap;

        for (char* ptr1 = lowPtr + gapJump; ptr1 != highPtr; ptr1 += elemSize) {
            memcpy(temp, ptr1, elemSize);

            char* ptr2 = ptr1;
            char* ptr3 = ptr2 - gapJump;
            char* endPtr = lowPtr + gapJump;

            while (ptr2 >= endPtr && comp(temp, ptr3) < 0) {
                memcpy(ptr2, ptr3, elemSize);

                ptr2 -= gapJump;
                ptr3 -= gapJump;
            }

            memcpy(ptr2, temp, elemSize);
        }
    }

    free(temp);
}
