#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H


#include "_sort_utils.h"

typedef char*(*searcher_t)(char*, char*, const size_t, const comparator_t);

char* linear_search(char*, char*, const size_t, const comparator_t);

char* binary_search(char*, char*, const size_t, const comparator_t);

char* exponential_search(char*, char*, const size_t, const comparator_t);

void insertion_sort(void*, const size_t, const size_t, const comparator_t, const searcher_t);

void shell_sort(void*, const size_t, const size_t, const comparator_t);


#endif
