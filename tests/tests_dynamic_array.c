#include "../containers/dynamic_array.h"
#include "../data_types/complex.h"
#include "../data_types/integer.h"
#include <stdio.h>
#include <assert.h>

void test_array_initialize() {
    puts("1. Initializing...");
    DynamicArray* arr = array_initialize(1, GetComplexFieldInfo());
    assert(arr != NULL);
    assert(arr->capacity == 1);
    assert(arr->size == 0);
    assert(arr->info == GetComplexFieldInfo());
    array_destroy(arr);
    puts("SUCCESS");
}

void test_array_push_back() {
    puts("2. Pushing back...");
    DynamicArray* arr = array_initialize(1, GetIntFieldInfo());
    size_t elem_size = arr->info->size;
    int elem1 = 1, elem2 = 2, elem3 = 3;
    array_push_back(arr, &elem1);
    assert(*(int*)arr->data == 1);
    assert(arr->size == 1);
    array_push_back(arr, &elem2);
    assert(*(int*)arr->data == 1);
    assert(*((int*)arr->data + elem_size) == 2);
    assert(arr->size == 2);
    assert(arr->capacity == 2);
    puts("SUCCESS");
}

void test_array_remove_by_index() {
    puts("3. Removing by index...");
    DynamicArray* arr = array_initialize(3, GetIntFieldInfo());
    size_t elem_size = arr->info->size;
    int* elem1 = malloc(sizeof(int));
    int* elem2 = malloc(sizeof(int));
    int* elem3 = malloc(sizeof(int));
    *elem1 = 1, *elem2 = 2, *elem3 = 3;
    array_push_back(arr, elem1);
    array_push_back(arr, elem2);
    array_push_back(arr, elem3);
    array_remove_by_index(arr, 1);
    assert(arr->size == 2);
    assert(*(int*)arr->data == 1);
    assert(*((int*)arr->data + elem_size) == 3);
    array_destroy(arr);
    puts("SUCCESS");
}

void test_array_insert() {
    puts("4. Inserting...");
    DynamicArray* arr = array_initialize(3, GetIntFieldInfo());
    size_t elem_size = arr->info->size;
    int* elem1 = malloc(sizeof(int));
    int* elem2 = malloc(sizeof(int));
    int* elem3 = malloc(sizeof(int));
    int* elem4 = malloc(sizeof(int));
    *elem1 = 1, *elem2 = 2, *elem3 = 3, *elem4 = 4;
    array_push_back(arr, elem1);
    array_push_back(arr, elem2);
    array_push_back(arr, elem3);
    array_insert(arr, elem4, 1);
    assert(*(int*)arr->data == 1);
    assert(*((int*)arr->data + elem_size) == 4);
    assert(*((int*)arr->data + elem_size * 2) == 2);
    assert(*((int*)arr->data + elem_size * 3) == 3);
    array_destroy(arr);
    puts("SUCCESS");
}

void test_array_get() {
    puts("5. Getting an element...");
    DynamicArray* arr = array_initialize(2, GetIntFieldInfo());
    int* elem1 = malloc(sizeof(int));
    int* elem2 = malloc(sizeof(int));
    *elem1 = 1, *elem2 = 2;
    array_push_back(arr, elem1);
    array_push_back(arr, elem2);
    int* got_elem1 = (int*)array_get(arr, 0);
    int* got_elem2 = (int*)array_get(arr, 1);
    assert(*got_elem1 == 1);
    assert(*got_elem2 == 2);
    assert(array_get(arr, 2) == NULL);
    array_destroy(arr);
    puts("SUCCESS");
}

