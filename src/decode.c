#include "struct2x.h"
#include "thirdParty/cJSON.h"


void decodeObj(cJSON* obj, void* stru, const field_iter* filelds);

bool decodeBool(cJSON* obj, void* stru, const field_iter* fileld) {
    bool* value = (bool*)((int)stru + fileld->offset);
    cJSON* item = cJSON_GetObjectItem(obj, fileld->szName);
    if (item) {
        if (item->type == cJSON_False)
            *value = false;
        else
            *value = true;
    }
}

void decodeChar(cJSON* obj, void* stru, const field_iter* fileld) {
    char* value = (char*)((int)stru + fileld->offset);
    cJSON* item = cJSON_GetObjectItem(obj, fileld->szName);
    if (item) {
        *value = item->valueint;
    }
}

void decodeInt(cJSON* obj, void* stru, const field_iter* fileld) {
    int* value = (int*)((int)stru + fileld->offset);
    cJSON* item = cJSON_GetObjectItem(obj, fileld->szName);
    if (item) {
        *value = item->valueint;
    }
}

void decodeFloat(cJSON* obj, void* stru, const field_iter* fileld) {
    float* value = (float*)((int)stru + fileld->offset);
    cJSON* item = cJSON_GetObjectItem(obj, fileld->szName);
    if (item) {
        *value = item->valuedouble;
    }
}

void decodeDouble(cJSON* obj, void* stru, const field_iter* fileld) {
    double* value = (double*)((int)stru + fileld->offset);
    cJSON* item = cJSON_GetObjectItem(obj, fileld->szName);
    if (item) {
        *value = item->valuedouble;
    }
}

void decodeStruct(cJSON* obj, void* stru, const field_iter* fileld) {
    void* item = (void*)((int)stru + fileld->offset);
    cJSON* childObj = cJSON_GetObjectItem(obj, fileld->szName);
    decodeObj(childObj, item, fileld->childFieldIter);
}

typedef void(*decodeFunction)(cJSON*, void*, const field_iter*);
const decodeFunction decodeArray[ETYPE_MAX] = {
    &decodeBool,
    &decodeChar,
    &decodeInt,
    &decodeFloat,
    &decodeDouble,
    &decodeStruct
};

void decodeObj(cJSON* obj, void* stru, const field_iter* filelds) {
    const field_iter* curFileld = filelds;
    do {
        unsigned type = curFileld->type;
        decodeArray[type](obj, stru, curFileld);
    } while (curFileld++ && fieldTypeIsValid(curFileld->type));
}

bool decode(void* stru, const field_iter* filelds, const char* sz) {
    cJSON* root = cJSON_Parse(sz);
    decodeObj(root, stru, filelds);
    
    return true;
}