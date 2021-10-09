#include <stdlib.h>
#include <string.h>
#include "sort_utils.h"
#include "selection_sort.h"

char* _find_min(char* lowPtr, char* highPtr, const size_t elemSize, int(*comp)(const void*, const void*)) {
    char* minValue = lowPtr;

    for (char* current = lowPtr + elemSize; current != highPtr; current += elemSize) {
        if (comp(current, minValue) < 0) {
            minValue = current;
        }
    }

    return minValue;
}

void selection_sort(void* arr, const size_t count, const size_t elemSize, int(*comp)(const void*, const void*)) {
    char* lowPtr = (char*)arr;
    char* highPtr = lowPtr + elemSize * count;
    void* buffer = malloc(elemSize);
    
    for (char* current = lowPtr; current != highPtr; current += elemSize) {
        char* minValue = _find_min(current, highPtr, elemSize, comp);

        if (minValue != current) {
            swap(minValue, current, elemSize, buffer);
        }
    }

    free(buffer);
}

void _stable_swap(char* lowPtr, char* highPtr, const size_t elemSize, void* buffer) {
    memcpy(buffer, highPtr, elemSize);

    for (char* current = highPtr; current != lowPtr; current -= elemSize) {
        memcpy(current, current - elemSize, elemSize);
    }

    memcpy(lowPtr, buffer, elemSize);
}

void stable_selection_sort(void* arr, const size_t count, const size_t elemSize, int(*comp)(const void*, const void*)) {
    char* lowPtr = (char*)arr;
    char* highPtr = lowPtr + elemSize * count;
    void* buffer = malloc(elemSize);

    for (char* current = lowPtr; current != highPtr; current += elemSize) {
        char* minValue = _find_min(current, highPtr, elemSize, comp);

        if (minValue != current) {
            _stable_swap(current, minValue, elemSize, buffer);
        }
    }

    free(buffer);
}

char* _find_max(char* lowPtr, char* highPtr, const size_t elemSize, int(*comp)(const void*, const void*)) {
    char* maxValue = lowPtr;

    for (char* current = lowPtr + elemSize; current != highPtr; current += elemSize) {
        if (comp(current, maxValue) > 0) {
            maxValue = current;
        }
    }

    return maxValue;
}

void double_selection_sort(void* arr, const size_t count, const size_t elemSize, int(*comp)(const void*, const void*)) {
    char* lowPtr = (char*)arr;
    char* highPtr = lowPtr + count * elemSize;
    void* buffer = malloc(elemSize);

    while (lowPtr < highPtr) {
        char* minValue = _find_min(lowPtr, highPtr, elemSize, comp);
        char* maxValue = _find_max(lowPtr, highPtr, elemSize, comp);

        if (minValue != lowPtr) {
            swap(lowPtr, minValue, elemSize, buffer);
        }
        if (maxValue != highPtr) {
            swap(highPtr - elemSize, comp(minValue, maxValue) > 0 ? minValue : maxValue, elemSize, buffer);
        }

        lowPtr += elemSize;
        highPtr -= elemSize;
    }

    free(buffer);
}
