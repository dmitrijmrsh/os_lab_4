#include "realization.hpp"

float Derivative(float A, float deltaX) {
    return (cosf(A + deltaX) - cosf(A - deltaX)) / (2 * deltaX);
}

int* Sort(int* array) {
    int base, left, right, i, j;
    base = left = right = i = j = 0;
    std::stack<int> st;
    st.push(ArraySize - 1);
    st.push(0);
    while (!st.empty()) {
        left = st.top();
        st.pop();
        right = st.top();
        st.pop();
        if (((right - left) == 1) && (array[left] > array[right])) {
            std::swap(array[left], array[right]);
        } else {
            base = array[(left + right) / 2];
            i = left;
            j = right;
            while (i <= j) {
                while (base > array[i]) {
                    ++i;
                }
                while (base < array[j]) {
                    --j;
                }
                if (i <= j) {
                    std::swap(array[i], array[j]);
                    ++i;
                    --j;
                }
            }
        }
        if (left < j) {
            st.push(j);
            st.push(left);
        }
        if (right > i) {
            st.push(right);
            st.push(i);
        }
    }
    return array;
}