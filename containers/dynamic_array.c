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

void array_remove_by_index(DynamicArray* arr, size_t index) {
    if (arr == NULL) return;
    if (index >= arr->size)
    {
        //дописать вывод ошибки
        return;
    }
    arr->info->destroy(arr->data[index]);
    for (size_t i = index; i < (arr->size - 1); i++)
    {
        arr->data[i] = arr->data[i + 1];
    }
    arr->data[arr->size-1] = NULL;
    arr->size--;
}