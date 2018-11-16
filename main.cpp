
#include <iostream>
#include "matrix.h"

int main() {
    
    matrix<int> A(4, 5);
    matrix<int> B(A);
    std::cout << A;
    std::cout<<"COPY CONSTRUCTOR TEST"<<std::endl; 
    
}
