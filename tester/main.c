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
    char* szValue;
    childStru child;
}data;


field_iter data_fields[] = {
    FIELDITER(data, bValue, ETYPE_BOOL, 0),
    FIELDITER(data, cValue, ETYPE_CHAR, 0),
    FIELDITER(data, nValue, ETYPE_INT, 0),
    FIELDITER(data, fValue, ETYPE_FLOAT, 0),
    FIELDITER(data, dbValue, ETYPE_DOUBLE, 0),
    FIELDITER(data, szValue, ETYPE_STRING, 0),
    FIELDITER(data, child, ETYPE_STRUCT, childStru_fields)
};


int main() {
    data ins = { true, 'f', 6, 7.7, 9.9};
    ins.szValue = (char*)malloc(4 + 1);
    memset(ins.szValue, 0, 5);
    memcpy(ins.szValue, "asdf", 4);
    ins.child.bValue = true;

    const char* sz = encode(&ins, data_fields, true);

    data ins2;
    ins2.szValue = (char*)malloc(4 + 1);
    memset(ins.szValue, 0, 5);

    decode(&ins2, data_fields, sz);

    free(ins2.szValue);

    free(sz);

    free(ins.szValue);
    return 0;
}