#ifndef C_QUEUE
#define C_QUEUE
    #include <stdlib.h>
    #include <string.h>
    #include "cvector.h"

    typedef struct c_string {
        cvector* string;
        ui08* cachedstr;
    } cstring;

    #define cstr_allocg() cstr_alloc(NULL)

    cstring* cstr_alloc(const char* str);
    void cstr_free(cstring* csbd);
    void cstr_append(cstring* csbd, const char* str);
    void cstr_insert(cstring* csbd, ui32 pos, const char* str);
    void cstr_remove(cstring* csbd, ui32 pos);
    void cstr_removec(cstring* csbd, ui32 pos, ui32 count);
    const ui08* cstr_getstring(cstring* csbd);
#endif
