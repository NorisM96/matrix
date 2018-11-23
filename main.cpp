#include "matrix.h"
#include <string>

void test_fondamental_methods() {

    //testing the constructor with 0 rows, 0 colunms filled with
    //default values
    Matrix<int> A(0,0);
    std::cout << "matrix of 0 elements\n" << A << std::endl;

    //generic matrices with default values
    Matrix<int> B(3,4);
    std::cout << "matrix (3,4) with default (int) values\n" << B << std::endl;

    //generic matrix with strings as elements
    Matrix<std::string> C(2,2);
    std::cout << "matrix with strings as elements (default values "")\n" << C << std::endl;

    //matrix with strings as elements and "prova" as default value
    Matrix<std::string> D(4,3, "prova");
    std::cout << "matrix with strings as elements and \"prova as default value\"\n" << D << std::endl;

    //copy constructor (results in a deep copy of the matrix)
    Matrix<std::string> E(D);
    std::cout << "copy constructor of the previous matrix\n" << E << std::endl;

    //assignment operator test
    Matrix<std::string> F = E;
    std::cout << "assignment operator\n" << F << std::endl;

    //test operator () 
    F(1,1) = "(1,1)";
    F(2,2) = "(2,2)";

    std::cout << "modified positions (1,1) and (2,2)\n" << F << std::endl;
}

void test_submatrix() {
    Matrix<int> A(4,5);

    for(int r = 0; r != 4; r++){
        for(int c = 0; c != 5; c++){
            A(r, c) = r + c;
        }
    }

    std::cout << "matrix with assigned values (we effetuate all the submatrices on this matrix)\n" << A << std::endl;

    Matrix<int> B = A.subMatrix(1,1,2,2);
    std::cout << "submatrix starting from (1,1) and ending in (2,2)\n" << B << std::endl;

    Matrix<int> C = A.subMatrix(0,0,3,4);
    std::cout << "submatrix starting form the begin of the matrix and ending to the end of the matrix\n" << C << std::endl;

    Matrix<int> D = A.subMatrix(0,1,1,3);
    std::cout << "submatrix starting from (0,1) and ending in (1,3)\n" << D << std::endl; 
}

void test_deepcopy(){
    Matrix<int> A(4,5,6),B(A);
    std::cout<< "Matrix copy costructor \n" << B << std::endl;
    Matrix<int> C(B.transpose()); //This thing shall not deep copy the object (RVO but it's theoretically move constructor)
    std::cout<< "Matrix copy costructor on transp method \n" << C << std::endl;
    std::cout<< "Chainging 1,1 element, the first two matrixies does not have to share memory, the last two does \n";
    C(1,1) = 0;
    Matrix<int> D = B;
    std::cout<< "Printing Matrixes \n" << A << std::endl << B << std::endl << C;    
    
}

int main() {

    test_fondamental_methods();

    test_submatrix();

    test_deepcopy();


}

