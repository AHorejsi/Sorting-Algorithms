#include <stdbool.h>
#include <stdlib.h>
#include "bubble_sort.h"

void bubble_sort(void* arr, const size_t count, const size_t elemSize, const comparator_t comp) {
    size_t endIndex = count - 1;
    char* ptr = (char*)arr;
    char* endPtr = ptr + (endIndex * elemSize);
    void* buffer = malloc(elemSize);

    for (size_t i = 0; i < endIndex; ++i) {
        bool swapped = false;

        for (char* current = ptr; current < endPtr; current += elemSize) {
            char* next = current + elemSize;

            if (comp(next, current) < 0) {
                swap(current, next, elemSize, buffer);
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }

    free(buffer);
}

bool _bubble_up(char* lowPtr, char* highPtr, const size_t elemSize, const comparator_t comp, void* buffer) {
    bool swapped = false;

    for (char* current = lowPtr; current < highPtr; current += elemSize) {
        char* next = current + elemSize;

        if (comp(next, current) < 0) {
            swap(current, next, elemSize, buffer);
            swapped = true;
        }
    }

    return swapped;
}

bool _bubble_down(char* lowPtr, char* highPtr, const size_t elemSize, const comparator_t comp, void* buffer) {
    bool swapped = false;

    for (char* current = highPtr - elemSize; current >= lowPtr; current -= elemSize) {
        char* next = current + elemSize;

        if (comp(next, current) < 0) {
            swap(current, next, elemSize, buffer);
            swapped = true;
        }
    }

    return swapped;
}

void cocktail_sort(void* arr, const size_t count, const size_t elemSize, const comparator_t comp) {
    char* lowPtr = (char*)arr;
    char* highPtr = lowPtr + elemSize * (count - 1);
    void* buffer = malloc(elemSize);
    bool swapped = true;

    while (swapped) {
        swapped = _bubble_up(lowPtr, highPtr, elemSize, comp, buffer);

        if (!swapped) {
            return;
        }

        highPtr -= elemSize;
        swapped = _bubble_down(lowPtr, highPtr, elemSize, comp, buffer);
        lowPtr += elemSize;
    }

    free(buffer);
}

bool _bubble_up_even_indices(char* lowPtr, char* highPtr, const size_t elemSize, const comparator_t comp, void* buffer) {
    bool isSortedOnEvenIndices = true;
    size_t increase = elemSize + elemSize;
    char* endPtr = highPtr - increase;

    for (char* current = lowPtr; current <= endPtr; current += increase) {
        char* next = current + elemSize;

        if (comp(next, current) < 0) {
            swap(current, next, elemSize, buffer);
            isSortedOnEvenIndices = false;
        }
    }

    return isSortedOnEvenIndices;
}

bool _bubble_up_odd_indices(char* lowPtr, char* highPtr, const size_t elemSize, const comparator_t comp, void* buffer) {
    bool isSortedOnOddIndices = true;
    size_t increase = elemSize + elemSize;
    char* endPtr = highPtr - increase;

    for (char* current = lowPtr + elemSize; current <= endPtr; current += increase) {
        char* next = current + elemSize;

        if (comp(next, current) < 0) {
            swap(current, next, elemSize, buffer);
            isSortedOnOddIndices = false;
        }
    }

    return isSortedOnOddIndices;
}

void print(int* arr, const size_t count) {
    for (size_t index = 0; index < count; ++index) {
        printf("%d ", arr[index]);
    }

    puts("\n");
}

void brick_sort(void* arr, const size_t count, const size_t elemSize, const comparator_t comp) {
    char* lowPtr = (char*)arr;
    char* highPtr = lowPtr + elemSize * count;
    void* buffer = malloc(elemSize);
    bool isSortedOnEvenIndices = false;
    bool isSortedOnOddIndices = false;

    while (!(isSortedOnEvenIndices && isSortedOnOddIndices)) {
        isSortedOnEvenIndices = _bubble_up_even_indices(lowPtr, highPtr, elemSize, comp, buffer);
        isSortedOnOddIndices = _bubble_up_odd_indices(lowPtr, highPtr, elemSize, comp, buffer);
    }

    free(buffer);
}

size_t _next_gap(const size_t gap) {
    size_t nextGap = gap * 10 / 13;

    if (nextGap < 1) {
        nextGap = 1;
    }

    return nextGap;
}

void comb_sort(void* arr, const size_t count, const size_t elemSize, const comparator_t comp) {
    char* lowPtr = (char*)arr;
    char* highPtr = lowPtr + elemSize * count;
    void* buffer = malloc(elemSize);
    bool swapped = true;
    size_t gap = count;

    while (swapped || gap > 1) {
        gap = _next_gap(gap);
        swapped = false;
        char* endPtr = highPtr - gap * elemSize;

        for (char* current = lowPtr; current < endPtr; current += elemSize) {
            char* next = current + gap * elemSize;

            if (comp(next, current) < 0) {
                swap(current, next, elemSize, buffer);
                swapped = true;
            }
        }
    }

    free(buffer);
}
