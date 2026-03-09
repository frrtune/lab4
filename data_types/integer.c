#include "integer.h"
#include <stdlib.h>

const FieldInfo* GetIntFieldInfo() {
    static FieldInfo* int_info = NULL;
    if (!int_info) {
        int_info = (FieldInfo*)malloc(sizeof(FieldInfo));
        if (!int_info) return NULL;
        int_info->size = sizeof(int);
        int_info->clone = IntClone;
        int_info->destroy = IntDestroy;
        int_info->print = IntPrint;
        int_info->scan = IntScan;
    }
    return int_info;
}

static void* IntClone(const void* current_int) {
    if (!current_int) return NULL;
    int* new_int = (int*)malloc(sizeof(int));
    if (!new_int) return NULL;
    *new_int = *(const int*) current_int;
    return new_int;
}

static void IntDestroy(void* current_int) {
    free(current_int);
}

static void IntPrint(const void* current_int) {
    if (!current_int) {
        puts("NULL");
        return;
    }
    printf("%d", *(const int*)current_int);
}

static void IntScan(void* current_int) {
    if (!current_int) {
        puts("NULL");
        return;
    }
    scanf("%d", (int*)current_int);
}