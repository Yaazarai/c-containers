#include "cvector.h"

#pragma region Push Back / Push Front
void cvpushback(cvector* cvec, type data) {
    if (cvec->cached <= 0)
        cvcache(cvec);

    memcpy(cvec->memory + (cvec->length * cvec->typesz), data, cvec->typesz);
    
    cvec->length ++;
    cvec->cached --;
};

void cvpushfront(cvector* cvec, type data) {
    if (cvec->cached <= 0)
        cvcache(cvec);

    if (cvec->length > 0)
        memmove(cvec->memory + cvec->typesz, cvec->memory, cvec->length * cvec->typesz);
    
    memcpy(cvec->memory, data, cvec->typesz);

    cvec->length++;
    cvec->cached--;
};
#pragma endregion


#pragma region Insert / Remove
void cvinsert(cvector* cvec, ui32 pos, type data) {
    if (cvec->cached <= 0)
        cvcache(cvec);

    if (cvec->length > 0)
        memmove(cvec->memory + ((pos + 1) * cvec->typesz), cvec->memory + (pos * cvec->typesz), (cvec->length - pos) * cvec->typesz);

    memcpy(cvec->memory + (pos * cvec->typesz), data, cvec->typesz);

    cvec->length++;
    cvec->cached--;
};

void cvremove(cvector* cvec, ui32 pos) {
    if (cvec->cached <= 0)
        cvcache(cvec);

    if (cvec->length > 0) {
        memmove(cvec->memory + (pos * cvec->typesz), cvec->memory + ((pos + 1) * cvec->typesz), (cvec->length - pos) * cvec->typesz);

        cvec->length--;
        cvec->cached++;
    }
};
#pragma endregion


#pragma region Set / Get
type cvget(cvector* cvec, ui32 pos) {
    return (type) *(cvec->memory + (pos * cvec->typesz));
};

void cvset(cvector* cvec, ui32 pos, type data) {
    memcpy(cvec->memory + (pos * cvec->typesz), data, cvec->typesz);
};
#pragma endregion


#pragma region Copy / Clone
void cvcopy(cvector* cvecs, cvector* cvecd) {
    if (cvecs == NULL || cvecd == NULL)
        return;

    free(cvecd);
    cvecd = cvalloc(cvecs->typesz, cvecs->cachesz);
    memcpy(cvecd->memory, cvecs->memory, cvecs->length * cvecs->typesz);
};

cvector* cvclone(cvector* cvecs) {
    if (cvecs == NULL)
        return NULL;

    cvector* cvecd = cvalloc(cvecs->typesz, cvecs->cachesz);
    memcpy(cvecd->memory, cvecs->memory, cvecs->length * cvecs->typesz);
    return cvecd;
};
#pragma endregion


#pragma region Swap / Reverse
void cvswap(cvector* cvec, ui32 posx, ui32 posy) {
    if (posx != posy && posx < cvec->length && posy < cvec->length) {
        ui08* b1 = cvec->memory + (posx * cvec->typesz),
            *b2 = cvec->memory + (posy * cvec->typesz);

        for (ui32 i = 0; i < cvec->typesz; i++) {
            *b1 ^= *b2 ^= *b1 ^= *b2;
            *b1++;
            *b2++;
        }
    }
};

void cvreverse(cvector* cvec) {
    for (ui32 i = 0, sr = cvec->length, s = sr-- / 2; i < s; i++)
        cvswap(cvec, i, sr - i);
};
#pragma endregion


#pragma region Clear / Empty
void cvclear(cvector* cvec) {
    if (cvec == NULL)
        return;

    free(cvec->memory);
};

cbool cvempty(cvector* cvec) {
    return (cvec != NULL && cvec->memory != NULL && cvec->length > 0) ? c_false : c_true;
};
#pragma endregion


#pragma region Iterators
cviter cvbegin(cvector* cvec) {
    cviter iter;
    iter.iteration = cvec->memory;
    iter.iterpos = cv_begin;
    iter.memory = cvec;
    return iter;
};

cviter cvend(cvector* cvec) {
    cviter iter;
    iter.iteration = cvec->memory + (cvec->length * cvec->typesz);
    iter.iterpos = cv_end;
    iter.memory = cvec;
    return iter;
};

cviter cvrbegin(cvector* cvec) {
    cviter iter;
    iter.iteration = cvec->memory + (cvec->length * cvec->typesz) + cvec->typesz;
    iter.iterpos = cv_rbegin;
    iter.memory = cvec;
    return iter;
};

cviter cvrend(cvector* cvec) {
    cviter iter;
    iter.iteration = cvec->memory - cvec->typesz;
    iter.iterpos = cv_rend;
    iter.memory = cvec;
    return iter;
};
#pragma endregion


#pragma region Byte (Size / Max Size)
ui32 cvsize(cvector* cvec) {
    if (cvec->memory == NULL)
        return 0;
    return cvec->length * cvec->typesz;
};

ui32 cvcachesize(cvector* cvec) {
    if (cvec->memory == NULL)
        return 0;
    return cvec->cached * cvec->typesz;
};

ui32 cvmaxsize(cvector* cvec) {
    if (cvec->memory == NULL)
        return 0;
    return (cvec->length + cvec->cachesz) * cvec->typesz;
};

ui32 cvcount(cvector* cvec) {
    if (cvec == NULL)
        return 0;
    return cvec->length;
};
#pragma endregion
