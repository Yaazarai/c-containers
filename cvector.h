#ifndef C_VECTOR
#define C_VECTOR
    #include <stdlib.h>
    #include <string.h>
    #include "base/carray.h"

    typedef struct c_vector {
        ui32 typesz, cachesz, length, cached;
        memory* memory;
    } cvector;

    #define cv_alloc(ty, cachesz) ca_allocg(cvector, ty, cachesz)
    #define cv_free(ptr) ca_freeg(ptr)
    #define cv_cache(ptr) ca_cacheg(ptr)
    #define cv_resize(ptr, length) ca_resizeg(ptr, length)

    #define cv_clear(ptr) ca_clearg(ptr)
    #define cv_empty(ptr) ca_emptyg(ptr)

    #define cv_size(ptr) ca_sizeg(ptr)
    #define cv_cachesize(ptr) ca_cachesizeg(ptr)
    #define cv_maxsize(ptr) ca_maxsizeg(ptr)
    #define cv_count(ptr) ca_countg(ptr)

    #define cv_begin(ptr) ca_beging(ptr)
    #define cv_end(ptr) ca_endg(ptr)
    #define cv_rbegin(ptr) ca_rbeging(ptr)
    #define cv_rend(ptr) ca_rendg(ptr)

    void cv_pushback(cvector* cvec, type data);
    void cv_pushfront(cvector* cvec, type data);
    void cv_insert(cvector* cvec, ui32 pos, type data);
    void cv_remove(cvector* cvec, ui32 pos);

    type cv_get(cvector* cvec, ui32 pos);
    void cv_set(cvector* cvec, ui32 pos, type data);

    void cv_copy(cvector* cvecs, cvector* cvecd);
    cvector* cv_clone(cvector* cvec);

    void cv_swap(cvector* cvec, ui32 posx, ui32 posy);
    void cv_reverse(cvector* cvec);
#endif
