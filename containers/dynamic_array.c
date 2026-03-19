#include "dynamic_array.h"
#include <errno.h>
#include <stdio.h>

void show_errno(void)
{
    const char *err_info = "unknown error";
    switch (errno)
    {
        case EDOM:
            err_info = "domain error";
            break;
        case EILSEQ:
            err_info = "illegal sequence";
            break;
        case ERANGE:
            err_info = "pole or range error";
            break;
        case EINVAL:
            err_info = "invalid argument";
            break;
        case ENOMEM:
            err_info = "memory error";
            break;
        case 0:
            err_info = "no error";
    }
    fputs(err_info, stderr);
    puts(" occurred");
}

DynamicArray* array_initialize(size_t capacity, const FieldInfo* info) {
    if (!capacity || !info ) {
        errno = EINVAL;
        show_errno();
        return NULL;
    }
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    if (arr == NULL) {
        errno = ENOMEM;
        show_errno();
        return NULL;
    }
    arr->data = malloc(info->size * capacity);
    if (arr->data == NULL) {
        free(arr);
        errno = ENOMEM;
        show_errno();
        return NULL;
    }
    arr->size = 0;
    arr->capacity = capacity;
    arr->info = info;
    return arr;
}

void array_remove_by_index(DynamicArray* arr, size_t index) {
    if (arr == NULL) {
        errno = ENOMEM;
        show_errno();
        return;
    }
    if (index >= arr->size)
    {
        errno = ERANGE;
        show_errno();
        return;
    }
    size_t elem_size = arr->info->size;
    void* elem = (char*)arr->data + (elem_size * index);
    arr->info->destroy(elem);
    for (size_t i = index; i < (arr->size - 1); i++) {
        *((char*)arr->data + (elem_size * i)) = *((char*)arr->data + (elem_size * (i + 1)));
    }
    arr->size--;
}

void array_destroy(DynamicArray* arr) {
    if (arr == NULL) {
        errno = ENOMEM;
        show_errno();
        return;
    }
    while (arr->size > 0) {
        array_remove_by_index(arr, arr->size-1);
    }
    free(arr->data);
    free(arr);
}

void array_push_back(DynamicArray* arr, void* elem) {
    if (arr == NULL || elem == NULL) {
        errno = EINVAL;
        show_errno();
        return;
    }
    size_t elem_size = arr->info->size;
    if (arr->size == arr->capacity) {
        void* new_data = realloc(arr->data, 2 * arr->capacity * elem_size);
        if (new_data == NULL) {
            errno = ENOMEM;
            show_errno();
            return;
        }
        arr->data = new_data;
        arr->capacity = 2 * arr->capacity;
    }       
    for (size_t i = 0; i < elem_size; i++) {
        *((char*)arr->data + (elem_size * arr->size) + i) = *((char*)elem + i);
    }
    arr->size++;
}

void array_insert(DynamicArray* arr, void* elem, size_t index) {
    if (arr == NULL || elem == NULL || index > arr->size) {
        errno = EINVAL;
        show_errno();
        return;
    }
    size_t elem_size = arr->info->size;
    if (arr->size == arr->capacity) {
        void* new_data = realloc(arr->data, 2 * arr->capacity * elem_size);
        if (new_data == NULL) {
            errno = ENOMEM;
            show_errno();
            return;
        }
        arr->data = new_data;
        arr->capacity = 2 * arr->capacity;
    }
    for (size_t i = arr->size; i > index; i--) {
        for (size_t j = 0; j < elem_size; j++) {
            *((char*)arr->data + elem_size * i + j) = *((char*)arr->data + elem_size * (i - 1) + j);
        }
    }
    for (size_t i = 0; i < elem_size; i++) {
        *((char*)arr->data + elem_size * index + i) = *((char*)elem + i);
    }
    arr->size++;
}

const void* array_get(const DynamicArray* arr, size_t index) {
    if (arr == NULL || index >= arr->size) {
        errno = EINVAL;
        show_errno();
        return NULL;
    }
    return arr->data[index];
}

DynamicArray* array_map(const DynamicArray* arr, void* (*function)(const void*)) {
    if (arr == NULL || function == NULL) {
        errno = EINVAL;
        show_errno();
        return NULL;
    }
    DynamicArray* new_arr = array_initialize(arr->size, arr->info);
    if (new_arr == NULL) {
        errno = ENOMEM;
        show_errno();
        return NULL;
    }
    for (size_t i = 0; i < arr->size; i++) {
        void* new_elem = function(arr->data[i]);
        if (new_elem == NULL) {
            errno = ENOMEM;
            show_errno();
            array_destroy(new_arr);
            return NULL;
        }
        array_push_back(new_arr, new_elem);
    }
    return new_arr;
}

DynamicArray* array_where(const DynamicArray* arr, int (*function)(const void*)) {
    if (arr == NULL || function == NULL) {
        errno = EINVAL;
        show_errno();
        return NULL;
    }
    DynamicArray* new_arr = array_initialize(arr->size, arr->info);
    if (new_arr == NULL) {
        errno = ENOMEM;
        show_errno();
        return NULL;
    }
    for (size_t i = 0; i < arr->size; i++) {
        if (function(arr->data[i])) {
            void* copied_elem = arr->info->clone(arr->data[i]);
            array_push_back(new_arr, copied_elem);
        }
    }
    return new_arr;
}

DynamicArray* array_concatenate(DynamicArray* arr1, DynamicArray* arr2) {
    if (arr1 == NULL || arr2 == NULL || arr1->info != arr2->info) {
        errno = EINVAL;
        show_errno();
        return NULL;
    }
    DynamicArray* new_arr = array_initialize(arr1->size + arr2->size, arr1->info);
    if (new_arr == NULL) {
        errno = ENOMEM;
        show_errno();
        return NULL;
    }
    for (size_t i = 0; i < arr1->size; i++) {
        void* copied_elem = arr1->info->clone(arr1->data[i]);
        array_push_back(new_arr, copied_elem);
    }
    for (size_t i = 0; i < arr2->size; i++) {
        void* copied_elem = arr2->info->clone(arr2->data[i]);
        array_push_back(new_arr, copied_elem);
    }
    return new_arr;
}