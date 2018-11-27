#include "matrix.h"
#include <string>


//Test on the must-have methods
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

//test to the deep copy of a matrix
void test_deepcopy(){
    matrix<int> A(4,5,6),B(A);
    std::cout<< "***TEST DEEP COPY*** \n\n" << B << std::endl;
    
    matrix<int> C(B.transpose()); //This thing shall not deep copy the object (RVO but it's theoretically move constructor)
    std::cout<< "matrix copy costructor on transp method \n" << C << std::endl;
    std::cout<< "Changing 1,1 element, the first two matrixies does not have to share memory, the last two does \n";
    C(1,1) = 000;
    
    matrix<int> D = B;
    std::cout<< "Printing matrixes \n" << A << std::endl << B << std::endl << C;    
    
    std::cout<< "Deep copying a Diagonal Matrix" << std::endl;
    std::cout<< "Start matrix\n" << A;
    matrix<int> E = A.diagonal().diagonalMatrix();
    std::cout<< "\nDiagonal Matrix\n" << E;
    matrix<int> F = E;
    std::cout<< "\nDeep copy matrix\n" << F;
    F(0,0) = 1;
    std::cout<< "\nMatrixes after a modification on the deep copied one\n" << F << std::endl << E;
}

//Test on the tranpose method of matrix
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

//Test on the submatrix method of matrix
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

//Test on the diagonal method of matrix
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

//Test on the diagonal matrix method of matrix
void test_diagonalmatrix() {
    std::cout << "***TEST DIAGONALMATRIX***\n\n";
    matrix<int> A(1,6,6);

    std::cout << "matrix A\n" << A << std::endl;

    const auto B = A.diagonalMatrix();

    std::cout << "diagonal matrix of A\n" << B << std::endl;

}

//Test on the various iterators we implemented
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

//Test of a particular usage of the matrix operations 
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
    std::cout << "starting matrix" << std::endl;
    std::cout << A;
    std::cout << "starting vector" << std::endl;
    std::cout << A.diagonal();
    std::cout << "result matrix" << std::endl;
    std::cout << A.diagonal().diagonalMatrix();

    std::cout << "Using operators on temporary objects" << std::endl;
    std::cout << "Transpose of a diagonal vector of a submatrix\n";
    std::cout << "Starting matrix\n" << A;
    std::cout << "Result vector \n" << A.subMatrix(0,0,2,2).diagonal().transpose();

    std::cout << "Now the (0, 0) element of a temporary view of the matrix will be changed\n";
    A.diagonal().transpose().subMatrix(0, 0, 0, 0)(0,0) = 0;
    std::cout << "Showing some views of the matrix, there should be a 0 somewhere\n";
    std::cout << A << std::endl << C << std::endl << B << std::endl;
   

}

void test_libray_usage2() {
    std::cout << "***TEST LIBRARY USAGE 2***\n\n";

    matrix<int>A (3,6);

    for(auto iter = A.row_begin(); iter != A.row_end(); ++iter) {
        *iter = rand() % 50;
    } 

    std::cout << "matrix A\n" << A << std::endl;

    auto B = A.transpose().subMatrix(0,0,1,1).diagonal();

    std::cout << "diagonal of the submatrix (0,0,1,1) of the transposed A (called B)\n" << B << std::endl;

    matrix<int> C = B.diagonalMatrix();

    std::cout << "diagonal matrix of matrix B (called C)\n";

    for (auto iter = C.row_begin(); iter != C.row_end(); ++iter) {
        std::cout << *iter << " ";
    }

    std::cout << "\nmatrix C with cout\n" << C << std::endl;




}

//custom type used as a test case
struct course {
    unsigned int credits;
    std::string name;
    course() : credits(0), name("def") {}
    course(unsigned int cr, std::string n) : credits(cr), name(n) {}
    bool operator>(const course c) const{
      return ( credits > c.credits );
    }
    unsigned int getCredits() const{
      return credits;
    }

};

//overload of standard output operator in order to print a course type 
std::ostream &operator<<(std::ostream &os,const course c){
	os << c.name << " ; " << c.credits;
	return os;
}

void test_custom_type(){
    std::cout << "***CUSTOM TYPE TEST***\n\n";

    std::cout << "***We will create a matrix containg objects of type course***\n\n";
    
    matrix<course> A(4, 5);
    
    std::cout << "Empty 4x5 matrix\n" << A;
    
    course def(6, "Advanced algorithm 2");
    matrix<course> B(3, 4, def);
    
    std::cout << "3x4 matrix with fixed value\n" << B;
    
    std::cout << "Operations test on last matrix\n\n\n";
    std::cout << "Transpose\n";
    std::cout << B.transpose();
    
    std::cout << "Submatrix 2x2\n";
    std::cout << B.subMatrix(0,0,1,1);
    
    std::cout << "Diagonal\n";
    std::cout << B.diagonal();
    
    std::cout << "Diagonal matrix of diagonal\n";
    std::cout << B.diagonal().diagonalMatrix();

    

}

void diagonal_problem() {
    matrix<int>A (1,6);

    for(auto iter = A.row_begin(); iter != A.row_end(); ++iter) {
        *iter = rand() % 50;
    }

    std::cout << "matrix A\n" << A << std::endl;

    auto B = A.diagonalMatrix();
    const auto C = A.diagonalMatrix();

    std::cout << "non const diagonalmatrix\n\n";

    for(auto iter = B.row_begin(); iter != B.row_end(); ++iter ) {
        std::cout << *iter << " ";
    }

        std::cout << "const diagonalmatrix\n\n";

    for(auto iter = C.row_begin(); iter != C.row_end(); ++iter ) {
        std::cout << *iter << " ";
    }

    


}


int main() {
    /*

    test_fondamental_methods();

    test_deepcopy();

    test_transpose();

    test_subMatrix();

    test_diagonal();

    test_diagonalmatrix();

    test_iterators();

    test_library_usage();
    */

    //test_libray_usage2();

    //test_custom_type();

    diagonal_problem();

}

 