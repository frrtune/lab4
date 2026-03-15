#include "../containers/dynamic_array.h"
#include "../data_types/complex.h"
#include "../data_types/integer.h"
#include <stdio.h>
#include <assert.h>

void test_array_initialize() {
    DynamicArray* arr = array_initialize(10, GetComplexFieldInfo());
    assert(arr != NULL);
    assert(arr->capacity == 10);
    assert(arr->size == 0);
    assert(arr->info == GetComplexFieldInfo());
    array_destroy(arr);
    puts("SUCCESS");
}