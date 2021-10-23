#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "merge_sort.h"

range_array_t _make_subarray(char* lowPtr, char* highPtr, const size_t elemSize) {
    size_t subSize = highPtr - lowPtr;
    char* subArr = (char*)malloc(subSize);
    memcpy(subArr, lowPtr, subSize);

    range_array_t arr = { subArr, subArr + subSize };

    return arr;
}

void merge(char* lowPtr, char* midPtr, char* highPtr, const size_t elemSize, const comparator_t comp) {
    range_array_t leftArr = _make_subarray(lowPtr, midPtr, elemSize);
    range_array_t rightArr = _make_subarray(midPtr, highPtr, elemSize);

    char* leftPtr = leftArr.lowPtr;
    char* rightPtr = rightArr.lowPtr;
    char* ptr = lowPtr;

    while (leftPtr != leftArr.highPtr && rightPtr != rightArr.highPtr) {
        if (comp(leftPtr, rightPtr) <= 0) {
            memcpy(ptr, leftPtr, elemSize);
            leftPtr += elemSize;
        }
        else {
            memcpy(ptr, rightPtr, elemSize);
            rightPtr += elemSize;
        }

        ptr += elemSize;
    }

    while (leftPtr != leftArr.highPtr) {
        memcpy(ptr, leftPtr, elemSize);

        leftPtr += elemSize;
        ptr += elemSize;
    }

    while (rightPtr != rightArr.highPtr) {
        memcpy(ptr, rightPtr, elemSize);

        rightPtr += elemSize;
        ptr += elemSize;
    }

    free(leftArr.lowPtr);
    free(rightArr.lowPtr);
}

void in_place_merge(char* lowPtr, char* midPtr, char* highPtr, const size_t elemSize, const comparator_t comp) {
    char* start = midPtr;
    void* buffer = malloc(elemSize);

    while (lowPtr < midPtr && start < highPtr) {
        if (comp(lowPtr, start) <= 0) {
            lowPtr += elemSize;
        }
        else {
            memcpy(buffer, start, elemSize);
            char* ptr = start;

            while (ptr != lowPtr) {
                memcpy(ptr, ptr - elemSize, elemSize);
                ptr -= elemSize;
            }

            memcpy(lowPtr, buffer, elemSize);

            lowPtr += elemSize;
            midPtr += elemSize;
            start += elemSize;
        }
    }

    free(buffer);
}

void bottom_up_merge_sort(void* arr, const size_t count, const size_t elemSize, const comparator_t comp, const merger_t merger) {
    char* lowPtr = (char*)arr;
    size_t endIndex = count - 1;

    for (size_t currentCount = 1; currentCount < count; currentCount += currentCount) {
        size_t increment = currentCount + currentCount;

        for (size_t leftIndex = 0; leftIndex < count; leftIndex += increment) {
            size_t midIndex = minimum(leftIndex + currentCount, endIndex);
            size_t rightIndex = minimum(leftIndex + increment, count);

            char* leftPtr = lowPtr + leftIndex * elemSize;
            char* midPtr = lowPtr + midIndex * elemSize;
            char* rightPtr = lowPtr + rightIndex * elemSize;

            merger(leftPtr, midPtr, rightPtr, elemSize, comp);
        }
    }
}

void _run_top_down_merge_sort(char* lowPtr, char* highPtr, const size_t elemSize, const comparator_t comp, const merger_t merger) {
    size_t size = highPtr - lowPtr;
    size_t count = size / elemSize;

    if (count > 1) {
        size_t midpoint = size / 2 / elemSize;
        char* midPtr = lowPtr + midpoint * elemSize;

        _run_top_down_merge_sort(lowPtr, midPtr, elemSize, comp, merger);
        _run_top_down_merge_sort(midPtr, highPtr, elemSize, comp, merger);

        merger(lowPtr, midPtr, highPtr, elemSize, comp);
    }
}

void top_down_merge_sort(void* arr, const size_t count, const size_t elemSize, const comparator_t comp, const merger_t merger) {
    char* lowPtr = (char*)arr;
    char* highPtr = lowPtr + count * elemSize;
    
    _run_top_down_merge_sort(lowPtr, highPtr, elemSize, comp, merger);
}
