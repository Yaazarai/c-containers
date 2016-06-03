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
    
    typedef unsigned int ui32;
    typedef unsigned char ui08;
    typedef void* type;

    typedef enum cv_bool {
        c_false, c_true
    } cbool;

    typedef struct c_base {
        ui32 typesz, cachesz, length, cached;
        ui08* memory;
    } cbase;

    cbase* cb_alloc(ui32 strcsz, ui32 typesz, ui32 cachesz);
    void cb_free(cbase* cbse);
    cbool cb_cache(cbase* cbse);
    cbool cb_resize(cbase* cbse, ui32 length);

    #define cb_allocg(strc, ty, cachesz) (strc*) cb_alloc(sizeof(strc), sizeof(ty), cachesz)
    #define cb_freeg(ptr) cb_free((cbase*) ptr)
    #define cb_cacheg(ptr) cb_cache((cbase*) ptr)
    #define cb_resizeg(ptr, length) cb_resize((cbase*) ptr, length)
#endif
