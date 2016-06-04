#ifndef C_QUEUE
#define C_QUEUE
    #include <stdlib.h>
    #include <string.h>
    #include "cvector.h"

    typedef struct c_string {
        cvector* string;
        memory* cachedstr;
    } cstring;

    #define cstr_allocg() cstr_alloc(NULL)

    cstring* cstr_alloc(char* str);
    void cstr_free(cstring* csbd);
    void cstr_append(cstring* csbd, char* str);
    void cstr_insert(cstring* csbd, ui32 pos, char* str);
    void cstr_remove(cstring* csbd, ui32 pos);
    void cstr_removec(cstring* csbd, ui32 pos, ui32 count);
    void cstr_concat(cstring* cstrd, cstring* cstrs);
    const ui08* cstr_getstring(cstring* csbd);
#endif
