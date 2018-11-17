
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

    
    std::cout << "\n\n\n";
    std::cout << "PROVA ITERATORE COLONNA: " << std::endl;

    for(int r = 0; r != 4; r++){
        for(int c = 0; c != 5; c++){
            D(r, c) = r + c;
        }
    }
    std::cout << D;

    //iterazione sulla matrice per colonna
    int i = 0;
    int col = 1;
    for(auto iter = D.col_begin(0); iter != D.col_end(4); ++iter){
        if(i == 4 || i == 0){
            std::cout << "\nColonna " << col << ": ";
            i=0;
            col++;
        }
        std::cout << *iter << " ";
        i++;
    }

    std::cout << "\n";
    
    auto iter1 = D.col_begin(1);
    auto iter2 = D.col_begin(2);

    for(int i = 0; i < 4; i++){
        ++iter1;
    }

    if(iter1 == iter2){
        std::cout << "equivalence between iterators test passed" << std::endl;
    }

    std::cout << "\n\n\n";

    i= 0;
    int rowa = 1;
    //prova iteratore riga
    std::cout << "PROVA ITERATORE RIGA: " << std::endl;
    for(auto iter = D.row_begin(0); iter != D.row_end(3); ++iter){
        if(i == 5 || i == 0){
            std::cout << "\nRiga " << rowa << ": ";
            i=0;
            rowa++;
        }
        std::cout << *iter << " ";
        i++;
        
    }
    
}
