#include "cvector.h"

#pragma region Push Back / Push Front
void cv_pushback(cvector* cvec, type data) {
    if (cvec->cached == 0)
        ca_cache((carray*) cvec);

    memcpy(cvec->memory->pointer + (cvec->length * cvec->typesz), data, cvec->typesz);
    
    cvec->length ++;
    cvec->cached --;
};

void cv_pushfront(cvector* cvec, type data) {
    if (cvec->cached == 0)
        ca_cache((carray*) cvec);

    if (cvec->length > 0)
        memmove(cvec->memory->pointer + cvec->typesz, cvec->memory->pointer, cvec->length * cvec->typesz);
    
    memcpy(cvec->memory->pointer, data, cvec->typesz);

    cvec->length++;
    cvec->cached--;
};
#pragma endregion


#pragma region Insert / Remove
void cv_insert(cvector* cvec, ui32 pos, type data) {
    if (cvec->cached == 0)
        ca_cache((carray*) cvec);

    if (cvec->length > 0)
        memmove(cvec->memory->pointer + ((pos + 1) * cvec->typesz), cvec->memory->pointer + (pos * cvec->typesz), (cvec->length - pos) * cvec->typesz);

    memcpy(cvec->memory->pointer + (pos * cvec->typesz), data, cvec->typesz);

    cvec->length++;
    cvec->cached--;
};

void cv_remove(cvector* cvec, ui32 pos) {
    if (cvec->cached == 0)
        ca_cache((carray*) cvec);

    if (cvec->length > 0) {
        memmove(cvec->memory->pointer + (pos * cvec->typesz), cvec->memory->pointer + ((pos + 1) * cvec->typesz), (cvec->length - pos) * cvec->typesz);

        cvec->length--;
        cvec->cached++;
    }
};
#pragma endregion


#pragma region Set / Get
type cv_get(cvector* cvec, ui32 pos) {
    return (type) *(cvec->memory->pointer + (pos * cvec->typesz));
};

void cv_set(cvector* cvec, ui32 pos, type data) {
    memcpy(cvec->memory->pointer + (pos * cvec->typesz), data, cvec->typesz);
};
#pragma endregion


#pragma region Copy / Clone
void cv_copy(cvector* cvecs, cvector* cvecd) {
    if (cvecs == NULL || cvecd == NULL)
        return;

    free(cvecd);
    cvecd = (cvector*) ca_alloc(sizeof(cvecs), cvecs->typesz, cvecs->cachesz);
    memcpy(cvecd->memory->pointer, cvecs->memory->pointer, cvecs->length * cvecs->typesz);
};

cvector* cv_clone(cvector* cvecs) {
    if (cvecs == NULL)
        return NULL;

    cvector* cvecd = (cvector*) ca_alloc(sizeof(cvecs), cvecs->typesz, cvecs->cachesz);
    memcpy(cvecd->memory->pointer, cvecs->memory->pointer, cvecs->length * cvecs->typesz);
    return cvecd;
};
#pragma endregion


#pragma region Swap / Reverse
void cv_swap(cvector* cvec, ui32 posx, ui32 posy) {
    if (posx != posy && posx < cvec->length && posy < cvec->length) {
        ui08* b1 = cvec->memory->pointer + (posx * cvec->typesz),
            *b2 = cvec->memory->pointer + (posy * cvec->typesz);

        for (ui32 i = 0; i < cvec->typesz; i++) {
            *b1 ^= *b2 ^= *b1 ^= *b2;
            *b1++;
            *b2++;
        }
    }
};

void cv_reverse(cvector* cvec) {
    for (ui32 i = 0, sr = cvec->length, s = sr-- / 2; i < s; i++)
        cv_swap(cvec, i, sr - i);
};
#pragma endregion
