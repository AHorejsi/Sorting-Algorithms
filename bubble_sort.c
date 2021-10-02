#include <stdbool.h>
#include "sort_utils.h"
#include "bubble_sort.h"

void bubble_sort(void* arr, const size_t count, const size_t size, int(*comp)(const void*, const void*)) {
    char* usable = (char*)arr;
    size_t end = count - 1;

    for (size_t i = 0; i < end; ++i) {
        bool swapped = false;

        for (size_t j = 0; j < end; ++j) {
            char* elem = usable + (j * size);
            void* first = elem;
            void* second = elem + size;

            if (comp(first, second) > 0) {
                swap(first, second, size);
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }
}
