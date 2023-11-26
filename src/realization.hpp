#pragma once

#include <math.h>
#include <stack>
#include <algorithm>

int ArraySize;

extern "C" {
    float Derivative(float A, float deltaX);
    int* Sort(int* array);
}