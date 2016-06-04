#include "nullmem.h"

#pragma region Null Terminated Memory
void* reallocg(void* ptr, size_t size) {
    void* nptr = calloc(size + 1, 1);

    if (nptr != NULL) {
        if (ptr == NULL)
            return nptr;

        size_t plen = strlen((char*)ptr);
        memcpy(nptr, ptr, (size > plen) ? plen : size);

        free(ptr);
        return nptr;
    }

    return ptr;
};

void* callocg(size_t size) {
    return calloc(size + 1, sizeof(char));
};

void* mallocg(size_t size) {
    void* ptr = malloc(size + 1);
    *((char*)ptr + size) = 0;
    return ptr;
};
#pragma endregion
