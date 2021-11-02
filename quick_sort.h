#ifndef QUICK_SORT_H
#define QUICK_SORT_H


#include <stddef.h>
#include "sort_utils.h"

typedef enum pivot_selector { FIRST, MIDDLE, LAST, RANDOM, MEDIAN_OF_THREE } pivot_selector_t;
typedef enum partition_scheme { LOMUTO, HOARE, STABLE, THREE_WAY } partition_scheme_t;

typedef struct quick_sort_config {
    pivot_selector_t pivotSelector;
    partition_scheme_t partitionScheme;
    algorithm_type_t algoType;
} quick_sort_config_t;

void quick_sort(void*, const size_t, const size_t, const comparator_t, const quick_sort_config_t*);


#endif
