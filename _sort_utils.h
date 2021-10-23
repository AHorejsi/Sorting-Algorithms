#ifndef _SORT_UTILS_H
#define _SORT_UTILS_H


#include <stddef.h>
#include <stdbool.h>

typedef int(*comparator_t)(const void*, const void*);

typedef struct range_array {
    char* lowPtr;
    char* highPtr;
} range_array_t;

void swap(void*, void*, const size_t, void*);

bool is_sorted(void*, const size_t, const size_t, const comparator_t);

size_t minimum(const size_t, const size_t);


#endif
