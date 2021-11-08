#include <string.h>
#include <stdlib.h>
#include "sort_utils.h"
#include "counting_sort.h"

size_t _min(char* lowPtr, char* highPtr, const size_t count, const size_t elemSize) {
    size_t minValue = *(size_t*)lowPtr;
    
    for (char* ptr = lowPtr + elemSize; ptr != highPtr; ptr += elemSize) {
        minValue = minimum(*(size_t*)ptr, minValue);
    }

    return minValue;
}

size_t _max(char* lowPtr, char* highPtr, const size_t count, const size_t elemSize) {
    size_t maxValue = *(size_t*)lowPtr;
    
    for (char* ptr = lowPtr + elemSize; ptr != highPtr; ptr += elemSize) {
        maxValue = maximum(*(size_t*)ptr, maxValue);
    }

    return maxValue;
}

void counting_sort(void* arr, const size_t count, const size_t elemSize) {
    char* lowPtr = (char*)arr;
    char* highPtr = lowPtr + count * elemSize;

    size_t minValue = _min(lowPtr, highPtr, count, elemSize);
    size_t maxValue = _max(lowPtr, highPtr, count, elemSize);
    size_t range = maxValue - minValue + 1;
    
    size_t* counts = (size_t*)calloc(range, sizeof(size_t));
    size_t* output = (size_t*)malloc(count * sizeof(size_t));

    for (char* ptr = lowPtr; ptr != highPtr; ptr += elemSize) {
        ++(counts[*(size_t*)ptr - minValue]);
    }

    for (size_t index = 1; index < range; ++index) {
        counts[index] += counts[index - 1];
    }

    for (char* ptr = highPtr - elemSize; ptr >= lowPtr; ptr -= elemSize) {
        size_t countsIndex = *(size_t*)ptr - minValue;

        memcpy(output + (counts[countsIndex] - 1), lowPtr, elemSize);
        --(counts[countsIndex]);
    }

    memcpy(lowPtr, output, count * elemSize);

    free(counts);
    free(output);
}
