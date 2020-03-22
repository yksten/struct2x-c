#include "struct2x.h"
#include "thirdParty/cJSON.h"


bool fieldTypeIsValid(unsigned int type) {
    switch (type) {
    case ETYPE_BOOL:
    case ETYPE_CHAR:
    case ETYPE_INT:
    case ETYPE_FLOAT:
    case ETYPE_DOUBLE:
    case ETYPE_STRING:
        return true;
    default:
        return false;
    }
}

void encodeBool(cJSON* obj, const char* sz, void* stru, int offset) {
    bool item = *(bool*)((int)stru + offset);
    if (item)
        cJSON_AddTrueToObject(obj, sz);
    else
        cJSON_AddFalseToObject(obj, sz);
}

void encodeChar(cJSON* obj, const char* sz, void* stru, int offset) {
    char item = *(char*)((int)stru + offset);
    cJSON_AddNumberToObject(obj, sz, item);
}

void encodeInt(cJSON* obj, const char* sz, void* stru, int offset) {
    int item = *(int*)((int)stru + offset);
    cJSON_AddNumberToObject(obj, sz, item);
}

void encodeFloat(cJSON* obj, const char* sz, void* stru, int offset) {
    float item = *(float*)((int)stru + offset);
    cJSON_AddNumberToObject(obj, sz, item);
}

void encodeDouble(cJSON* obj, const char* sz, void* stru, int offset) {
    double item = *(double*)((int)stru + offset);
    cJSON_AddNumberToObject(obj, sz, item);
}

void encodeString(cJSON* obj, const char* sz, void* stru, int offset) {
    char* item = *(char**)((int)stru + offset);
    cJSON_AddStringToObject(obj, sz, item);
}

typedef void(*encodeFunction)(cJSON*, const char*, void*, int);
const encodeFunction encodeArray[ETYPE_MAX] = {
    &encodeBool,
    &encodeChar,
    &encodeInt,
    &encodeFloat,
    &encodeDouble,
    &encodeString
};

const char* encode(void* stru, const field_iter* filelds, bool bUnformatted) {
    cJSON* root = cJSON_CreateObject();
    const field_iter* curFileld = filelds;
    do {
        unsigned type = curFileld->type;
        encodeArray[type](root, curFileld->szNmae, stru, curFileld->offset);
    } while (curFileld++ && fieldTypeIsValid(curFileld->type));
    char *out = 0;
    if (bUnformatted)
        out = cJSON_PrintUnformatted(root);
    else 
        out = cJSON_Print(root);
    return out;
}