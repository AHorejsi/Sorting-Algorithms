#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <stddef.h>

void selection_sort(void*, const size_t, const size_t, int(*)(const void*, const void*));

void stable_selection_sort(void*, const size_t, const size_t, int(*)(const void*, const void*));

void double_selection_sort(void*, const size_t, const size_t, int(*)(const void*, const void*));

#endif
