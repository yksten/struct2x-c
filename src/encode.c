#include "struct2x.h"
#include "thirdParty/cJSON.h"


bool fieldTypeIsValid(unsigned int type) {
    switch (type) {
    case ETYPE_BOOL:
    case ETYPE_CHAR:
    case ETYPE_INT:
    case ETYPE_FLOAT:
    case ETYPE_DOUBLE:
    case ETYPE_STRUCT:
        return true;
    default:
        return false;
    }
}

void encodeObj(cJSON* obj, void* stru, const field_iter* filelds);

void encodeBool(cJSON* obj, void* stru, const field_iter* fileld) {
    bool item = *(bool*)((int)stru + fileld->offset);
    if (item)
        cJSON_AddTrueToObject(obj, fileld->szName);
    else
        cJSON_AddFalseToObject(obj, fileld->szName);
}

void encodeChar(cJSON* obj, void* stru, const field_iter* fileld) {
    char item = *(char*)((int)stru + fileld->offset);
    cJSON_AddNumberToObject(obj, fileld->szName, item);
}

void encodeInt(cJSON* obj, void* stru, const field_iter* fileld) {
    int item = *(int*)((int)stru + fileld->offset);
    cJSON_AddNumberToObject(obj, fileld->szName, item);
}

void encodeFloat(cJSON* obj, void* stru, const field_iter* fileld) {
    float item = *(float*)((int)stru + fileld->offset);
    cJSON_AddNumberToObject(obj, fileld->szName, item);
}

void encodeDouble(cJSON* obj, void* stru, const field_iter* fileld) {
    double item = *(double*)((int)stru + fileld->offset);
    cJSON_AddNumberToObject(obj, fileld->szName, item);
}

void encodeStruct(cJSON* obj, void* stru, const field_iter* fileld) {
    void* item = (void*)((int)stru + fileld->offset);
    cJSON* childObj = cJSON_CreateObject();
    cJSON_AddItemToObject(obj, fileld->szName, childObj);
    encodeObj(childObj, item, fileld->childFieldIter);
}

typedef void(*encodeFunction)(cJSON*, void*, const field_iter*);
const encodeFunction encodeArray[ETYPE_MAX] = {
    &encodeBool,
    &encodeChar,
    &encodeInt,
    &encodeFloat,
    &encodeDouble,
    &encodeStruct
};

void encodeObj(cJSON* obj, void* stru, const field_iter* filelds) {
    const field_iter* curFileld = filelds;
    do {
        unsigned type = curFileld->type;
        encodeArray[type](obj, stru, curFileld);
    } while (curFileld++ && fieldTypeIsValid(curFileld->type));
}

const char* encode(void* stru, const field_iter* filelds, bool bUnformatted) {
    cJSON* root = cJSON_CreateObject();
    encodeObj(root, stru, filelds);
    char *out = 0;
    if (bUnformatted)
        out = cJSON_PrintUnformatted(root);
    else 
        out = cJSON_Print(root);
    cJSON_Delete(root);
    return out;
}