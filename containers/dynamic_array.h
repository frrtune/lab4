#pragma once

#include "../core/FieldInfo.h"

typedef struct {
    size_t size;
    size_t capacity;
    void** data;
    const FieldInfo* info;
} DynamicArray;

DynamicArray* array_initialize(size_t capacity, const FieldInfo* info);