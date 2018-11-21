#include "matrix.h"


int main() {
    Matrix<int> A(4, 5), B(A);
    std::cout << A;
    std::cout << "COPYYYYYYYY" << std::endl;
    std::cout << B;
    Matrix<int> C(4,5,6);
    std::cout << "GUARDA MAMMA COL SEI DIOCANEEEEEEE" << std::endl;
    std::cout << C;
    Matrix<int> D(C);
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
        std::cout << *iter << " " ;
        i++;
        
    }

    auto S = D.subMatrix(2,1,3,4);
    std::cout << "\n\n" << S;
    

    std::cout << "\n\n\n" << std::endl;

    std::cout << D << std::endl;

    std::cout << "\n\n\n" << std::endl;

    auto E = D.transpose();
    std::cout << E << std::endl;

    auto F = E.transpose();
    std::cout << "\n\n\n" << std::endl;
    std::cout << F << std::endl;

    auto G = F.subMatrix(1,1,3,3);
    std::cout << "\n\n\n" << std::endl;

    std::cout << G;

    std::cout << "matrice dritta\n";

    Matrix<int> FF (4,5);

    for(int r = 0; r != 4; r++){
        for(int c = 0; c != 5; c++){
            FF(r, c) = r + c;
        }
    }
    std::cout << FF << std::endl;

    std::cout << "trans"<< std::endl;

    auto LL =  FF.transpose() ;

    std::cout << LL << std::endl;

    std::cout << " sub\n" << std::endl;

    auto GG = LL.subMatrix(0,1,3,3);

    std::cout << GG << "\n";

    auto DI = GG.transpose();

    std::cout << "trasposta\n" <<DI << std::endl;

    auto DG = GG.diagonal();

    std::cout <<"Diagonalley\n" << DG;

    auto DGT = DG.transpose();
    std::cout <<"Diagonalley al contrario\n" << DGT;

    auto DG2 = LL.diagonal();
    std::cout << LL;
    std::cout << "Diagonally su transposta \n" << DG2;

    auto DG3 = DG2.transpose();
    std::cout<< "DIO SMANDRAPPINO CANE " << DG3;

    auto DG6 = DG2.diagonalMatrix();
    std::cout << DG6;

    Matrix<int> VE1(5,1,3), VE2(1,5,3);
    std::cout << "Vettore\n" << VE1;
    auto DGMV = VE1.diagonalMatrix();
    std::cout << "Covettore\n" << VE2;
    auto DGMV2 = VE2.diagonalMatrix();
    std::cout << "DIAGMATRIX Vettore\n "<<DGMV; 
    std::cout << "DIAGMATRIX Covettore\n" << DGMV2;
    std::cout << "SOTTOMATRICE DI PARTENZA\n" << GG;
    auto SMD = GG.subMatrix(0, 0, 3, 0);
    std::cout << "SOTTOMATRICE VETTORE\n" << SMD;
    auto DMVS = SMD.diagonalMatrix();
    std::cout << "DIAGONALMATRIX DI UN VETTORE SOTTOMATRICE\n" <<DMVS;   
    std::cout   << "Check transpose method" <<   std::endl;
    auto R = C.transpose();
    std::cout << R;
    C(1,2) = 5;
    std::cout<<"POSIZIONE 1,2 MATRICE NORMALE = 5" << std::endl;
    std::cout<<"STAMPO MATRICE NORMALE" << std::endl;
    std::cout << C;
    std::cout<<"STAMPO MATRICE TRASPOSTA" << std::endl;
    std::cout << R;
    R(1,2) = 3;
    std::cout<<"POSIZIONE 1,2 MATRICE TRASPOSTA = 3" << std::endl;
    std::cout<<"STAMPO MATRICE NORMALE" << std::endl;
    std::cout << C;
    std::cout<<"STAMPO MATRICE TRASPOSTA" << std::endl;
    std::cout << R;
    auto H = R.transpose();
    std::cout<<"STAMPO MATRICE TRASPOSTA TRANSPOSTA DIO CANTASTICO" << std::endl;
    std::cout << H;
    std::cout<<"TEST SOTTOMATRICE" << std::endl;
    auto S = C.subMatrix(1,1,4,5);
    std::cout<< "MATRICE NORMALE" <<std::endl;
    std::cout << C;
    std::cout<< "MATRICE SUB" << std::endl;
    std::cout << S;
    auto G = S.transpose();
    std::cout<< "MATRICE TRANSPOSTA" << std::endl;
    std::cout << G;
    std::cout<< "PROVO A CAMBIARE UN ELEMENTO, DOVREBBE MODIFICARE TUTTE LE MATRICI" << std::endl;
    G(0, 0) = 0;
    std::cout<<"TUTTE LE MATRICI DOVREBBERO AVERE UNO ZERO" << std::endl;
    std::cout << G;
    std::cout << S;
    std::cout << C;
    std::cout << "NON CENE DI NEGRI IN ITALIA CON MATRICI FUNXIONANTI" << std::endl; 
}
