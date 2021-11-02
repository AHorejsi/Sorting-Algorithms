#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "quick_sort.h"

typedef char*(*_pivot_selector_func_t)(char*, char*, const size_t, const comparator_t, void*);
typedef range_array_t(*_partition_scheme_func_t)(char*, char*, const size_t, const comparator_t, void*, void*, const _pivot_selector_func_t);
typedef char*(*_partition_point_func_t)(char*, const size_t);

typedef struct _quick_sort_algorithm {
    _pivot_selector_func_t pivotSelectorFunc;
    _partition_scheme_func_t partitionSchemeFunc;
    _partition_point_func_t left;
    _partition_point_func_t right;
} _quick_sort_algorithm_t;

char* _before_point(char* ptr, const size_t elemSize) {
    return ptr - elemSize;
}

char* _at_point(char* ptr, const size_t elemSize) {
    return ptr;
}

char* _after_point(char* ptr, const size_t elemSize) {
    return ptr + elemSize;
}

char* _first_pivot_selector(char* lowPtr, char* highPtr, const size_t elemSize, const comparator_t comp, void* swapBuffer) {
    return lowPtr;
} 

char* _middle_pivot_selector(char* lowPtr, char* highPtr, const size_t elemSize, const comparator_t comp, void* swapBuffer) {
    size_t count = (highPtr - lowPtr) / elemSize + 1;
    size_t midIndex = count / 2;

    return lowPtr + midIndex * elemSize;
}

char* _last_pivot_selector(char* lowPtr, char* highPtr, const size_t elemSize, const comparator_t comp, void* swapBuffer) {
    return highPtr;
}

char* _random_pivot_selector(char* lowPtr, char* highPtr, const size_t elemSize, const comparator_t comp, void* swapBuffer) {
    size_t count = (highPtr - lowPtr) / elemSize + 1;
    size_t randIndex = abs(rand()) % count;

    return lowPtr + randIndex * elemSize;
}

char* _median_of_three_pivot_selector(char* lowPtr, char* highPtr, const size_t elemSize, const comparator_t comp, void* swapBuffer) {
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

range_array_t _lomuto_partition_scheme(char* lowPtr, char* highPtr, const size_t elemSize, const comparator_t comp, void* swapBuffer, void* pivotBuffer, const _pivot_selector_func_t pivotSelector) {
    char* pivotPtr = pivotSelector(lowPtr, highPtr, elemSize, comp, swapBuffer);
    swap(pivotPtr, highPtr, elemSize, swapBuffer);

    memcpy(pivotBuffer, highPtr, elemSize);
    char* ptr1 = lowPtr - elemSize;

    for (char* ptr2 = lowPtr; ptr2 != highPtr; ptr2 += elemSize) {
        if (comp(ptr2, pivotBuffer) <= 0) {
            ptr1 += elemSize;
            swap(ptr1, ptr2, elemSize, swapBuffer);
        }
    }

    char* swapPtr = ptr1 + elemSize;
    swap(swapPtr, highPtr, elemSize, swapBuffer);
    range_array_t result = { swapPtr, swapPtr };

    return result;
}

range_array_t _hoare_partition_scheme(char* lowPtr, char* highPtr, const size_t elemSize, const comparator_t comp, void* swapBuffer, void* pivotBuffer, const _pivot_selector_func_t pivotSelector) {
    char* pivotPtr = pivotSelector(lowPtr, highPtr, elemSize, comp, swapBuffer);
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
            range_array_t result = { highPtr, highPtr };
            return result;
        }

        swap(lowPtr, highPtr, elemSize, swapBuffer);
    }
}

