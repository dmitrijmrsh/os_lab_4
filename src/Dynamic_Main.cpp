#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <malloc.h>

typedef enum {
    FIRST,
    SECOND,
} Contract;

Contract current = FIRST;

const char* lib_name1 = "./lib_first.so";
const char* lib_name2 = "./lib_second.so";

float (*Derivative)(float A, float deltaX) = NULL;
int* (*Sort)(int* array) = NULL;
int* ArraySizePtr;

void* libHandle = NULL;

void LoadDynamicLib(Contract con) {
    if (con == FIRST) {
        libHandle = dlopen(lib_name1, RTLD_LAZY);
    } else if (con == SECOND) {
        libHandle = dlopen(lib_name2, RTLD_LAZY);
    } else {
        std::cerr << "Contract if error\n";
        exit(EXIT_FAILURE);
    }

    if (!libHandle) {
        std::cerr << dlerror();
        exit(EXIT_FAILURE);
    }
}

void LoadContract() {
    LoadDynamicLib(current);
    Derivative = (float (*)(float, float))dlsym(libHandle, "Derivative");
    Sort = (int* (*)(int*))dlsym(libHandle, "Sort");
    ArraySizePtr = (int*)dlsym(libHandle, "ArraySize");
 
    if (Derivative == NULL || Sort == NULL || ArraySizePtr == NULL) {
        std::cerr << "dlsym error\n";
    }
}

void UnloadDynamicLib() {
    dlclose(libHandle);
}

void ChangeContract() {
    UnloadDynamicLib();

    if (current == FIRST) {
        current = SECOND;
    } else {
        current = FIRST;
    }

    LoadContract();
}

void GuideToUse() {
    std::cout << "Hello user, there are list of commands you can use\n";
    std::cout << "0 - change current contract\n";
    std::cout << "1 - get first function result\n";
    std::cout << "2 - get second function result\n";
}

int main() {
    LoadContract();

    int cmd = 0;

    GuideToUse();
    while(std::cin >> cmd) {
        switch (cmd) {
            case 0:
               ChangeContract(); 
               if (current == FIRST) {
                std::cout << "Contract was changed to first\n";
               } else {
                std::cout << "Contract was changed to second\n";
               }
               break;
            case 1:
                float A, deltaX;
                std::cin >> A >> deltaX;
                std::cout << "The value of Derivative is: " << Derivative(A, deltaX) << '\n';
                break;
            case 2:
                int* array;
                scanf("%d", ArraySizePtr);
                array = (int*)malloc(*ArraySizePtr * sizeof(int));
                for (int i = 0; i < *ArraySizePtr; ++i) {
                    std::cin >> array[i];
                }
                array = Sort(array);
                std::cout << "Sorted array: ";
                for (int i = 0; i < *ArraySizePtr; ++i) {
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
    UnloadDynamicLib();


    return 0;
}