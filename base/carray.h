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

#ifndef C_ARRAY
#define C_ARRAY
    #include <stdlib.h>
    #include <string.h>
    #include "memory.h"
    
    typedef unsigned int ui32;
    typedef unsigned char ui08;
    typedef void* type;

    typedef enum c_bool {
        c_false, c_true
    } cbool;

    typedef struct c_array {
        ui32 typesz, cachesz, length, cached;
        memory* memory;
    } carray;

    typedef enum ca_iterpos {
        cbbegin, cbend, cbrbegin, cbrend
    } cbiterpos;

    typedef struct ca_iter {
        void* memory;
        ui08* iteration;
        enum cbiterpos iterpos;
    } cbiter;

    carray* ca_alloc(ui32 strcsz, ui32 typesz, ui32 cachesz);
    void ca_free(carray* cbse);
    cbool ca_cache(carray* cbse);
    cbool ca_resize(carray* cbse, ui32 length);

    void ca_clear(carray* cbse);
    cbool ca_empty(carray* cbse);

    ui32 ca_size(carray* cbse);
    ui32 ca_cachesize(carray* cbse);
    ui32 ca_maxsize(carray* cbse);
    ui32 ca_count(carray* cbse);

    cbiter ca_begin(carray* cbse);
    cbiter ca_end(carray* cbse);
    cbiter ca_rbegin(carray* cbse);
    cbiter ca_rend(carray* cbse);

    #define ca_allocg(strc, ty, cachesz) (strc*) ca_alloc(sizeof(strc), sizeof(ty), cachesz)
    #define ca_freeg(ptr) ca_free((carray*) ptr)
    #define ca_cacheg(ptr) ca_cache((carray*) ptr)
    #define ca_resizeg(ptr, length) ca_resize((carray*) ptr, length)

    #define ca_clearg(ptr) ca_clear((carray*) ptr)
    #define ca_emptyg(ptr) ca_empty((carray*) ptr)

    #define ca_sizeg(ptr) ca_size((carray*) ptr)
    #define ca_cachesizeg(ptr) ca_cachesize((carray*) ptr)
    #define ca_maxsizeg(ptr) ca_maxsize((carray*) ptr)
    #define ca_countg(ptr) ca_count((carray*) ptr)

    #define ca_beging(ptr) ca_begin((carray*) ptr)
    #define ca_endg(ptr) ca_end((carray*) ptr)
    #define ca_rbeging(ptr) ca_rbegin((carray*) ptr)
    #define ca_rendg(ptr) ca_rend((carray*) ptr)
#endif
