#ifndef __STRUCT2X_H__
#define __STRUCT2X_H__
#include <stdbool.h>

#define offsetof(s,m) (size_t)&(((s *)0)->m)

#define FIELDITER(stru, field, type, iter) { #field, type, offsetof(struct stru, field), iter }

enum {
    ETYPE_BOOL,
    ETYPE_CHAR,
    ETYPE_INT,
    ETYPE_FLOAT,
    ETYPE_DOUBLE,
    ETYPE_STRUCT,
    ETYPE_MAX
};

bool fieldTypeIsValid(unsigned int type);

typedef struct field_iter field_iter_t;

typedef struct field_iter {
    const char* szName;
    int type;
    unsigned int offset;
    field_iter_t* childFieldIter;
}field_iter;


const char* encode(void* stru, const field_iter* filelds, bool bUnformatted);

bool decode(void* stru, const field_iter* filelds, const char* sz);

#endif