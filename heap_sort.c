#include <stdlib.h>
#include <stddef.h>
#include "heap_sort.h"

ptrdiff_t _find_index_of_largest(char* arr, const ptrdiff_t index, const ptrdiff_t count, const ptrdiff_t elemSize, const comparator_t comp) {
    ptrdiff_t indexOfLargest = index;
    ptrdiff_t indexOfLeft = 2 * index + 1;
    ptrdiff_t indexOfRight = 2 * index + 2;

    char* ptrOfLargest = arr + indexOfLargest * elemSize;
    char* ptrOfLeft = arr + indexOfLeft * elemSize;
    char* ptrOfRight = arr + indexOfRight * elemSize;

    if (indexOfLeft < count && comp(ptrOfLeft, ptrOfLargest) > 0) {
        ptrOfLargest = ptrOfLeft;
        indexOfLargest = indexOfLeft;
    }

    if (indexOfRight < count && comp(ptrOfRight, ptrOfLargest) > 0) {
        ptrOfLargest = ptrOfRight;
        indexOfLargest = indexOfRight;
    }

    return indexOfLargest;
}

void _heapify(char* arr, ptrdiff_t index, const ptrdiff_t count, const ptrdiff_t elemSize, const comparator_t comp, void* buffer) {
    ptrdiff_t indexOfLargest;

    while (true) {
        indexOfLargest = _find_index_of_largest(arr, index, count, elemSize, comp);

        if (index == indexOfLargest) {
            break;
        }
        else {
            swap(arr + index * elemSize, arr + indexOfLargest * elemSize, elemSize, buffer);
            index = indexOfLargest;
        }
    }
}

void binary_heap_sort(void* arr, const size_t count, const size_t elemSize, const comparator_t comp) {
    char* lowPtr = (char*)arr;
    char* highPtr = lowPtr + count * elemSize;
    void* buffer = malloc(elemSize);

    ptrdiff_t lowIndex = 0;
    ptrdiff_t highIndex = count - 1;
    ptrdiff_t midIndex = (lowIndex + highIndex) / 2;

    for (ptrdiff_t index = midIndex; index >= lowIndex; --index) {
        _heapify(lowPtr, index, highIndex, elemSize, comp, buffer);
    }

    for (ptrdiff_t index = highIndex; index > lowIndex; --index) {
        swap(lowPtr, lowPtr + index * elemSize, elemSize, buffer);
        _heapify(lowPtr, lowIndex, index, elemSize, comp, buffer);
    }

    free(buffer);
}
