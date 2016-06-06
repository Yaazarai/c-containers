#ifndef C_STACK
#define C_STACK
    #include <stdlib.h>
    #include <string.h>
    #include "base/carray.h"

    typedef struct c_stack {
        ui32 typesz, cachesz, length, cached;
        memory* memory;
    } cstack;

    #define cs_alloc(ty, cachesz) ca_allocg(cstack, ty, cachesz)
    #define cs_free(ptr) ca_freeg(ptr)

    #define cs_clear(ptr) ca_clearg(ptr)
    #define cs_empty(ptr) ca_emptyg(ptr)

    #define cs_size(ptr) ca_sizeg(ptr)
    #define cs_cachesize(ptr) ca_cachesizeg(ptr)
    #define cs_maxsize(ptr) ca_maxsizeg(ptr)
    #define cs_count(ptr) ca_countg(ptr)

    type cs_top(cstack* cstk);
    type cs_get(cstack* cstk, ui32 pos);
    void cs_push(cstack* cstk, type data);
    void cs_pop(cstack* cstk);
#endif
