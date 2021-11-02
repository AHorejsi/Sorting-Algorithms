#ifndef MERGE_SORT_H
#define MERGE_SORT_H


#include "sort_utils.h"

typedef void(*merger_t)(char*, char*, char*, const size_t, const comparator_t);

void merge(char*, char*, char*, const size_t, const comparator_t);

void in_place_merge(char*, char*, char*, const size_t, const comparator_t);

void bottom_up_merge_sort(void*, const size_t, const size_t, const comparator_t, const merger_t);

void top_down_merge_sort(void*, const size_t, const size_t, const comparator_t, const merger_t);


#endif
