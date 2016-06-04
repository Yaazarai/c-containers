#ifndef C_VECTOR
#define C_VECTOR
    #include <stdlib.h>
    #include <string.h>
    #include "cbase.h"

    typedef struct c_vector {
        ui32 typesz, cachesz, length, cached;
        memory* memory;
    } cvector;

    #define cv_alloc(ty, cachesz) cb_allocg(cvector, ty, cachesz)
    #define cv_free(ptr) cb_freeg(ptr)
    #define cv_cache(ptr) cb_cacheg(ptr)
    #define cv_resize(ptr, length) cb_resizeg(ptr, length)

    #define cv_clear(ptr) cb_clearg(ptr)
    #define cv_empty(ptr) cb_emptyg(ptr)

    #define cv_size(ptr) cb_sizeg(ptr)
    #define cv_cachesize(ptr) cb_cachesizeg(ptr)
    #define cv_maxsize(ptr) cb_maxsizeg(ptr)
    #define cv_count(ptr) cb_countg(ptr)

    #define cv_begin(ptr) cb_beging(ptr)
    #define cv_end(ptr) cb_endg(ptr)
    #define cv_rbegin(ptr) cb_rbeging(ptr)
    #define cv_rend(ptr) cb_rendg(ptr)

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
