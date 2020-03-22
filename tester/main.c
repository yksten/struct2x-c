#include <stdio.h>

#include "struct2x.h"

typedef struct childStru {
    bool bValue;
}childStru;

field_iter childStru_fields[] = {
    FIELDITER(childStru, bValue, ETYPE_BOOL, 0)
};

typedef struct data {
    bool bValue;
    char cValue;
    int nValue;
    float fValue;
    double dbValue;
    childStru child;
}data;


field_iter data_fields[] = {
    FIELDITER(data, bValue, ETYPE_BOOL, 0),
    FIELDITER(data, cValue, ETYPE_CHAR, 0),
    FIELDITER(data, nValue, ETYPE_INT, 0),
    FIELDITER(data, fValue, ETYPE_FLOAT, 0),
    FIELDITER(data, dbValue, ETYPE_DOUBLE, 0),
    FIELDITER(data, child, ETYPE_STRUCT, childStru_fields)
};


int main() {
    data ins = { true, 'f', 6, 7.7, 9.9, {true} };
    const char* sz = encode(&ins, data_fields, true);

    data ins2;
    decode(&ins2, data_fields, sz);

    free(sz);
    return 0;
}