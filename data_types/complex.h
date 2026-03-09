#pragma once

#include "../core/FieldInfo.h"

typedef struct {
    double Re;
    double Im;
} Complex;
const FieldInfo* GetComplexFieldInfo();
static void* ComplexClone(const void* current_complex);
static void ComplexDestroy(void* current_complex);
static void ComplexPrint(const void* current_complex);
static void ComplexScan(void* current_complex);