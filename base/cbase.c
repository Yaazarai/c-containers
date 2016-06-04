#include "cbase.h"

#pragma region Alloc / Free
cbase* cb_alloc(ui32 structsz, ui32 typesz, ui32 cachesz) {
    cbase* cstk = (cbase*) callocg(structsz);
    cstk->typesz = typesz;
    cstk->cachesz = cachesz;
    cstk->length = 0;
    cstk->cached = cachesz;
    cstk->memory = (ui08*)callocg(cachesz, typesz);
    return cstk;
};

void cb_free(cbase* cbse) {
    if (cbse == NULL)
        return;

    if (cbse->memory != NULL)
        free(cbse->memory);
    free(cbse);
};
#pragma endregion


#pragma region Cache / Resize
cbool cb_cache(cbase* cbse) {
    if (cbse == NULL || cbse->cached != 0)
        return c_false;

    return cb_resize(cbse, cbse->length + cbse->cachesz);
};

cbool cb_resize(cbase* cbse, ui32 length) {
    if (cbse == NULL)
        return c_false;

    if (cbse->memory == NULL) {
        cbse->memory = callocg(length * cbse->typesz, sizeof(ui08));
        cbse->length = 0;
        cbse->cached = length;
    } else {
        ui08* memory = reallocg(cbse->memory, length * cbse->typesz);

        if (memory != NULL) {
            cbse->memory = memory;

            if (length < cbse->length) {
                cbse->length = length;
                cbse->cached = 0;
            } else {
                cbse->cached = length - cbse->length;
            }
        }
    }

    return (cbse->memory == NULL) ? c_false : c_true;
};
#pragma endregion


#pragma region Clear / Empty
void cb_clear(cbase* cbse) {
    if (cbse == NULL)
        return;

    free(cbse->memory);
};

cbool cb_empty(cbase* cbse) {
    return (cbse != NULL && cbse->memory != NULL && cbse->length > 0) ? c_false : c_true;
};
#pragma endregion


#pragma region Byte (Size / Max Size)
ui32 cb_size(cbase* cbse) {
    if (cbse->memory == NULL)
        return 0;
    return cbse->length * cbse->typesz;
};

ui32 cb_cachesize(cbase* cbse) {
    if (cbse->memory == NULL)
        return 0;
    return cbse->cached * cbse->typesz;
};

ui32 cb_maxsize(cbase* cbse) {
    if (cbse->memory == NULL)
        return 0;
    return (cbse->length + cbse->cachesz) * cbse->typesz;
};

ui32 cb_count(cbase* cbse) {
    if (cbse == NULL)
        return 0;
    return cbse->length;
};
#pragma endregion


#pragma region Iterators
cbiter cb_begin(cbase* cbse) {
    cbiter iter;
    iter.iteration = cbse->memory;
    iter.iterpos = cbbegin;
    iter.memory = cbse;
    return iter;
};

cbiter cb_end(cbase* cbse) {
    cbiter iter;
    iter.iteration = cbse->memory + (cbse->length * cbse->typesz);
    iter.iterpos = cbend;
    iter.memory = cbse;
    return iter;
};

cbiter cb_rbegin(cbase* cbse) {
    cbiter iter;
    iter.iteration = cbse->memory + (cbse->length * cbse->typesz) + cbse->typesz;
    iter.iterpos = cbrbegin;
    iter.memory = cbse;
    return iter;
};

cbiter cb_rend(cbase* cbse) {
    cbiter iter;
    iter.iteration = cbse->memory - cbse->typesz;
    iter.iterpos = cbrend;
    iter.memory = cbse;
    return iter;
};
#pragma endregion
