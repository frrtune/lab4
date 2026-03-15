#include "../containers/dynamic_array.h"
#include "../data_types/complex.h"
#include "../data_types/integer.h"
#include <stdio.h>
#include <assert.h>

void test_array_initialize() {
    DynamicArray* arr = array_initialize(1, GetComplexFieldInfo());
    assert(arr != NULL);
    assert(arr->capacity == 1);
    assert(arr->size == 0);
    assert(arr->info == GetComplexFieldInfo());
    array_destroy(arr);
    puts("SUCCESS");
}

void test_array_push_back() {
    DynamicArray* arr = array_initialize(1, GetIntFieldInfo());
    int elem1 = 1, elem2 = 2, elem3 = 3;
    array_push_back(arr, &elem1);
    assert(*(int*)arr->data[0] == 1);
    assert(arr->size == 1);
    array_push_back(arr, &elem2);
    assert(*(int*)arr->data[0] == 1);
    assert(*(int*)arr->data[1] == 2);
    assert(arr->size == 2);
    assert(arr->capacity == 2);
    puts("SUCCESS");
}

int main() {
    test_array_initialize();
    test_array_push_back();
    return 0;
}