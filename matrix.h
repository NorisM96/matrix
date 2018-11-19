
#ifndef MATRIX_H
#define MATRIX_H

#include "iterators.h"
#include <ostream> // std::ostream
#include <vector>
#include <iterator> // std::forward_iterator_tag
#include <memory>
#include <iostream>


template <typename T>
class Matrix
{
  public:
	typedef T type;
	typedef typename std::vector<T>::iterator iterator;
	typedef typename std::vector<T>::const_iterator const_iterator;
	typedef typename std::vector<T>::iterator row_iterator;
	typedef typename std::vector<T>::const_iterator const_row_iterator;

	typedef index_col_iterator<T> column_iterator;
	typedef const_index_col_iterator<T> const_column_iterator;

	//DEFAULT CONSTRUCTOR
	Matrix() : columns(0), rows(0), start_row(0), start_column(0), pter(nullptr){}

	//CONSTRUCTOR WHICH CONSTRUCT A Matrix FILLED WITH ZEROES ON CREATION
	explicit Matrix(const unsigned rws , const unsigned cols)  {
		columns = cols;
		rows = rws;
		start_row= 0;
		start_column = 0;
		transp = false;
		pter = std::make_shared<std::vector<T>>(columns * rows);
		for (type c : *pter)
			c = type();
	}

	//CONSTRUCTOR WHICH CONSTRUCT A Matrix FILLED WITH A DEFAULT VALUE ON CREATION
	explicit Matrix(const unsigned rws, const unsigned cols, const type &val) {
		columns = cols;
		rows = rws;
		start_row= 0;
		start_column = 0;
		transp = false;
		pter = std::make_shared<std::vector<T>>(columns * rows);
		for (unsigned i = 0; i < (columns * rows); i++)
			pter->operator[](i) = val;
	}
	
	

	//COPY CONSTRUCTOR
	Matrix(const Matrix<type> &other){
		columns = other.columns;
		rows = other.rows;
		start_row = other.start_row;
		start_column = other.start_column;
		transp = other.transp;
		pter = std::make_shared<std::vector<T>>(columns * rows);
		for (unsigned i = 0; i < (columns * rows); i++)
			pter->operator[](i) = other.pter->operator[](i);
		std::cout << "COPY CONSTRUCTOR INVOKED" <<std::endl;
	}

	//MOVE COSTRUCTOR
	Matrix(Matrix<T> &&other){
		std::cout << "MOVE CONSTUCTOR INVOKED" <<std::endl;
		columns = other.columns;
		rows = other.rows;
		start_row= other.start_row;
		start_column = other.start_column;
		pter = other.pter;	//maybe private method to do this
		other.pter = nullptr; //same problem as above, but maybe with same class type there is no need
	}

	//MOVE ASSIGNMENT OPERATOR
	Matrix &operator=(Matrix<type> &&other) {
		std::cout<<"MOVE ASSIGNMENT INVOKED" << std::endl;
		columns = other.columns;
		rows = other.rows;
		start_row= other.start_row;
		start_column = other.start_column;
		transp = other.transp;
		pter = other.pter;	//maybe private method to do this
		other.pter = nullptr; //same problem as above
	}

	//ASSIGNMENT OPERATOR
	Matrix &operator=(const Matrix<type> &other){
		std::cout<<"NORMAL ASSIGNMENT INVOKED" << std::endl;
		if (this != &other){
			Matrix<T> tmp(other);
			this->swap(tmp);
		}
		return *this;
	}

	//SWAP METHOD FOR ASSIGNMENT OPERATOR
	void swap(Matrix<T> &other) {
		std::swap(other.pter, this->pter);
		std::swap(other.columns, this->columns);
		std::swap(other.rows, this->rows);
		std::swap(other.pter, this->pter);
		std::swap(other.start_column, this->start_column);
		std::swap(other.start_row, this->start_row);
		std::swap(other.transp, this->transp);
	}

	

	//OPERATOR () TO DIRECTLY ACCESS THE ELEMENTS
	type &operator()(unsigned row, unsigned column) {
		if(!transp)
			return pter->operator[]((row+start_row) * (columns + start_column) + (column + start_column));
		else
			return pter->operator[]((column + start_column) * (rows + start_row) + (row + start_row));
	}


