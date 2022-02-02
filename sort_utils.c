#include <string.h>
#include "sort_utils.h"

void swap(void* a, void* b, const size_t elemSize, void* buffer) {
    memcpy(buffer, b, elemSize);
    memcpy(b, a, elemSize);
    memcpy(a, buffer, elemSize);
}

bool is_sorted(void* arr, const size_t count, const size_t elemSize, const comparator_t comp) {
    char* lowPtr = (char*)arr;
    char* highPtr = lowPtr + (count - 1) * elemSize;

    for (char* current = lowPtr; current != highPtr; current += elemSize) {
        char* next = current + elemSize;

        if (comp(current, next) > 0) {
            return false;
        }
    }

    return true;
}

size_t minimum(const size_t first, const size_t second) {
    return second ^ ((first ^ second) & -(first < second));
}

size_t maximum(const size_t first, const size_t second) {
    return first ^ ((first ^ second) & -(first < second));
}

int double_compare(const void* left, const void* right) {
    return *(double*)left < *(double*)right;
}
