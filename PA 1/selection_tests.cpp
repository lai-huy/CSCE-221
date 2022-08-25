#include <iostream>
#include "selection.h"

using std::cout;

int main() {
    int* A = new int[7] {8, 6, 7, 5, 3, 0, 9};

    for (int i = 0; i < 9; ++i) {
        try {
            select(i, A, 7);
        } catch (const std::invalid_argument& err) {
            cout << "Error occured\n";
        }
    }

    try {
        select(0, A, 0);
    } catch (const std::invalid_argument& err) {
        cout << "Error occured\n";
    }

    delete[] A;
    A = nullptr;

    try {
        select(0, A, 0);
    } catch (const std::invalid_argument& err) {
        cout << "Error occured\n";
    }
    
    return 0;
}