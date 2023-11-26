#include "realization.hpp"

#include <iostream>
#include <stdlib.h>

void GuideToUse() {
    std::cout << "Hello user, there are list of commands you can use\n";
    std::cout << "1 - get first function result\n";
    std::cout << "2 - get second function result\n";
}

int main() {
    int cmd = 0;

    GuideToUse();
    while(std::cin >> cmd) {
        switch (cmd) {
        case 1:
            float A, deltaX;
            std::cin >> A >> deltaX;
            std::cout << "The value of Derivative is: " << Derivative(A, deltaX) << '\n';
            break;
        case 2:
            int* array;
            std::cin >> ArraySize;
            array = (int*)malloc(sizeof(int) * ArraySize);
            for (int i = 0; i < ArraySize; ++i) {
                std::cin >> array[i];
            }
            array = Sort(array);
            std::cout << "Sorted array: ";
            for (int i = 0; i < ArraySize; ++i) {
                std::cout << array[i] << ' ';
            }
            std::cout << '\n';
            free(array);
            array = nullptr;
            break;
        default:
            std::cout << "There are no commands with that id\n";
            break;
        }
    }

    return 0;
}