range_array_t _stable_partition_scheme(char* lowPtr, char* highPtr, const size_t elemSize, const comparator_t comp, void* swapBuffer, void* pivotBuffer, const _pivot_selector_func_t pivotSelector) {
    size_t size = highPtr - lowPtr;
    size_t midIndex = size / elemSize / 2;
    char* midPtr = lowPtr + midIndex * elemSize;

    char* pivotPtr = pivotSelector(lowPtr, highPtr, elemSize, comp, swapBuffer);
    swap(pivotPtr, midPtr, elemSize, swapBuffer);

    char* lesser = (char*)malloc(size);
    char* greater = (char*)malloc(size);
    char* lesserPtr = lesser;
    char* greaterPtr = greater;
    memcpy(pivotBuffer, midPtr, elemSize);

    for (char* ptr = lowPtr; ptr <= highPtr; ptr += elemSize) {
        if (ptr != midPtr) {
            int comparison = comp(ptr, pivotBuffer);

            if (comparison < 0) {
                memcpy(lesserPtr, ptr, elemSize);
                lesserPtr += elemSize;
            }
            else if (comparison > 0) {
                memcpy(greaterPtr, ptr, elemSize);
                greaterPtr += elemSize;
            }
            else {
                if (ptr < midPtr) {
                    memcpy(lesserPtr, ptr, elemSize);
                    lesserPtr += elemSize;
                }
                else {
                    memcpy(greaterPtr, ptr, elemSize);
                    greaterPtr += elemSize;
                }
            }
        }
    }

    size_t lesserSize = lesserPtr - lesser;
    size_t greaterSize = greaterPtr - greater;
    char* partitionPoint = lowPtr + lesserSize;

    memcpy(lowPtr, lesser, lesserSize);
    memcpy(partitionPoint, pivotBuffer, elemSize);
    memcpy(partitionPoint + elemSize, greater, greaterSize);

    free(lesser);
    free(greater);

    range_array_t result = { partitionPoint, partitionPoint };

    return result;
}

range_array_t _three_way_partition_scheme(char* lowPtr, char* highPtr, const size_t elemSize, const comparator_t comp, void* swapBuffer, void* pivotBuffer, const _pivot_selector_func_t pivotSelector) {
    char* leftPartitionPoint;
    char* rightPartitionPoint;

    if (highPtr - lowPtr <= elemSize) {
        if (comp(lowPtr, highPtr) > 0) {
            swap(lowPtr, highPtr, elemSize, swapBuffer);
        }

        leftPartitionPoint = lowPtr;
        rightPartitionPoint = highPtr;
    }
    else {
        char* pivotPtr = pivotSelector(lowPtr, highPtr, elemSize, comp, swapBuffer);
        swap(pivotPtr, highPtr, elemSize, swapBuffer);

        char* midPtr = lowPtr;
        memcpy(pivotBuffer, highPtr, elemSize);

        while (midPtr <= highPtr) {
            int comparison = comp(midPtr, pivotBuffer);

            if (comparison < 0) {
                swap(lowPtr, midPtr, elemSize, swapBuffer);
                lowPtr += elemSize;
                midPtr += elemSize;
            }
            else if (comparison > 0) {
                swap(midPtr, highPtr, elemSize, swapBuffer);
                highPtr -= elemSize;
            }
            else {
                midPtr += elemSize;
            }
        }

        leftPartitionPoint = lowPtr - elemSize;
        rightPartitionPoint = midPtr;
    }

    range_array_t result = { leftPartitionPoint, rightPartitionPoint };

    return result;
}

_pivot_selector_func_t _find_pivot_selector(const pivot_selector_t type) {
    _pivot_selector_func_t function;

    switch (type) {
    case FIRST:
        function = _first_pivot_selector;
        break;
    case MIDDLE:
        function = _middle_pivot_selector;
        break;
    case LAST:
        function = _last_pivot_selector;
        break;
    case RANDOM:
        function = _random_pivot_selector;
        break;
    case MEDIAN_OF_THREE:
        function = _median_of_three_pivot_selector;
        break;
    }

    return function;
}

_partition_scheme_func_t _find_partition_scheme(const partition_scheme_t type) {
    _partition_scheme_func_t function;

    switch (type) {
    case LOMUTO:
        function = _lomuto_partition_scheme;
        break;
    case HOARE:
        function = _hoare_partition_scheme;
        break;
    case STABLE:
        function = _stable_partition_scheme;
        break;
    case THREE_WAY:
        function = _three_way_partition_scheme;
        break;
    }

    return function;
}

