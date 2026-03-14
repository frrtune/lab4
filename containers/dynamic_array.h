#pragma once

#include "../core/FieldInfo.h"

typedef struct {
    size_t size;
    size_t capacity;
    void** data;
    const FieldInfo* info;
} DynamicArray;

DynamicArray* array_initialize(size_t capacity, const FieldInfo* info);
void array_remove_by_index(DynamicArray* arr, size_t index);
void array_destroy(DynamicArray* arr);
void array_push_back(DynamicArray* arr, void* elem);
void array_insert(DynamicArray* arr, void* elem, size_t index);
const void* array_get(const DynamicArray* arr, size_t index);
DynamicArray* array_map(const DynamicArray* arr, void* (*function)(const void*));