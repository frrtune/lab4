#pragma once

#include "../core/FieldInfo.h"

typedef struct {
    size_t size;
    size_t capacity;
    void** data;
    const FieldInfo* info;
} DynamicArray;