	const type &operator()(unsigned row, unsigned column) const {
		if(!transp)
			return pter->operator[]((row+start_row) * (columns + start_column) + (column + start_column));
		else
			return pter->operator[]((column + start_column) * (rows + start_row) + (row + start_row));
	}

	//SUBMatrix METHOD
	Matrix subMatrix(const unsigned srw, const unsigned scold, const unsigned erow,const unsigned ecold) {
		return Matrix<type>((start_row + srw), (start_row + erow), (start_column + scold), (start_column + ecold), transp, pter);
	}

	//TRANSPOSE METHOD
	Matrix transpose() const{
		return Matrix<type>(*this, !transp);
	}
	//DIAGONAL METHOD(MUST RETURN A VECTOR WITH ELEMENT = TO DIAGONAL OF THE Matrix)
	Matrix<type> diagonal() const {

	}

	//DESTRUCTOR
	~Matrix(){
		columns = 0;
		rows = 0;
		start_column = 0;
		start_row = 0;
		std::vector<type>().swap(*pter);
	}
	//DIAGONAL Matrix METHOD(MUST BE USED ONLY BY VECTOR CLASS AND IT RETURNS A DIAGONAL Matrix WHOSE ELEMENTS BELONGS TO THE VECTOR )
	const Matrix<type> diagonalMatrix() const {
	}

	//GET METHOD FOR ROWS PARAMETER
	unsigned getRows() const {
		return rows;
	}

	//GET METHOD FOR COLUMNS PARAMETER
	unsigned getColumns() const {
		return columns;
	}

	//ALL THE FUCKING ITERATORS
	iterator begin() { return pter->begin();}
	iterator end() { return pter->end(); }
	const_iterator begin() const { return pter->begin(); }
	const_iterator end() const { return pter->end(); }

	row_iterator row_begin(unsigned i) { return pter->begin() + (i * columns); }   //mi sa che sto scrivendo cose a caso
	row_iterator row_end(unsigned i) { return pter->begin() + (i + 1) * columns; } //non scrivo codice da anni
	const_row_iterator row_begin(unsigned i) const { return pter->begin() + (i * columns); }
	const_row_iterator row_end(unsigned i) const { return pter->begin() + (i + 1) * columns; }

	column_iterator col_begin(unsigned i) { return column_iterator(*this, 0, i); }
	column_iterator col_end(unsigned i) { return column_iterator(*this, 0, i + 1); } //questa potrebbe andare come no, il tempo ce lo dirà
	//virtual const_column_iterator col_begin(unsigned i) const { return column_iterator(*this, 0, i); }
	//virtual const_column_iterator col_end(unsigned i) const { return column_iterator(*this, 0, i + 1); } //idem come sopra

	//KILL ME PLEASE , OKAY
  protected:

	Matrix(const unsigned srw, const unsigned erow, const unsigned scl, const unsigned ecol , const bool trsp, const std::shared_ptr<std::vector<type>> ptr){
		if(!trsp){
			rows = (erow -srw) + 1;
			columns = (ecol -scl) +1;
		}
		else{
			rows = (ecol - scl) + 1;
			columns = (erow - srw) + 1;
		}
		pter = ptr;
		start_row= srw;
		start_column = scl;
		transp = trsp;
	}

	Matrix(const Matrix<T> &other, const bool trsp){
		pter = other.pter;
		start_row= other.start_column;
		start_column = other.start_row;
		rows = other.columns;
		columns = other.rows;
		transp = trsp;
	}


  	std::shared_ptr<std::vector<type>> pter;
	bool transp;
	unsigned columns, rows, start_row, start_column;
};


//OVERLOAD OSTREAM OPERATOR
template <typename T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &ma){
	for (unsigned r = 0; r < ma.getRows(); r++){
		for (unsigned c = 0; c < ma.getColumns(); c++){
			os << "[" << ma(r, c) << "] ";
		}
		os << std::endl;
	}
	return os;
}


#endif