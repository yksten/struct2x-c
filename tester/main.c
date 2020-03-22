#include <stdio.h>

#include "struct2x.h"


typedef struct data {
    bool bValue;
    char cValue;
    int nValue;
    float fValue;
    double dbValue;
    char* szValue;
}data;


field_iter data_fields[] = {
    { "bValue", ETYPE_BOOL, offsetof(struct data, bValue) },
    { "cValue", ETYPE_CHAR, offsetof(struct data, cValue) },
    { "nValue", ETYPE_INT, offsetof(struct data, nValue) },
    { "fValue", ETYPE_FLOAT, offsetof(struct data, fValue) },
    { "dbValue", ETYPE_DOUBLE, offsetof(struct data, dbValue) },
    { "szValue", ETYPE_STRING, offsetof(struct data, szValue) }
};



int main() {
    data ins = { true, 'f', 6, 7.7, 9.9};
    ins.szValue = (char*)malloc(4 + 1);
    memset(ins.szValue, 0, 5);
    memcpy(ins.szValue, "asdf", 4);

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