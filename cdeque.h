#ifndef C_DEQUE
#define C_DEQUE
    #include <stdlib.h>
    #include <string.h>
    #include "cstack.h"

    typedef struct c_deque {
        ui32 trackfront, trackback;
        cstack* forwards, *backwards;
    } cdeque;

    #define cd_clear(ptr) ca_clearg(ptr->forwards); ca_clearg(ptr->backwards)
    #define cd_empty(ptr) ca_emptyg(ptr->forwards) && ca_emptyg(ptr->backwards)

    #define cd_size(ptr) ca_sizeg(ptr->forwards) + ca_sizeg(ptr->backwards)
    #define cd_cachesize(ptr) ca_cachesizeg(ptr->forwards) + ca_cachesizeg(ptr->backwards)
    #define cd_maxsize(ptr) ca_maxsizeg(ptr->forwards) + ca_maxsizeg(ptr->backwards)
    #define cd_count(ptr) ca_countg(ptr->forwards) + ca_countg(ptr->backwards)

    #define cd_allocg(ty, cachesz) cd_alloc(sizeof(ty), cachesz);
    cdeque* cd_alloc(ui32 typesz, ui32 cachsz);
    void cd_free(cdeque* cstr);
    type cd_top(cdeque* cdqu);
    type cd_bottom(cdeque* cdqu);
    void cd_pushback(cdeque* cdqu, type data);
    void cd_pushfront(cdeque* cdqu, type data);
    void cd_popback(cdeque* cdqu);
    void cd_popfront(cdeque* cdqu);
    void cd_insert(cdeque* cdqu, ui32 pos, type data);
    void cd_remove(cdeque* cdqu, ui32 pos);
#endif
