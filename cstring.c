#include "cstring.h"

void cstr_clearcache(cstring* cstr) {
    if (cstr->cachedstr == NULL)
        return;

    freeg(cstr->cachedstr);
};

cstring* cstr_alloc(char* str) {
    cstring* cstr = (cstring*)callocg(sizeof(cstring));
    cstr->string = NULL;
    cstr->cachedstr = NULL;
    cstr_append(cstr, str);
    return cstr;
};

void cstr_free(cstring* cstr) {
    if (cstr == NULL)
        return;

    if (cstr->cachedstr != NULL)
        freeg(cstr->cachedstr);

    cv_free(cstr->string);
    free(cstr);
};

void cstr_append(cstring* cstr, char* str) {
    if (str == NULL)
        return;

    if (cstr->string == NULL)
        cstr->string = cv_alloc(ui08, 8);

    for (ui32 i = 0; i < strlen(str); i++)
        cv_pushback(cstr->string, str + i);
};

void cstr_insert(cstring* cstr, ui32 pos, char* str) {
    if (str == NULL)
        return;
    
    if (cstr->string == NULL) {
        cstr_append(cstr, str);
        return;
    }

    for (int i = strlen(str) - 1; i >= 0; i--)
        cv_insert(cstr->string, pos, str + i);
};

void cstr_remove(cstring* cstr, ui32 pos) {
    if (cstr->string == NULL || pos < 0 || pos >= cstr->string->length)
        return;

    cstr_clearcache(cstr);
    cv_remove(cstr->string, pos);
};

void cstr_removec(cstring* cstr, ui32 pos, ui32 count) {
    if (cstr->string == NULL || pos < 0 || pos >= cstr->string->length)
        return;

    for(ui32 i = 0; (i < count) && ((pos + i) < cstr->string->length); i ++)
        cv_remove(cstr->string, pos);
};

void cstr_concat(cstring* cstrd, cstring* cstrs) {
    cstr_append(cstrd, cstrs->string->memory->pointer);
};

const ui08* cstr_getstring(cstring* cstr) {
    if (cstr->cachedstr != NULL && cstr->cachedstr->pointer != NULL)
        return cstr->cachedstr->pointer;
    if (cstr->string == NULL || cstr->string->length == 0)
        return NULL;

    memory* cachedstr = callocg(cstr->string->length + 1);
    memcpy(cachedstr->pointer, cstr->string->memory->pointer, cstr->string->length);
    cstr->cachedstr = cachedstr;
    return cachedstr->pointer;
};
