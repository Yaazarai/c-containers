#include "cstack.h"

#pragma region Top / Push / Pop
type cs_top(cstack* cstk) {
    return (type) (cstk->memory->pointer + ((cstk->length - 1) * cstk->typesz));
};

void cs_push(cstack* cstk, type data) {
    if (cstk->cached == 0)
        ca_cache((carray*) cstk);

    memcpy(cstk->memory->pointer + (cstk->length * cstk->typesz), data, cstk->typesz);

    cstk->length ++;
    cstk->cached --;
};

void cs_pop(cstack* cstk) {
    if (cstk->length > 0) {
        memset(cstk->memory->pointer + ((cstk->length - 1) * cstk->typesz), 0, cstk->typesz);

        cstk->length --;
        cstk->cached ++;
    }
};
#pragma endregion
