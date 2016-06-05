#include "cdeque.h"

cdeque* cd_alloc(ui32 typesz, ui32 cachesz) {
    cdeque* cdqu = (cdeque*) calloc(sizeof(cdeque), sizeof(ui08));
    cdqu->forwards = (cstack*) ca_alloc(sizeof(cstack), typesz, cachesz);
    cdqu->backwards = (cstack*) ca_alloc(sizeof(cstack), typesz, cachesz);
    return cdqu;
};

void cd_free(cdeque* cdqu) {
    if (cdqu == NULL)
        return;

    cs_free(cdqu->forwards);
    cs_free(cdqu->backwards);
    free(cdqu);
};

type cd_top(cdeque* cdqu) {
    return cs_top(cdqu->forwards);
};

type cd_bottom(cdeque* cdqu) {
    return cs_top(cdqu->backwards);
};

void cd_pushback(cdeque* cdqu, type data) {
    if (cdqu->trackback == 0) {
        cs_push(cdqu->forwards, data);
    } else {
        memcpy(cdqu->backwards->memory->pointer + (cdqu->trackback * cdqu->backwards->typesz), data, cdqu->backwards->typesz);

        cdqu->trackback--;
        cdqu->backwards->length++;
        cdqu->backwards->cached--;
    }
};

void cd_pushfront(cdeque* cdqu, type data) {
    if (cdqu->trackfront == 0) {
        cs_push(cdqu->backwards, data);
    } else {
        memcpy(cdqu->forwards->memory->pointer + (cdqu->trackfront * cdqu->forwards->typesz), data, cdqu->forwards->typesz);

        cdqu->trackfront--;
        cdqu->forwards->length++;
        cdqu->forwards->cached--;
    }
};

void cd_popback(cdeque* cdqu) {
    if (cdqu->forwards->length > 0) {
        cs_pop(cdqu->forwards);
    } else {
        if (cdqu->backwards->length == 0)
            return;

        memset(cdqu->backwards->memory->pointer + (cdqu->trackback * cdqu->backwards->typesz), 0, cdqu->backwards->typesz);

        cdqu->trackback++;
        cdqu->backwards->length--;

        if (cdqu->backwards->length == 0)
            cdqu->trackback = 0;
    }
};

void cd_popfront(cdeque* cdqu) {
    if (cdqu->backwards->length > 0) {
        cs_pop(cdqu->backwards);
    } else {
        if (cdqu->forwards->length == 0)
            return;

        memset(cdqu->forwards->memory->pointer + (cdqu->trackfront * cdqu->forwards->typesz), 0, cdqu->forwards->typesz);

        cdqu->trackfront++;
        cdqu->forwards->length--;

        if (cdqu->forwards->length == 0)
            cdqu->trackfront = 0;
    }
};

void cs_insert(cstack* cstk, ui32 pos, type data) {
    if (cstk->cached == 0)
        ca_cache((carray*)cstk);

    if (cstk->length > 0)
        memmove(cstk->memory->pointer + ((pos + 1) * cstk->typesz), cstk->memory->pointer + (pos * cstk->typesz), (cstk->length - pos) * cstk->typesz);

    memcpy(cstk->memory->pointer + (pos * cstk->typesz), data, cstk->typesz);

    cstk->length++;
    cstk->cached--;
};

void cd_insert(cdeque* cdqu, ui32 pos, type data) {
    if (cdqu->trackback == 0 && cdqu->trackfront == 0) {
        if (pos < cdqu->backwards->length) {
            cs_insert(cdqu->backwards, cdqu->trackback + (cdqu->backwards->length - pos), data);
        } else {
            cs_insert(cdqu->forwards, cdqu->trackfront + pos - cdqu->backwards->length, data);
        }
    } else {
        if (cdqu->forwards->length == 0) {
            cs_insert(cdqu->backwards, cdqu->trackback + (cdqu->backwards->length - pos), data);
        }

        if (cdqu->backwards->length == 0) {
            cs_insert(cdqu->forwards, cdqu->trackfront + pos - cdqu->backwards->length, data);
        }
    }
};
