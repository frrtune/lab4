#include "dynamic_array.h"

DynamicArray* array_initialize(size_t capacity, const FieldInfo* info) {
    if (!capacity || !info ) {
        return NULL;
    }
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    if (arr == NULL) return NULL;
    arr->data = (void**)malloc(sizeof(void*) * capacity);
    if (arr->data == NULL) {
        free(arr);
        return NULL;
    }
    arr->size = 0;
    arr->capacity = capacity;
    arr->info = info;
    return arr;
}
