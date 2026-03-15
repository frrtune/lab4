#pragma once

#include "../core/FieldInfo.h"

typedef struct {
    double Re;
    double Im;
} Complex;
const FieldInfo* GetComplexFieldInfo();
void* ComplexClone(const void* current_complex);
void ComplexDestroy(void* current_complex);
void ComplexPrint(const void* current_complex);
void ComplexScan(void* current_complex);