#include "memory.h"

#pragma region Null Terminated Memory
memory* reallocg(memory* ptr, size_t length) {
    size_u8* newptr = (size_u8*) calloc(length + 1, sizeof(size_u8));

    if (newptr != NULL) {
        if (ptr->pointer == NULL) {
            ptr->pointer = newptr;
            return ptr;
        }

        memcpy(newptr, ptr->pointer, (length > ptr->length) ? ptr->length : length);
        ptr->length = length;
        free(ptr->pointer);
        ptr->pointer = newptr;
    }

    return ptr;
};

memory* callocg(size_t length) {
    memory* ptr = (memory*) calloc(sizeof(memory), sizeof(size_u8));
    ptr->pointer = calloc(length + 1, sizeof(size_u8));
    ptr->length = length;
    return ptr;
};

memory* mallocg(size_t length) {
    memory* ptr = (memory*) malloc(sizeof(memory));
    ptr->pointer = malloc(length + 1);
    ptr->length = length;
    *((size_u8*)ptr->pointer + length) = 0;
    return ptr;
};

void freeg(memory* ptr) {
    if (ptr == NULL)
        return;
    if (ptr->pointer != NULL)
        free(ptr->pointer);
    free(ptr);
};

size_t strleng(memory* ptr) {
    return ptr->length;
};
#pragma endregion
