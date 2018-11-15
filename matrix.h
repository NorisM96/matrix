
#ifndef MATRIX_H
#define MATRIX_H

#include "iterators.h"
#include <ostream> // std::ostream
#include <vector>
#include <iterator> // std::forward_iterator_tag

template <typename T>
class matrix {
  public:
    typedef unsigned int size_c;
    typedef unsigned int size_r;
    typedef T type;
    //DEFAULT CONSTRUCTOR
    matrix() : columns(0), rows(0), pter(nullpter) {

    }
    //CONSTRUCTOR WHICH CONSTRUCT A MATRIX FILLED WITH ZEROES ON CREATION
    extern matrix(const size_c cols, const sizer rws) : columns(cols), rows(rws), pter(std::make_shared<std::vector<type>>(cols * rows)) {
      for(type c: *pter)
        c = type();
    }

    //COPY CONSTRUCTOR
    matrix(const matrix<T> &other) : columns(0), rows(0), pter(nullptr) {
      rows = other.getRows();
      columns = other.getColumns();
      pter(std::make_shared<std::vector<type>>(cols * rows))
      //Copy all values with foreach, need to implements iterators first
      /*
        int i = 0;
        for( j : other){
          pter[i] = other.pter[i];
          i++;                May not be right
        }
      */
    }

    //MOVE COSTRUCTOR
    matrix(const matrix<T> &&other) : columns(0), rows(0), pter(nullptr){
      pter = other.pter;  //maybe private method to do this
      other.pter = nullptr; //same problem as above, but maybe with same class type there is no need
    }

    //ASSIGNMENT OPERATOR
    matrix &operator= (const matrix<type> &other) {
      if (this != &other) {
        matrix<T> tmp(other);
        this->swap(tmp);
      }
      return *this;
    }

    //SWAP METHOD FOR ASSIGNMENT OPERATOR
    void swap(matrix<T> &other) {
      std::swap(other.pter, this->pter);
      std::swap(other.columns, this->columns);
      std::swap(other.rows, this->rows);
    }

    //MOVE ASSIGNMENT OPERATOR
    matrix &operator= (const matrix<type> &&other) {
      pter = other.pter;  //maybe private method to do this
      other.pter = nullptr; //same problem as above
    }

    //OPERATOR () TO DIRECTLY ACCESS THE ELEMENTS 
    type& operator ()( unsigned row, unsigned column ) { 
		  return pter->operator[](row*rows + column);
	  }
	  
    const T& operator ()( unsigned row, unsigned column ) const { 
		  return pter->operator[](row*rows + column);
	  }

    //SUBMATRIX METHOD
    matrix<type> submatrix() const{

    }

    //TRANSPOSE METHOD
    matrix<type> transpose() const {

    }
    //DIAGONAL METHOD(MUST RETURN A VECTOR WITH ELEMENT = TO DIAGONAL OF THE MATRIX)
    matrix<type> diagonal()  const{
      
    }

    //DIAGONAL MATRIX METHOD(MUST BE USED ONLY BY VECTOR CLASS AND IT RETURNS A DIAGONAL MATRIX WHOSE ELEMENTS BELONGS TO THE VECTOR )
    const matrix<type> diagonalmatrix() const{
      
    }

    //GET METHOD FOR ROWS PARAMETER
    unsigned getRows() const{
      return rows;
    }
    
    //GET METHOD FOR COLUMNS PARAMETER
    unsigned getColumns() const{
      return columns;
    }

    //ALL THE FUCKING ITERATORS
    iterator begin() { return pter->begin(); }
    iterator end() { return pter->end(); }
    const_iterator begin() const { return pter->begin(); }
    const_iterator end() const { return pter->end(); }
    
    row_iterator row_begin(unsigned i) { return col_begin(1) + (rows - 1); }//mi sa che sto scrivendo cose a caso
    row_iterator row_end(unsigned i) { return col_begin(columns) + (rows - 1); }//non scrivo codice da anni
    const_row_iterator row_begin(unsigned i) {return col_begin(1) + (rows - 1);}
    const_row_iterator row_end(unsigned i) {return col_begin(columns) + (rows - 1);}

    column_iterator col_begin(unsigned i) { return pter->begin() + ( i * columns); }
    column_iterator col_end(unsigned i) { return col_begin(i) + (columns - 1); } //questa potrebbe andare come no, il tempo ce lo dirà
    const_column_iterator col_begin(unsigned i) const { return pter->begin() + ( i * columns); }
    const_column_iterator col_end(unsigned i){ return col_begin(i) + (columns - 1); } //idem come sopra

  //KILL ME PLEASE , OKAY
  private:
    std::shared_ptr<std::vector<type>> pter;
    unsigned columns,rows;
    
};

//OVERLOAD OSTREAM OPERATOR
template <typename T>
std::ostream &operator<<(std::ostream &os,
	const matrix<T> &ma){
		for(int r = 1;r <= ma.getRows();r++){
      for(int c = 1;c <= ma.getColumns();c++){
        os <<"[" << ma(r,c) << "] ";
      }
      os << std::endl;
    }
		return os;
}

#endif