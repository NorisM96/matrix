
#ifndef MATRIX_H
#define MATRIX_H

#include "iterators.h"
#include <ostream> // std::ostream
#include <vector>
#include <iterator> // std::forward_iterator_tag
#include <memory>
#include <iostream>


template <typename T>
class MatrixTranspose : public Matrix<T> {
	public:

	virtual T &operator()(unsigned row, unsigned column) {
		return Matrix<T>::pter->operator[]((column + Matrix<T>::scolumn) * (Matrix<T>::rows + Matrix<T>::srow) + (row + Matrix<T>::srow));
	}


	virtual const T &operator()(unsigned row, unsigned column) const {
		return Matrix<T>::pter->operator[]((column + Matrix<T>::scolumn) * (Matrix<T>::rows + Matrix<T>::srow) + (row + Matrix<T>::srow));
	}

	//index_col_iterator<T> begin() {return column_iterator(*this, 0, 0);}
	//index_col_iterator<T> end() {return column_iterator(*this, 0, Matrix<T>::columns);}

	MatrixTranspose() : Matrix<T>(){}

	MatrixTranspose(const unsigned rws, const unsigned cols,const unsigned scol, const unsigned srw, const std::shared_ptr<std::vector<T>> ptr){
		Matrix<T>::rows = cols;
		Matrix<T>::columns = rws;
		Matrix<T>::pter = ptr;
		Matrix<T>::srow = scol;
		Matrix<T>::scolumn = srw;
	}

};

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
	Matrix() : columns(0), rows(0), srow(0), scolumn(0), pter(nullptr){}

	//CONSTRUCTOR WHICH CONSTRUCT A Matrix FILLED WITH ZEROES ON CREATION
	explicit Matrix(const unsigned rws , const unsigned cols)  {
		columns = cols;
		rows = rws;
		srow = 0;
		scolumn = 0;
		pter = std::make_shared<std::vector<T>>(columns * rows);
		for (type c : *pter)
			c = type();
	}

	//CONSTRUCTOR WHICH CONSTRUCT A Matrix FILLED WITH A DEFAULT VALUE ON CREATION
	explicit Matrix(const unsigned rws, const unsigned cols, const type &val) {
		columns = cols;
		rows = rws;
		srow = 0;
		scolumn = 0;
		pter = std::make_shared<std::vector<T>>(columns * rows);
		for (unsigned i = 0; i < (columns * rows); i++)
			pter->operator[](i) = val;
	}
	
	

	//COPY CONSTRUCTOR
	Matrix(const Matrix<type> &other){
		columns = other.columns;
		rows = other.rows;
		srow = other.srow;
		scolumn = other.scolumn;
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
		srow = other.srow;
		scolumn = other.scolumn;
		pter = other.pter;	//maybe private method to do this
		other.pter = nullptr; //same problem as above, but maybe with same class type there is no need
	}

	//MOVE ASSIGNMENT OPERATOR
	Matrix &operator=(Matrix<type> &&other) {
		std::cout<<"MOVE ASSIGNMENT INVOKED" << std::endl;
		columns = other.columns;
		rows = other.rows;
		srow = other.srow;
		scolumn = other.scolumn;
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
		std::swap(other.scolumn, this->scolumn);
		std::swap(other.srow, this->srow);
	}

	

	//OPERATOR () TO DIRECTLY ACCESS THE ELEMENTS
	virtual type &operator()(unsigned row, unsigned column) {
		return pter->operator[]((row+srow) * (columns +scolumn) + (column + scolumn));
	}


	virtual const type &operator()(unsigned row, unsigned column) const {
		return pter->operator[]((row+srow) * (columns +scolumn) + (column + scolumn));
	}

	//SUBMatrix METHOD
	Matrix subMatrix(const unsigned srow, const unsigned scold, const unsigned erow,const unsigned ecold) {
		return Matrix<type>(srow, erow, scold, ecold, pter);
	}

	//TRANSPOSE METHOD
	virtual MatrixTranspose<type> transpose() const{
		return MatrixTranspose<type>(rows, columns, scolumn, srow, pter);
	}
	//DIAGONAL METHOD(MUST RETURN A VECTOR WITH ELEMENT = TO DIAGONAL OF THE Matrix)
	Matrix<type> diagonal() const {
	}

	//DESTRUCTOR
	~Matrix(){
		columns = 0;
		rows = 0;
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
	virtual iterator begin() { return pter->begin();}

	virtual iterator end() { return pter->end(); }
	virtual const_iterator begin() const { return pter->begin(); }
	virtual const_iterator end() const { return pter->end(); }

	virtual row_iterator row_begin(unsigned i) { return pter->begin() + (i * columns); }   //mi sa che sto scrivendo cose a caso
	virtual row_iterator row_end(unsigned i) { return pter->begin() + (i + 1) * columns; } //non scrivo codice da anni
	virtual const_row_iterator row_begin(unsigned i) const { return pter->begin() + (i * columns); }
	virtual const_row_iterator row_end(unsigned i) const { return pter->begin() + (i + 1) * columns; }

	virtual column_iterator col_begin(unsigned i) { return column_iterator(*this, 0, i); }
	virtual column_iterator col_end(unsigned i) { return column_iterator(*this, 0, i + 1); } //questa potrebbe andare come no, il tempo ce lo dirà
	//virtual const_column_iterator col_begin(unsigned i) const { return column_iterator(*this, 0, i); }
	//virtual const_column_iterator col_end(unsigned i) const { return column_iterator(*this, 0, i + 1); } //idem come sopra

	//KILL ME PLEASE , OKAY
  protected:

	Matrix(const unsigned srw, const unsigned erow, const unsigned scl, const unsigned ecol , const std::shared_ptr<std::vector<type>> ptr){
		pter = ptr;
		srow = srw;
		scolumn = scl;
		rows = erow - srw;
		columns = ecol - scl;
	}

  	std::shared_ptr<std::vector<type>> pter;
	unsigned columns, rows, srow, scolumn;
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