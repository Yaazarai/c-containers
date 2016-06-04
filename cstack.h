#ifndef C_STACK
#define C_STACK
    #include <stdlib.h>
    #include <string.h>
    #include "cbase.h"

    typedef struct c_stack {
        ui32 typesz, cachesz, length, cached;
        memory* memory;
    } cstack;

    #define cs_alloc(ty, cachesz) cb_allocg(cstack, ty, cachesz)
    #define cs_free(ptr) cb_freeg(ptr)
    #define cs_cache(ptr) cb_cacheg(ptr)
    #define cs_resize(ptr, length) cb_resizeg(ptr, length)

    #define cs_clear(ptr) cb_clearg(ptr)
    #define cs_empty(ptr) cb_emptyg(ptr)

    #define cs_size(ptr) cb_sizeg(ptr)
    #define cs_cachesize(ptr) cb_cachesizeg(ptr)
    #define cs_maxsize(ptr) cb_maxsizeg(ptr)
    #define cs_count(ptr) cb_countg(ptr)

    #define cs_begin(ptr) cb_beging(ptr)
    #define cs_end(ptr) cb_endg(ptr)
    #define cs_rbegin(ptr) cb_rbeging(ptr)
    #define cs_rend(ptr) cb_rendg(ptr)

    type cs_top(cstack* cstk);
    void cs_push(cstack* cstk, type data);
    void cs_pop(cstack* cstk);
#endif
