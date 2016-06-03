#include "cstack.h"

#pragma region Top / Push / Pop
type cs_top(cstack* cstk) {
    return (type) *(cstk->memory + ((cstk->length - 1) * cstk->typesz));
};

void cs_push(cstack* cstk, type data) {
    if (cstk->cached <= 0)
        cb_cacheg(cstk);

    memcpy(cstk->memory + (cstk->length * cstk->typesz), data, cstk->typesz);
    
    cstk->length ++;
    cstk->cached --;
};

void cs_pop(cstack* cstk) {
    if (cstk->length > 0) {
        cstk->length --;
        cstk->cached ++;
    }
};
#pragma endregion


#pragma region Swap / Empty
void cs_swap(cstack* cstks, cstack* cstkd) {
    if (cstks == NULL || cstkd == NULL)
        return;

    cstack* temp = cstks;
    cstks = cstkd;
    cstkd = temp;
};

cbool cs_empty(cstack* cstk) {
    return (cstk == NULL || cstk->memory == NULL || cstk->length == 0);
};
#pragma endregion


#pragma region Byte (Size / Max Size)
ui32 cs_size(cstack* cstk) {
    if (cstk->memory == NULL)
        return 0;
    return cstk->length * cstk->typesz;
};

ui32 cs_cachesize(cstack* cstk) {
    if (cstk->memory == NULL)
        return 0;
    return cstk->cached * cstk->typesz;
};

ui32 cs_maxsize(cstack* cstk) {
    if (cstk->memory == NULL)
        return 0;
    return (cstk->length + cstk->cachesz) * cstk->typesz;
};

ui32 cs_count(cstack* cstk) {
    if (cstk == NULL)
        return 0;
    return cstk->length;
};
#pragma endregion
