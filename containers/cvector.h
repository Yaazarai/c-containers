#ifndef C_VECTOR
#define C_VECTOR
    #include <stdlib.h>
    #include <string.h>
    #include "base\cbase.h"

    typedef enum cv_iterpos {
        cv_begin, cv_end, cv_rbegin, cv_rend
    } cviterpos;

    typedef struct c_vector {
        ui32 typesz, cachesz, length, cached;
        ui08* memory;
    } cvector;

    typedef struct cv_iter {
        cvector* memory;
        ui08* iteration;
        enum cviterpos iterpos;
    } cviter;

    #define cv_alloc(strc, ty, cachesz) cb_allocg(strc, ty, cachesz)
    #define cv_free(ptr) cb_freeg(ptr)
    #define cv_cache(ptr) cb_cacheg(ptr)
    #define cv_resize(ptr, length) cb_resizeg(ptr, length)

    void cvpushback(cvector* cvec, type data);
    void cvpushfront(cvector* cvec, type data);
    void cvinsert(cvector* cvec, ui32 pos, type data);
    void cvremove(cvector* cvec, ui32 pos);

    type cvget(cvector* cvec, ui32 pos);
    void cvset(cvector* cvec, ui32 pos, type data);

    void cvcopy(cvector* cvecs, cvector* cvecd);
    cvector* cvclone(cvector* cvec);

    void cvswap(cvector* cvec, ui32 posx, ui32 posy);
    void cvreverse(cvector* cvec);

    void cvclear(cvector* cvec);
    cbool cvempty(cvector* cvec);

    cviter cvbegin(cvector* cvec);
    cviter cvend(cvector* cvec);
    cviter cvrbegin(cvector* cvec);
    cviter cvrend(cvector* cvec);

    ui32 cvsize(cvector* cvec);
    ui32 cvcachesize(cvector* cvec);
    ui32 cvmaxsize(cvector* cvec);
    ui32 cvcount(cvector* cvec);
#endif
