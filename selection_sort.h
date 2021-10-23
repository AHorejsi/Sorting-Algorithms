#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H


#include <stddef.h>
#include "_sort_utils.h"

void selection_sort(void*, const size_t, const size_t, const comparator_t);

void stable_selection_sort(void*, const size_t, const size_t, const comparator_t);

void double_selection_sort(void*, const size_t, const size_t, const comparator_t);


#endif
