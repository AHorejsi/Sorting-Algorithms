#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H


#include <stddef.h>
#include "_sort_utils.h"

void bubble_sort(void*, const size_t, const size_t, const comparator_t);

void cocktail_sort(void*, const size_t, const size_t, const comparator_t);

void brick_sort(void*, const size_t, const size_t, const comparator_t);

void comb_sort(void*, const size_t, const size_t, const comparator_t);


#endif
