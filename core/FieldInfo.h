#pragma once
#include <stdlib.h>

typedef struct {
    size_t size;
    void* (*clone)(const void*);
    void (*destroy)(void*);
    void (*print)(const void*);
    void* (*scan)(void*);
} FieldInfo;