_partition_point_func_t _find_left_partition_point(const partition_scheme_t type) {
    _partition_point_func_t function;

    switch (type) {
    case LOMUTO:
    case STABLE:
        function = _before_point;
        break;
    case HOARE:
    case THREE_WAY:
        function = _at_point;
        break;
    }

    return function;
}

_partition_point_func_t _find_right_partition_point(const partition_scheme_t type) {
    _partition_point_func_t function;

    switch (type) {
    case LOMUTO:
    case HOARE:
    case STABLE:
        function = _after_point;
        break;
    case THREE_WAY:
        function = _at_point;
        break;
    }

    return function;
}

void _recur_quick_sort(char* lowPtr, char* highPtr, const size_t elemSize, const comparator_t comp, void* swapBuffer, void* pivotBuffer, const _quick_sort_algorithm_t* algo) {
    if (lowPtr < highPtr) {
        range_array_t partitionPoint = algo->partitionSchemeFunc(lowPtr, highPtr, elemSize, comp, swapBuffer, pivotBuffer, algo->pivotSelectorFunc);

        _recur_quick_sort(lowPtr, algo->left(partitionPoint.lowPtr, elemSize), elemSize, comp, swapBuffer, pivotBuffer, algo);
        _recur_quick_sort(algo->right(partitionPoint.highPtr, elemSize), highPtr, elemSize, comp, swapBuffer, pivotBuffer, algo);
    }
}

void _iter_quick_sort(char* lowPtr, char* highPtr, const size_t elemSize, const comparator_t comp, void* swapBuffer, void* pivotBuffer, const _quick_sort_algorithm_t* algo) {
    size_t size = highPtr - lowPtr;
    
    if (size > elemSize) {
        char** stack = (char**)malloc((size / elemSize) * sizeof(char*));
        char** stackPtr = stack;

        memcpy(stackPtr, &lowPtr, elemSize);
        stackPtr += elemSize;
        memcpy(stackPtr, &highPtr, elemSize);
        stackPtr += elemSize;

        while (stack != stackPtr) {
            highPtr = *(stackPtr - elemSize);
            stackPtr -= elemSize;
            lowPtr = *(stackPtr - elemSize);
            stackPtr -= elemSize;

            range_array_t partitionPoint = algo->partitionSchemeFunc(lowPtr, highPtr, elemSize, comp, swapBuffer, pivotBuffer, algo->pivotSelectorFunc);
            
            char* leftPartitionPoint = algo->left(partitionPoint.lowPtr, elemSize);
            char* rightPartitionPoint = algo->right(partitionPoint.highPtr, elemSize);

            if (leftPartitionPoint > lowPtr) {
                memcpy(stackPtr, &lowPtr, elemSize);
                stackPtr += elemSize;
                memcpy(stackPtr, &leftPartitionPoint, elemSize);
                stackPtr += elemSize;
            }

            if (rightPartitionPoint < highPtr) {
                memcpy(stackPtr, &rightPartitionPoint, elemSize);
                stackPtr += elemSize;
                memcpy(stackPtr, &highPtr, elemSize);
                stackPtr += elemSize;
            }
        }

        free(stack);
    }
}

void quick_sort(void* arr, const size_t count, const size_t elemSize, const comparator_t comp, const quick_sort_config_t* config) {
    char* lowPtr = (char*)arr;
    char* highPtr = lowPtr + count * elemSize;
    void* swapBuffer = malloc(elemSize);
    void* pivotBuffer = malloc(elemSize);

    _quick_sort_algorithm_t algo = {
        _find_pivot_selector(config->pivotSelector),
        _find_partition_scheme(config->partitionScheme),
        _find_left_partition_point(config->partitionScheme),
        _find_right_partition_point(config->partitionScheme)
    };

    if (ITERATIVE == config->algoType) {
        _iter_quick_sort(lowPtr, highPtr - elemSize, elemSize, comp, swapBuffer, pivotBuffer, &algo);
    }
    else if (RECURSIVE == config->algoType) {
        _recur_quick_sort(lowPtr, highPtr - elemSize, elemSize, comp, swapBuffer, pivotBuffer, &algo);
    }

    free(swapBuffer);
    free(pivotBuffer);
}
