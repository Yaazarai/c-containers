#include "cbase.h"

#pragma region Alloc / Free
cbase* cb_alloc(ui32 structsz, ui32 typesz, ui32 cachesz) {
    cbase* cstk = (cbase*) malloc(structsz);
    cstk->typesz = typesz;
    cstk->cachesz = cachesz;
    cstk->length = 0;
    cstk->cached = cachesz;
    cstk->memory = (ui08*)calloc(cachesz, typesz);
    return cstk;
};

void cb_free(cbase* cstk) {
    if (cstk == NULL)
        return;

    free(cstk->memory);
    free(cstk);
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
        cbse->memory = calloc(length * cbse->typesz, sizeof(ui08));
        cbse->length = 0;
        cbse->cached = length;
    }
    else {
        ui08* memory = realloc(cbse->memory, length * cbse->typesz);

        if (memory != NULL) {
            cbse->memory = memory;

            if (length < cbse->length) {
                cbse->length = length;
                cbse->cached = 0;
            }
            else {
                cbse->cached = length - cbse->length;
            }
        }
    }

    return (cbse->memory == NULL) ? c_false : c_true;
};
#pragma endregion