void test_complex() {
    puts("6. Testing complex numbers...");
    DynamicArray* arr = array_initialize(2, GetComplexFieldInfo());
    Complex* elem1 = (Complex*)malloc(sizeof(Complex));
    Complex* elem2 = (Complex*)malloc(sizeof(Complex));
    elem1->Re = 1.0;
    elem1->Im = 0.0;
    elem2->Re = -3.0;
    elem2->Im = 2.0;
    array_push_back(arr, elem1);
    array_push_back(arr, elem2);
    Complex* got_elem1 = (Complex*)array_get(arr, 0);
    Complex* got_elem2 = (Complex*)array_get(arr, 1);
    assert(got_elem1->Re == 1.0);
    assert(got_elem1->Im == 0.0);
    assert(got_elem2->Re == -3.0);
    assert(got_elem2->Im == 2.0);
    array_remove_by_index(arr, 0);
    assert(arr->size == 1);
    Complex* got_elem = (Complex*)array_get(arr, 0);
    assert(got_elem->Re == -3.0);
    assert(got_elem->Im == 2.0);
    array_destroy(arr);
    puts("SUCCESS");
}

void* double_int(const void* elem) {
    int* result = malloc(sizeof(int));
    *result = *(const int*)elem * 2;
    return result;
}

void test_map() {
    puts("7. Mapping...");
    DynamicArray* arr = array_initialize(4, GetIntFieldInfo());
    size_t elem_size = arr->info->size;
    int* elem1 = malloc(sizeof(int));
    int* elem2 = malloc(sizeof(int));
    int* elem3 = malloc(sizeof(int));
    int* elem4 = malloc(sizeof(int));
    *elem1 = 1, *elem2 = 2, *elem3 = 3, *elem4 = 4;
    array_push_back(arr, elem1);
    array_push_back(arr, elem2);
    array_push_back(arr, elem3);
    array_push_back(arr, elem4);
    DynamicArray* mapped_array = array_map(arr, double_int);
    assert(mapped_array->size == 4);
    assert(*((int*)arr->data) == 2);
    assert(*((int*)arr->data + elem_size) == 4);
    assert(*((int*)arr->data + elem_size * 2) == 6);
    assert(*((int*)arr->data + elem_size * 3) == 8);
    array_destroy(arr);
    array_destroy(mapped_array);
    puts("SUCCESS");
}

int is_positive(const void* elem) {
    return *(const int*)elem > 0;
}

void test_array_where() {
    puts("8. Producing where...");
    DynamicArray* arr = array_initialize(4, GetIntFieldInfo());
    size_t elem_size = arr->info->size;
    int* elem1 = malloc(sizeof(int));
    int* elem2 = malloc(sizeof(int));
    int* elem3 = malloc(sizeof(int));
    int* elem4 = malloc(sizeof(int));
    *elem1 = -1, *elem2 = 0, *elem3 = 1, *elem4 = 2;
    array_push_back(arr, elem1);
    array_push_back(arr, elem2);
    array_push_back(arr, elem3);
    array_push_back(arr, elem4);
    DynamicArray* whered_array = array_where(arr, is_positive);
    assert(whered_array->size == 2);
    puts("size is ok");
    assert(*(int*)arr->data == 1);
    assert(*((int*)arr->data + elem_size) == 2);
    array_destroy(whered_array);
    array_destroy(arr);
    puts("SUCCESS");
}

void test_array_concatenate() {
    puts("9. Concatenating...");
    DynamicArray* arr1 = array_initialize(2, GetIntFieldInfo());
    DynamicArray* arr2 = array_initialize(1, GetIntFieldInfo());
    size_t elem_size = arr1->info->size;
    int* elem1 = malloc(sizeof(int));
    int* elem2 = malloc(sizeof(int));
    int* elem3 = malloc(sizeof(int));
    *elem1 = -1, *elem2 = 0, *elem3 = 1;
    array_push_back(arr1, elem1);
    array_push_back(arr1, elem2);
    array_push_back(arr2, elem3);
    DynamicArray* concatenated_array = array_concatenate(arr1, arr2);
    assert(concatenated_array->size == 3);
    assert(*((int*)concatenated_array->data) == -1);
    assert(*((int*)concatenated_array->data + elem_size) == 0);
    assert(*((int*)concatenated_array->data + elem_size * 2) == 1);
    array_destroy(concatenated_array);
    array_destroy(arr1);
    array_destroy(arr2);
    puts("SUCCESS");
}

int main() {
    test_array_initialize();
    test_array_push_back();
    test_array_remove_by_index();
    test_array_insert();
    test_array_get();
    test_complex();
    test_map();
    test_array_where();
    test_array_concatenate();
    puts("DONE");
    return 0;
}