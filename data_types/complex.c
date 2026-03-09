#include "complex.h"
#include <stdlib.h>
#include <stdio.h>

const FieldInfo* GetComplexFieldInfo() {
    static FieldInfo* complex_info = NULL;
    if (!complex_info) {
        complex_info = (FieldInfo*)malloc(sizeof(FieldInfo));
        if (!complex_info) return NULL;
        complex_info->size = sizeof(Complex);
        complex_info->clone = ComplexClone;
        complex_info->destroy = ComplexDestroy;
    }
    return complex_info;
}

static void* ComplexClone(const void* current_complex) {
    if (!current_complex) return NULL;
    const Complex* current_complex_c = (const Complex*) current_complex;
    Complex* new_complex = (Complex*)malloc(sizeof(Complex));
    if (!new_complex) return NULL;
    new_complex->Re = current_complex_c->Re;
    new_complex->Im = current_complex_c->Im;
    return new_complex;
}

static void ComplexDestroy(void* current_complex) {
    free(current_complex);
}

static void ComplexPrint(const void* current_complex) {
    if (!current_complex) {
        puts("NULL");
        return;
    }
    const Complex* current_complex_c = (const Complex*)current_complex;
    if (current_complex_c->Im < 0) {
        printf("%lf-%lf*i", current_complex_c->Re, -current_complex_c->Im);
        return;
    }
    printf("%lf+%lf*i", current_complex_c->Re, current_complex_c->Im);
}

static void ComplexScan(void* current_complex) {
    if (!current_complex) {
        puts("NULL");
        return;
    }
    double re = 0.0, im = 0.0;
    scanf("%lf, %lf", &re, &im);
    Complex* current_complex_c = (Complex*)current_complex;
    current_complex_c->Re = re;
    current_complex_c->Im = im;
}