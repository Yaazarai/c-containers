#ifndef NULL_MEMORY
#define NULL_MEMORY
    #include <stdlib.h>
    #include <string.h>

    void* reallocg(void* ptr, size_t oldsz, size_t newsz);
    void* callocg(size_t size);
    void* mallocg(size_t size);
#endif
