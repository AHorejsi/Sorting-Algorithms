#include <stdlib.h>
#include <string.h>
#include "sort_utils.h"

void swap(void* a, void* b, const size_t size) {
    void* temp = malloc(size);
    memcpy(temp, b, size);
    memcpy(b, a, size);
    memcpy(a, temp, size);

    free(temp);
}
