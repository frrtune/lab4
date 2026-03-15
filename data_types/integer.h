#pragma once

#include "../core/FieldInfo.h"

const FieldInfo* GetIntFieldInfo();
void* IntClone(const void* current_int);
void IntDestroy(void* current_int);
void IntPrint(const void* current_int);
void IntScan(void* current_int);