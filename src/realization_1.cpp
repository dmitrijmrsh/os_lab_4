#include "realization.hpp"

float Derivative(float A, float deltaX) {
    return (cosf(A + deltaX) - cosf(A)) / deltaX;
}

int* Sort(int* array) {
    int i, j, temp;

    for (i = 0; i < ArraySize - 1; ++i) {
        for (j = 0; j < ArraySize - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    
    return array;
}