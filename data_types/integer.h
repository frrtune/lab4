#pragma once

#include "../core/FieldInfo.h"

const FieldInfo* GetIntFieldInfo();
static void* IntClone(const void* current_int);
static void IntDestroy(void* current_int);
static void IntPrint(const void* current_int);
static void IntScan(void* current_int);