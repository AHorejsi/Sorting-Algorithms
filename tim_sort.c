#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "insertion_sort.h"
#include "sort_utils.h"
#include "tim_sort.h"

range_array_t _create_subarray(char* lowPtr, char* highPtr) {
    size_t subSize = highPtr - lowPtr;
    char* subArr = (char*)malloc(subSize);
    memcpy(subArr, lowPtr, subSize);

    range_array_t arr = { subArr, subArr + subSize };

    return arr;
}

void _merge(char* lowPtr, char* midPtr, char* highPtr, const size_t elemSize, const comparator_t comp) {
    range_array_t leftArr = _create_subarray(lowPtr, midPtr);
    range_array_t rightArr = _create_subarray(midPtr, highPtr);

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

    memcpy(ptr, leftPtr, leftArr.highPtr - leftPtr);
    memcpy(ptr, rightPtr, rightArr.highPtr - rightPtr);

    free(leftArr.lowPtr);
    free(rightArr.lowPtr);
}

void tim_sort(void* arr, const size_t count, const size_t elemSize, const comparator_t comp) {
    size_t run = 32;
    char* lowPtr = (char*)arr;

    for (size_t index = 0; index < count; index += run) {
        size_t endIndex = minimum(index + run, count);
        size_t subcount = endIndex - index;

        insertion_sort(lowPtr + index * elemSize, subcount, elemSize, comp, linear_search);
    }

    size_t endIndex = count - 1;

    for (size_t currentCount = run; currentCount < count; currentCount += currentCount) {
        size_t increment = currentCount + currentCount;

        for (size_t leftIndex = 0; leftIndex < count; leftIndex += increment) {
            size_t midIndex = minimum(leftIndex + currentCount, endIndex);
            size_t rightIndex = minimum(leftIndex + increment, count);

            char* leftPtr = lowPtr + leftIndex * elemSize;
            char* midPtr = lowPtr + midIndex * elemSize;
            char* rightPtr = lowPtr + rightIndex * elemSize;

            _merge(leftPtr, midPtr, rightPtr, elemSize, comp);
        }
    }
}
