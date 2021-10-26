#ifndef HEAP_SORT_H
#define HEAP_SORT_H


#include "_sort_utils.h"

void binary_heap_sort(void*, const size_t, const size_t, const comparator_t);

void weak_heap_sort(void*, const size_t, const size_t, const comparator_t);

void smooth_sort(void*, const size_t, const size_t, const comparator_t);


#endif
