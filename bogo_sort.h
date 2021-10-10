#ifndef BOGO_SORT_H
#define BOGO_SORT_H


#include <stddef.h>
#include "sort_utils.h"

typedef void(*shuffler_t)(void*, const size_t, const size_t, void*);

void bogo_sort(void*, const size_t, const size_t, const comparator_t, const shuffler_t);

void permutation_sort(void*, const size_t, const size_t, const comparator_t);


#endif
