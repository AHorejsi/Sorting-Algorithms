#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <stddef.h>

void bubble_sort(void*, const size_t, const size_t, int(*)(const void*, const void*));

void cocktail_sort(void*, const size_t, const size_t, int(*)(const void*, const void*));

void brick_sort(void*, const size_t, const size_t, int(*)(const void*, const void*));

void comb_sort(void*, const size_t, const size_t, int(*)(const void*, const void*));

#endif