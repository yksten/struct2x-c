#include "struct2x.h"
#include "thirdParty/cJSON.h"


bool decodeBool(cJSON* obj, const char* sz, void* stru, int offset) {
    bool* value = (bool*)((int)stru + offset);
    cJSON* item = cJSON_GetObjectItem(obj, sz);
    if (item) {
        if (item->type == cJSON_False)
            *value = false;
        else
            *value = true;
    }
}

void decodeChar(cJSON* obj, const char* sz, void* stru, int offset) {
    char* value = (char*)((int)stru + offset);
    cJSON* item = cJSON_GetObjectItem(obj, sz);
    if (item) {
        *value = item->valueint;
    }
}

void decodeInt(cJSON* obj, const char* sz, void* stru, int offset) {
    int* value = (int*)((int)stru + offset);
    cJSON* item = cJSON_GetObjectItem(obj, sz);
    if (item) {
        *value = item->valueint;
    }
}

void decodeFloat(cJSON* obj, const char* sz, void* stru, int offset) {
    float* value = (float*)((int)stru + offset);
    cJSON* item = cJSON_GetObjectItem(obj, sz);
    if (item) {
        *value = item->valuedouble;
    }
}

void decodeDouble(cJSON* obj, const char* sz, void* stru, int offset) {
    double* value = (double*)((int)stru + offset);
    cJSON* item = cJSON_GetObjectItem(obj, sz);
    if (item) {
        *value = item->valuedouble;
    }
}

void decodeString(cJSON* obj, const char* sz, void* stru, int offset) {
    char** value = (char**)((int)stru + offset);
    cJSON* item = cJSON_GetObjectItem(obj, sz);
    if (item) {
        *value = item->valuestring;
    }
}

typedef void(*decodeFunction)(cJSON*, const char*, void*, int);
const decodeFunction decodeArray[ETYPE_MAX] = {
    &decodeBool,
    &decodeChar,
    &decodeInt,
    &decodeFloat,
    &decodeDouble,
    &decodeString
};

bool decode(void* stru, const field_iter* filelds, const char* sz) {
    cJSON* root = cJSON_Parse(sz);
    const field_iter* curFileld = filelds;
    do {
        unsigned type = curFileld->type;
        decodeArray[type](root, curFileld->szNmae, stru, curFileld->offset);
    } while (curFileld++ && fieldTypeIsValid(curFileld->type));
    
    return true;
}