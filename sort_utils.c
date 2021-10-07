#include <stdlib.h>
#include <string.h>
#include "sort_utils.h"

void swap(void* a, void* b, const size_t elemSize, void* buffer) {
    memcpy(buffer, b, elemSize);
    memcpy(b, a, elemSize);
    memcpy(a, buffer, elemSize);
}
