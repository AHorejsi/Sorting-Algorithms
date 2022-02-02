#ifndef SORT_UTILS_H
#define SORT_UTILS_H


#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

typedef intmax_t index_t;
typedef char* byte_t;

typedef int(*comparator_t)(const void*, const void*);
typedef void(*sorter_t)(void*, const size_t, const size_t, const comparator_t);

typedef enum algorithm_type { ITERATIVE, RECURSIVE } algorithm_type_t;

typedef struct range_array {
    byte_t lowPtr;
    byte_t highPtr;
} range_array_t;

void swap(void*, void*, const size_t, void*);

bool is_sorted(void*, const size_t, const size_t, const comparator_t);

size_t minimum(const size_t, const size_t);

size_t maximum(const size_t, const size_t);

int double_compare(const void*, const void*);


#endif
