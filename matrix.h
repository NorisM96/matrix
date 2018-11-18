
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
		return Matrix<T>::pter->operator[](column * Matrix<T>::rows + row);
	}


	virtual const T &operator()(unsigned row, unsigned column) const {
		return Matrix<T>::pter->operator[](column * Matrix<T>::rows + row);
	}

	//index_col_iterator<T> begin() {return column_iterator(*this, 0, 0);}
	//index_col_iterator<T> end() {return column_iterator(*this, 0, Matrix<T>::columns);}

	MatrixTranspose() : Matrix<T>(){}

	MatrixTranspose(const unsigned rws, const unsigned cols,const std::shared_ptr<std::vector<T>> ptr){
		Matrix<T>::rows = cols;
		Matrix<T>::columns = rws;
		Matrix<T>::pter = ptr; 
	}
};

template <typename T>
class SubMatrix : public Matrix<T> {
	public:
	virtual T &operator()(unsigned row, unsigned column) {
			return Matrix<T>::pter->operator[]((srow + row) * (Matrix<T>::columns + scol) + (scol + column));
				
	}


	virtual const T &operator()(unsigned row, unsigned column) const {
			return Matrix<T>::pter->operator[]((srow + row) * (Matrix<T>::columns+ scol) + (scol + column));
	}

	
	SubMatrix() : Matrix<T>(){}

	
	SubMatrix(const unsigned starting_row, const unsigned ending_row, const unsigned starting_col, const unsigned ending_col, const std::shared_ptr<std::vector<T>> ptr){
		Matrix<T>::rows = (ending_row - starting_row);
		Matrix<T>::columns = (ending_col - starting_col);
		scol = starting_col;
		srow = starting_row;
		Matrix<T>::pter = ptr; 
	}

	private:
		unsigned srow, scol;
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
	Matrix() : columns(0), rows(0), pter(nullptr){}

	//CONSTRUCTOR WHICH CONSTRUCT A Matrix FILLED WITH ZEROES ON CREATION
	explicit Matrix(const unsigned rws , const unsigned cols)  {
		columns = cols;
		rows = rws;
		pter = std::make_shared<std::vector<T>>(columns * rows);
		for (type c : *pter)
			c = type();
	}

	//CONSTRUCTOR WHICH CONSTRUCT A Matrix FILLED WITH A DEFAULT VALUE ON CREATION
	explicit Matrix(const unsigned rws, const unsigned cols, const type &val) {
		columns = cols;
		rows = rws;
		pter = std::make_shared<std::vector<T>>(columns * rows);
		for (unsigned i = 0; i < (columns * rows); i++)
			pter->operator[](i) = val;
	}
	
	

	//COPY CONSTRUCTOR
	Matrix(const Matrix<type> &other){
		columns = other.getColumns();
		rows = other.getRows();
		pter = std::make_shared<std::vector<T>>(columns * rows);
		for (unsigned i = 0; i < (columns * rows); i++)
			pter->operator[](i) = other.pter->operator[](i);
		std::cout << "COPY CONSTRUCTOR INVOKED" <<std::endl;
	}

	//MOVE COSTRUCTOR
	Matrix(Matrix<T> &&other) : columns(0), rows(0), pter(nullptr){
		std::cout << "MOVE CONSTUCTOR INVOKED" <<std::endl;
		pter = other.pter;	//maybe private method to do this
		other.pter = nullptr; //same problem as above, but maybe with same class type there is no need
	}

	//MOVE ASSIGNMENT OPERATOR
	Matrix &operator=(Matrix<type> &&other) {
		std::cout<<"MOVE ASSIGNMENT INVOKED" << std::endl;
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
	}

	

	//OPERATOR () TO DIRECTLY ACCESS THE ELEMENTS
	virtual type &operator()(unsigned row, unsigned column) {
		return pter->operator[](row *columns + column);
	}


	virtual const type &operator()(unsigned row, unsigned column) const {
		return pter->operator[](row * columns + column);
	}

	//SUBMatrix METHOD
	SubMatrix<type> subMatrix(const unsigned srow, const unsigned scold, const unsigned erow,const unsigned ecold) {
		return SubMatrix<type>(srow, erow, scold, ecold, pter);
	}

	//TRANSPOSE METHOD
	MatrixTranspose<type> transpose() const{
		return MatrixTranspose<type>(rows, columns, pter);
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

  	std::shared_ptr<std::vector<type>> pter;
	unsigned columns, rows;
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