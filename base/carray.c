#include "carray.h"
#pragma region Alloc / Free
carray* ca_alloc(ui32 structsz, ui32 typesz, ui32 cachesz) {
    carray* cstk = (carray*) calloc(structsz, sizeof(ui08));
    cstk->typesz = typesz;
    cstk->cachesz = cachesz;
    cstk->length = 0;
    cstk->cached = cachesz;
    cstk->memory = callocg(cachesz * typesz);
    return cstk;
};

void ca_free(carray* cary) {
    if (cary == NULL)
        return;

    if (cary->memory != NULL)
        freeg(cary->memory);
    free(cary);
};
#pragma endregion


#pragma region Cache / Resize
cbool ca_cache(carray* cary) {
    if (cary == NULL || cary->cached != 0)
        return c_false;

    return ca_resize(cary, cary->length + cary->cachesz);
};

cbool ca_resize(carray* cary, ui32 length) {
    if (cary == NULL)
        return c_false;

    if (cary->memory == NULL) {
        cary->memory = callocg(length * cary->typesz);
        cary->length = 0;
        cary->cached = length;
    } else {
        reallocg(cary->memory, length * cary->typesz);

        if (cary->memory != NULL) {
            if (length < cary->length) {
                cary->length = length;
                cary->cached = 0;
            } else {
                cary->cached = length - cary->length;
            }
        }
    }

    return (cary->memory == NULL) ? c_false : c_true;
};
#pragma endregion


#pragma region Clear / Empty
void ca_clear(carray* cary) {
    if (cary == NULL)
        return;

    freeg(cary->memory);
};

cbool ca_empty(carray* cary) {
    return (cary != NULL && cary->memory != NULL && cary->length > 0) ? c_false : c_true;
};
#pragma endregion


#pragma region Byte (Size / Max Size)
ui32 ca_size(carray* cary) {
    if (cary->memory == NULL)
        return 0;
    return cary->length * cary->typesz;
};

ui32 ca_cachesize(carray* cary) {
    if (cary->memory == NULL)
        return 0;
    return cary->cached * cary->typesz;
};

ui32 ca_maxsize(carray* cary) {
    if (cary->memory == NULL)
        return 0;
    return (cary->length + cary->cachesz) * cary->typesz;
};

ui32 ca_count(carray* cary) {
    if (cary == NULL)
        return 0;
    return cary->length;
};
#pragma endregion


#pragma region Iterators
cbiter ca_begin(carray* cary) {
    cbiter iter;
    iter.iteration = cary->memory->pointer;
    iter.iterpos = cbbegin;
    iter.memory = cary;
    return iter;
};

cbiter ca_end(carray* cary) {
    cbiter iter;
    iter.iteration = cary->memory->pointer + (cary->length * cary->typesz);
    iter.iterpos = cbend;
    iter.memory = cary;
    return iter;
};

cbiter ca_rbegin(carray* cary) {
    cbiter iter;
    iter.iteration = cary->memory->pointer + (cary->length * cary->typesz) - cary->typesz;
    iter.iterpos = cbrbegin;
    iter.memory = cary;
    return iter;
};

cbiter ca_rend(carray* cary) {
    cbiter iter;
    iter.iteration = cary->memory->pointer - cary->typesz;
    iter.iterpos = cbrend;
    iter.memory = cary;
    return iter;
};
#pragma endregion
