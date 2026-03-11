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

void array_destroy(DynamicArray* arr) {
    if (arr == NULL) return;
    while (arr->size > 0) {
        array_remove_by_index(arr, arr->size-1);
    }
    free(arr->data);
    free(arr);
}

void array_push_back(DynamicArray* arr, void* elem) {
    if (arr == NULL || elem == NULL) return;
    if (arr->size == arr->capacity) {
        void** new_data = realloc(arr->data, 2 * arr->capacity * sizeof(void*));
        if (new_data == NULL) return;
        arr->data = new_data;
        arr->capacity = 2 * arr->capacity;
    }
    arr->data[arr->size] = elem;
    arr->size++;
}

void array_insert(DynamicArray* arr, void* elem, size_t index) {
    if (arr == NULL || elem == NULL || index > arr->size) return;
    if (arr->size == arr->capacity) {
        void** new_data = realloc(arr->data, 2 * arr->capacity * sizeof(void*));
        if (new_data == NULL) return;
        arr->data = new_data;
        arr->capacity = 2 * arr->capacity;
    }
    for (size_t i = arr->size; i > index; i--) {
        arr->data[i] = arr->data[i-1];
    }
    arr->data[index] = elem;
    arr->size++;
}

const void* array_get(const DynamicArray* arr, size_t index) {
    if (arr == NULL || index >= arr->size) return;
    return arr->data[index];
}