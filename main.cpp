
#include <iostream>
#include "matrix.h"

int main() {
    matrix<int> A(4, 5), B(A);
    std::cout << A;
    std::cout << "COPYYYYYYYY" << std::endl;
    std::cout << B;
    matrix<int> C(4,5,6);
    std::cout << "GUARDA MAMMA COL SEI DIOCANEEEEEEE" << std::endl;
    std::cout << C;
    matrix<int> D(C);
    std::cout << "COPYYYYYYYYO ANCHE QUELLA COL 6, DIO VENTISEI" << std::endl;
    std::cout << D;
}
