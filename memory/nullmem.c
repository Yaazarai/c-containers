#include "nullmem.h"

#pragma region Null Terminated Memory
void* reallocg(void* ptr, size_t oldsz, size_t newsz) {
    void* nptr = calloc(newsz + 1, sizeof(char));

    if (nptr != NULL) {
        if (ptr == NULL)
            return nptr;

        size_t plen = oldsz;
        memcpy(nptr, ptr, (newsz > plen) ? plen : newsz);

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
