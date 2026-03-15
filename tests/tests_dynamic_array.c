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

void test_array_remove_by_index() {
    DynamicArray* arr = array_initialize(3, GetIntFieldInfo());
    int* elem1 = malloc(sizeof(int));
    int* elem2 = malloc(sizeof(int));
    int* elem3 = malloc(sizeof(int));
    *elem1 = 1, *elem2 = 2, *elem3 = 3;
    array_push_back(arr, elem1);
    array_push_back(arr, elem2);
    array_push_back(arr, elem3);
    array_remove_by_index(arr, 1);
    assert(arr->size == 2);
    assert(*(int*)arr->data[0] == 1);
    assert(*(int*)arr->data[1] == 3);
    array_destroy(arr);
    puts("SUCCESS");
}

void test_array_insert() {
    DynamicArray* arr = array_initialize(3, GetIntFieldInfo());
    int* elem1 = malloc(sizeof(int));
    int* elem2 = malloc(sizeof(int));
    int* elem3 = malloc(sizeof(int));
    int* elem4 = malloc(sizeof(int));
    *elem1 = 1, *elem2 = 2, *elem3 = 3, *elem4 = 4;
    array_push_back(arr, elem1);
    array_push_back(arr, elem2);
    array_push_back(arr, elem3);
    array_insert(arr, elem4, 1);
    assert(*(int*)arr->data[0] == 1);
    assert(*(int*)arr->data[1] == 4);
    assert(*(int*)arr->data[2] == 2);
    assert(*(int*)arr->data[3] == 3);
    array_destroy(arr);
    puts("SUCCESS");
}

void test_array_get() {
    DynamicArray* arr = array_initialize(2, GetIntFieldInfo());
    int* elem1 = malloc(sizeof(int));
    int* elem2 = malloc(sizeof(int));
    *elem1 = 1, *elem2 = 2;
    array_push_back(arr, elem1);
    array_push_back(arr, elem2);
    int* got_elem1 = (int*)array_get(arr, 0);
    int* got_elem2 = (int*)array_get(arr, 1);
    assert(*got_elem1 == 1);
    assert(*got_elem1 == 2);
    assert(array_get(arr, 2) == NULL);
    array_destroy(arr);
    puts("SUCCESS");
}

void test_complex() {
    DynamicArray* arr = array_initialize(2, GetComplexFieldInfo());
    Complex elem1 = {1.0, 0.0};
    Complex elem2 = {-3.0, 2.0};
    array_push_back(arr, &elem1);
    array_push_back(arr, &elem2);
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
    assert(got_elem->Re == 2.0);
    array_destroy(arr);
    puts("SUCCESS");
}

int* double_int(const int* elem) {
    int* result = malloc(sizeof(int));
    *result = *(const int*)elem * 2;
    return result;
}

void test_map() {
    DynamicArray* arr = array_initialize(4, GetIntFieldInfo());
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
    assert(*(int*)arr->data[0] == 2);
    assert(*(int*)arr->data[1] == 4);
    assert(*(int*)arr->data[2] == 6);
    assert(*(int*)arr->data[3] == 8);
    array_destroy(arr);
    puts("SUCCESS");
}

int main() {
    test_array_initialize();
    test_array_push_back();
    test_array_remove_by_index();
    test_array_insert();
    test_array_get();
    return 0;
}