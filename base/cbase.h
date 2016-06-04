/*
    Generic container library for dynamic memory.
*/
/*
    C doesn't support OOP--obviously--but the hack here is that
    the members of a struct will ALWAYS be defined in the same
    order in memory.

    This means if we redefine a new struct with the same members
    in the same order, we can cast the new struct back to the
    base struct as a generic container.

        --> I know you just cringed, don't hurt me. <--
*/

#ifndef CONTAINER_BASE
#define CONTAINER_BASE
    #include <stdlib.h>
    #include <string.h>
    #include "nullmem.h"
    
    typedef unsigned int ui32;
    typedef unsigned char ui08;
    typedef void* type;

    typedef enum cb_bool {
        c_false, c_true
    } cbool;

    typedef struct c_base {
        ui32 typesz, cachesz, length, cached;
        ui08* memory;
    } cbase;

    typedef enum cb_iterpos {
        cbbegin, cbend, cbrbegin, cbrend
    } cbiterpos;

    typedef struct cb_iter {
        void* memory;
        ui08* iteration;
        enum cbiterpos iterpos;
    } cbiter;

    cbase* cb_alloc(ui32 strcsz, ui32 typesz, ui32 cachesz);
    void cb_free(cbase* cbse);
    cbool cb_cache(cbase* cbse);
    cbool cb_resize(cbase* cbse, ui32 length);

    void cb_clear(cbase* cbse);
    cbool cb_empty(cbase* cbse);

    ui32 cb_size(cbase* cbse);
    ui32 cb_cachesize(cbase* cbse);
    ui32 cb_maxsize(cbase* cbse);
    ui32 cb_count(cbase* cbse);

    cbiter cb_begin(cbase* cbse);
    cbiter cb_end(cbase* cbse);
    cbiter cb_rbegin(cbase* cbse);
    cbiter cb_rend(cbase* cbse);

    #define cb_allocg(strc, ty, cachesz) (strc*) cb_alloc(sizeof(strc), sizeof(ty), cachesz)
    #define cb_freeg(ptr) cb_free((cbase*) ptr)
    #define cb_cacheg(ptr) cb_cache((cbase*) ptr)
    #define cb_resizeg(ptr, length) cb_resize((cbase*) ptr, length)

    #define cb_clearg(ptr) cb_clear((cbase*) ptr)
    #define cb_emptyg(ptr) cb_empty((cbase*) ptr)

    #define cb_sizeg(ptr) cb_size((cbase*) ptr)
    #define cb_cachesizeg(ptr) cb_cachesize((cbase*) ptr)
    #define cb_maxsizeg(ptr) cb_maxsize((cbase*) ptr)
    #define cb_countg(ptr) cb_count((cbase*) ptr)

    #define cb_beging(ptr) cb_begin((cbase*) ptr)
    #define cb_endg(ptr) cb_end((cbase*) ptr)
    #define cb_rbeging(ptr) cb_rbegin((cbase*) ptr)
    #define cb_rendg(ptr) cb_rend((cbase*) ptr)
#endif
