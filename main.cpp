#include "matrix.h"
#include <string>

void test_fondamental_methods() {
    std::cout << "***TEST FONDAMENTAL METHODS***\n\n";

    //testing the constructor with 0 rows, 0 colunms filled with
    //default values
    matrix<int> A(0,0);
    std::cout << "matrix of 0 elements\n" << A << std::endl;

    //generic matrices with default values
    matrix<int> B(3,4);
    std::cout << "matrix (3,4) with default (int) values\n" << B << std::endl;

    //generic matrix with strings as elements
    matrix<std::string> C(2,2);
    std::cout << "matrix with strings as elements (default values "")\n" << C << std::endl;

    //matrix with strings as elements and "prova" as default value
    matrix<std::string> D(4,3, "prova");
    std::cout << "matrix with strings as elements and \"prova as default value\"\n" << D << std::endl;

    //copy constructor (results in a deep copy of the matrix)
    matrix<std::string> E(D);
    std::cout << "copy constructor of the previous matrix\n" << E << std::endl;

    //assignment operator test
    matrix<std::string> F = E;
    std::cout << "assignment operator\n" << F << std::endl;

    //test operator () 
    F(1,1) = "(1,1)";
    F(2,2) = "(2,2)";

    std::cout << "modified positions (1,1) and (2,2)\n" << F << std::endl;
}

void test_transpose() {
    std::cout << "***TEST TRANSPOSE METHOD***\n\n";

    matrix<int> A(4,5);

    for(int r = 0; r != 4; r++){
        for(int c = 0; c != 5; c++){
            A(r, c) = r + c;
        }
    }

    std::cout << "matrix A\n" << A << "\n\n";

    auto B = A.transpose(); //doesn't use copy constructor thanks to rvo

    std::cout << "matrix B\n" << B << "\n\n";

}

void test_subMatrix() {
    matrix<int> A(4,5);

    for(int r = 0; r != 4; r++){
        for(int c = 0; c != 5; c++){
            A(r, c) = r + c;
        }
    }

    std::cout << "matrix with assigned values (we effetuate all the submatrices on this matrix)\n" << A << std::endl;

    
    matrix<int> B = A.subMatrix(1,1,2,2);
    std::cout << "sub starting from (1,1) and ending in (2,2)\n" << B << std::endl;

    matrix<int> C = A.subMatrix(0,0,3,4);
    std::cout << "submatrix starting form the begin of the matrix and ending to the end of the matrix\n" << C << std::endl;

    matrix<int> D = A.subMatrix(0,1,1,3);
    std::cout << "submatrix starting from (0,1) and ending in (1,3)\n" << D << std::endl; 
}

void test_diagonal() {

    std::cout << "***DIAGONAL TEST***\n\n";

    matrix<int> A(4,5);

    for(int r = 0; r != 4; r++){
        for(int c = 0; c != 5; c++){
            A(r, c) = r + c;
        }
    }

    std::cout << "matrix A\n" << A << std::endl;

    auto B = A.diagonal();

    std::cout << "diagonal of A\n" << B << std::endl;

    matrix<int> C(5,4);

    for(int r = 0; r != 5; r++){
        for(int c = 0; c != 4; c++){
            C(r, c) = r + c;
        }
    }

    std::cout << "matrix C\n" << C << std::endl;

    auto D = C.diagonal();

    std::cout << "diagonal of C\n" << D << std::endl;
    
}

void test_diagonalmatrix() {
    std::cout << "***TEST DIAGONALMATRIX***\n\n";
    matrix<int> A(1,6,6);

    std::cout << "matrix A\n" << A << std::endl;

    auto B = A.diagonalMatrix();

    std::cout << "diagonal matrix of A\n" << B << std::endl;

}

void test_deepcopy(){
    matrix<int> A(4,5,6),B(A);
    std::cout<< "matrix copy costructor \n" << B << std::endl;
    matrix<int> C(B.transpose()); //This thing shall not deep copy the object (RVO but it's theoretically move constructor)
    std::cout<< "matrix copy costructor on transp method \n" << C << std::endl;
    std::cout<< "Chainging 1,1 element, the first two matrixies does not have to share memory, the last two does \n";
    C(1,1) = 0;
    matrix<int> D = B;
    std::cout<< "Printing matrixes \n" << A << std::endl << B << std::endl << C;    
    
}

