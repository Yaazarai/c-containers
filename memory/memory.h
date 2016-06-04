#ifndef C_MEMORY
#define C_MEMORY
    #include <stdlib.h>
    #include <string.h>

    typedef unsigned char size_u8;
    typedef struct c_memory {
        size_t length;
        size_u8* pointer;
    } memory;

    memory* reallocg(memory* ptr, size_t length);
    memory* callocg(size_t length);
    memory* mallocg(size_t length);
    size_t strleng(memory* ptr);
    void freeg(memory* ptr);
#endif
