#ifndef C_STACK
#define C_STACK
    #include <stdlib.h>
    #include <string.h>
    #include "base\cbase.h"

    typedef struct c_stack {
        ui32 typesz, cachesz, length, cached;
        ui08* memory;
    } cstack;

    #define cs_alloc(ty, cachesz) cb_allocg(ty, cachesz)
    #define cs_free(ptr) cb_freeg(ptr)
    #define cs_cache(ptr) cb_cacheg(ptr)
    #define cs_resize(ptr, length) cb_resizeg(ptr, length)

    type cs_top(cstack* cstk);
    void cs_push(cstack* cstk, type data);
    void cs_pop(cstack* cstk);

    void cs_swap(cstack* cstks, cstack* cstkd);
    cbool cs_empty(cstack* cstk);

    ui32 cs_size(cstack* cstk);
    ui32 cs_cachesize(cstack* cstk);
    ui32 cs_maxsize(cstack* cstk);
    ui32 cs_count(cstack* cstk);
#endif
