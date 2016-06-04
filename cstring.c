#include "cstring.h"

void cstr_clearcache(cstring* csbd) {
    if (csbd->cachedstr == NULL)
        return;

    free(csbd->cachedstr);
};

cstring* cstr_alloc(char* str) {
    cstring* cstr = (cstring*)callocg(sizeof(cstring));
    cstr->string = NULL;
    cstr->cachedstr = NULL;
    cstr_append(cstr, str);
    return cstr;
};

void cstr_free(cstring* csbd) {
    if (csbd == NULL)
        return;

    if (csbd->cachedstr != NULL)
        free(csbd->cachedstr);

    cv_free(csbd->string);
    free(csbd);
};

void cstr_append(cstring* csbd, char* str) {
    if (str == NULL)
        return;

    if (csbd->string == NULL) {
        ui32 cachesz = 8;
        csbd->string = cv_alloc(ui08, cachesz);
    }

    for (ui32 i = 0; i < strlen(str); i++)
        cv_pushback(csbd->string, str + i);
};

void cstr_insert(cstring* csbd, ui32 pos, char* str) {
    if (str == NULL)
        return;
    
    if (csbd->string == NULL) {
        cstr_append(csbd, str);
        return;
    }

    for (int i = strlen(str) - 1; i >= 0; i--)
        cv_insert(csbd->string, pos, str + i);
};

void cstr_remove(cstring* csbd, ui32 pos) {
    if (csbd->string == NULL || pos < 0 || pos >= csbd->string->length)
        return;

    cstr_clearcache(csbd);
    cv_remove(csbd->string, pos);
};

void cstr_removec(cstring* csbd, ui32 pos, ui32 count) {
    if (csbd->string == NULL || pos < 0 || pos >= csbd->string->length)
        return;

    for(ui32 i = 0; (i < count) && ((pos + i) < csbd->string->length); i ++)
        cv_remove(csbd->string, pos);
};

const ui08* cstr_getstring(cstring* csbd) {
    if (csbd->cachedstr != NULL)
        return csbd->cachedstr;
    if (csbd->string == NULL || csbd->string->length == 0)
        return NULL;

    ui08* cachedstr = (ui08*) calloc(csbd->string->length + 1, 1);
    memcpy(cachedstr, csbd->string->memory, csbd->string->length);
    csbd->cachedstr = cachedstr;
    return cachedstr;
};
