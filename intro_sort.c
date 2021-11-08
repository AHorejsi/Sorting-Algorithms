#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "heap_sort.h"
#include "intro_sort.h"

#define SIMPLE_SORT_LIMIT 16

char* _select_pivot(char* lowPtr, char* highPtr, const size_t elemSize, const comparator_t comp, void* swapBuffer) {
    size_t count = (highPtr - lowPtr) / elemSize + 1;
    size_t midIndex = count / 2;
    char* midPtr = lowPtr + midIndex * elemSize;

    if (comp(highPtr, lowPtr) < 0) {
        swap(highPtr, lowPtr, elemSize, swapBuffer);
    }
    if (comp(midPtr, lowPtr) < 0) {
        swap(midPtr, lowPtr, elemSize, swapBuffer);
    }
    if (comp(highPtr, midPtr) < 0) {
        swap(highPtr, midPtr, elemSize, swapBuffer);
    }

    return midPtr;
}

char* _partition(char* lowPtr, char* highPtr, const size_t elemSize, const comparator_t comp, void* swapBuffer, void* pivotBuffer) {
    char* pivotPtr = _select_pivot(lowPtr, highPtr, elemSize, comp, swapBuffer);
    swap(pivotPtr, lowPtr, elemSize, swapBuffer);

    memcpy(pivotBuffer, lowPtr, elemSize);
    lowPtr -= elemSize;
    highPtr += elemSize;

    while (true) {
        do {
            lowPtr += elemSize;
        } while (comp(lowPtr, pivotBuffer) < 0);

        do {
            highPtr -= elemSize;
        } while (comp(highPtr, pivotBuffer) > 0);

        if (lowPtr >= highPtr) {
            return highPtr;
        }

        swap(lowPtr, highPtr, elemSize, swapBuffer);
    }
}

void _insert_sort(char* lowPtr, char* highPtr, const size_t elemSize, const comparator_t comp, void* swapBuffer) {
    for (char* ptr1 = lowPtr + elemSize; ptr1 != highPtr; ptr1 += elemSize) {
        memcpy(swapBuffer, ptr1, elemSize);
        char* ptr2 = ptr1;

        while (comp(ptr2 - elemSize, ptr2) > 0) {
            memcpy(ptr2 - elemSize, ptr2, elemSize);
            ptr2 -= elemSize;

            if (ptr1 == ptr2) {
                break;
            }
        }

        memcpy(ptr2, swapBuffer, elemSize);
    }
}

void _intro_sort_util(char* lowPtr, char* highPtr, const size_t elemSize, const comparator_t comp, void* swapBuffer, void* pivotBuffer, size_t depthLimit) {
    size_t count = ((highPtr - lowPtr) / elemSize) + 1;

    if (count <= SIMPLE_SORT_LIMIT) {
        _insert_sort(lowPtr, highPtr + elemSize, elemSize, comp, swapBuffer);
    }
    else if (0 == depthLimit) {
        binary_heap_sort(lowPtr, count, elemSize, comp);
    }
    else {
        --depthLimit;
        char* partitionPoint = _partition(lowPtr, highPtr, elemSize, comp, swapBuffer, pivotBuffer);

        _intro_sort_util(lowPtr, partitionPoint, elemSize, comp, swapBuffer, pivotBuffer, depthLimit);
        _intro_sort_util(partitionPoint + elemSize, highPtr, elemSize, comp, swapBuffer, pivotBuffer, depthLimit);
    }
}

void intro_sort(void* arr, const size_t count, const size_t elemSize, const comparator_t comp) {
    char* lowPtr = (char*)arr;
    char* highPtr = lowPtr + count * elemSize;
    size_t depthLimit = (size_t)(2 * log2(count));
    void* swapBuffer = malloc(elemSize);
    void* pivotBuffer = malloc(elemSize);

    _intro_sort_util(lowPtr, highPtr - elemSize, elemSize, comp, swapBuffer, pivotBuffer, depthLimit);

    free(swapBuffer);
    free(pivotBuffer);
}