void test_iterators() {
    std::cout << "***TEST ITERATORS***\n\n";

    matrix<int> A(4,5);

    for(int r = 0; r != 4; r++){
        for(int c = 0; c != 5; c++){
            A(r, c) = r + c;
        }
    } 

    std::cout << "Matrix A\n" << A << std::endl;

    //here we iterate the matrix by row and by colunm, on the whole matrix or selecting the
    //starting row/column and the ending row/column

    std::cout << "Matrix iterated with the row iterator\n";

    for(auto iter = A.row_begin(); iter != A.row_end(); ++iter) {
        std::cout << *iter << " ";
    } 

    std::cout << "\n";

    std::cout << "\nMatrix iterated with the col iterator\n";

    for(auto iter = A.col_begin(); iter != A.col_end(); ++iter) {
        std::cout << *iter << " ";
    }
    

    std::cout << "\n";

    std::cout << "\nMatrix iterated with the row iterator, only the first row\n";

    for(auto iter = A.row_begin(0); iter != A.row_end(0); ++iter) {
        std::cout << *iter << " ";
    } 

    std::cout << "\n";

    std::cout << "\nMatrix iterated with the row iterator, from row 2 to 3\n";

    for(auto iter = A.row_begin(1); iter != A.row_end(2); ++iter) {
        std::cout << *iter << " ";
    }

    std::cout << "\n";

    std::cout << "\nMatrix iterated with the col iterator, only the last column\n";

    for(auto iter = A.col_begin(4); iter != A.col_end(4); ++iter) {
        std::cout << *iter << " ";
    } 

    std::cout << "\n";

    std::cout << "\nMatrix iterated with the col iterator, from row 1 to 2\n";

    for(auto iter = A.col_begin(0); iter != A.col_end(1); ++iter) {
        std::cout << *iter << " ";
    }

    std::cout << "\n\n";


    //testing the const iterators (called automatically on a constant matrix)
    matrix<int> B(4,4);

    for(auto iter = B.row_begin(); iter != B.row_end(); ++iter) {
        *iter = rand() % 50;
    } 

    const auto C = B;  

    std::cout << "Matrix B\n" << B << std::endl;

    std::cout << "Matrix iterated with the const row iterator" << std::endl;

    for(auto iter = C.row_begin(); iter != C.row_end(); ++iter) {
        std::cout << *iter << " ";
    } 

    std::cout << "\n\n";


    std::cout << "Matrix iterated with the const column iterator" << std::endl;

    for(auto iter = C.col_begin(); iter != C.col_end(); ++iter) {
        std::cout << *iter << " ";
    }

    std::cout << "\n\n";


    //the same tests as before but on a constant matrix

    std::cout << "Matrix iterated with the row iterator, only the first column\n";

    for(auto iter = C.row_begin(0); iter != C.row_end(0); ++iter) {
        std::cout << *iter << " ";
    } 

    std::cout << "\n\n";

    std::cout << "Matrix iterated with the row iterator, from column 2 to 3\n";

    for(auto iter = C.row_begin(1); iter != C.row_end(2); ++iter) {
        std::cout << *iter << " ";
    }

    std::cout << "\n\n";

    std::cout << "Matrix iterated with the col iterator, only the last column\n";

    for(auto iter = C.col_begin(3); iter != C.col_end(3); ++iter) {
        std::cout << *iter << " ";
    }

    std::cout << "\n\n";
 

    std::cout << "Matrix iterated with the col iterator, from colunm 1 to 2\n";

    for(auto iter = C.col_begin(0); iter != C.col_end(1); ++iter) {
        std::cout << *iter << " ";
    }

    std::cout << "\n";

}


void test_library_usage() {
    std::cout << "***TEST LIBRARY USAGE***\n\n";

    matrix<int>A (3,6);

    for(auto iter = A.row_begin(); iter != A.row_end(); ++iter) {
        *iter = rand() % 50;
    } 

    std::cout << "matrix A\n" << A << std::endl;

    auto B = A.transpose();

    std::cout << "transpose of A (matrix B)\n" << B << std::endl;

    auto C = B.subMatrix(0,0,0,2);

    std::cout << "submatrix of B (taking the first row, creating vector C)\n" << C << std::endl; 

    auto D = C.transpose();

    std::cout << "transposing C (creating vector D)\n" << D << std::endl;

    auto E = D.diagonalMatrix();

    std::cout << "creating the diagonalmatrix starting from D (matrix E)(submatrix covector)\n" << E << std::endl;

    matrix<int>F(4,1,7);

    std::cout << "creating diagonal matrix from standard covector" << std::endl;

    auto O = F.diagonalMatrix();

    std::cout << O;

    std::cout << "creating diagonal matrix from standard vector" << std::endl;

    matrix<int>G(1,4,7);

    std::cout << G.diagonalMatrix();

    std::cout << "creating diagonal matrix from submatrix vector" << std::endl;
    matrix<int> J = A.subMatrix(0,2,0,5);
  
    std::cout << "starting vector" << std::endl;
    std::cout << J;
    std::cout << "\n" << std::endl;
    std::cout << J.diagonalMatrix();
    

    std::cout << "creating diagonal matrix from diagonal vector" << std::endl;
    std::cout << J;
    std::cout << "starting vector" << std::endl;
   

}

int main() {

    test_fondamental_methods();

    test_deepcopy();

    test_subMatrix();

    test_transpose();

    test_diagonal();

    test_diagonalmatrix();

    test_iterators();

    test_library_usage();


}

