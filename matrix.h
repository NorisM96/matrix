
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
	Matrix() : columns(0), rows(0), start_row(0), start_column(0), end_row(0), end_column(0), transp(false), pter(nullptr){}

	//CONSTRUCTOR WHICH CONSTRUCT A Matrix FILLED WITH ZEROES ON CREATION
	explicit Matrix(const unsigned rows , const unsigned columns)  {
		this->columns = columns;
		this->rows = rows;
		effective_rows = rows;
		effective_columns = columns;
		start_row = 0;
		start_column = 0;
		end_row = rows-1;
		end_column = columns-1;
		transp = false;
		pter = std::make_shared<std::vector<T>>(columns * rows);
		for (type c : *pter)
			c = type();
	}

	//CONSTRUCTOR WHICH CONSTRUCT A Matrix FILLED WITH A DEFAULT VALUE ON CREATION
	explicit Matrix(const unsigned rows, const unsigned columns, const type &val) {
		this->columns = columns;
		this->rows = rows;
		effective_rows = rows;
		effective_columns = columns;
		start_row = 0;
		start_column = 0;
		end_row = rows-1;
		end_column = columns-1;
		transp = false;
		pter = std::make_shared<std::vector<T>>(columns * rows);
		for (unsigned i = 0; i < (columns * rows); i++)
			pter->operator[](i) = val;
	}
	
	

	//COPY CONSTRUCTOR
	Matrix(const Matrix<type> &other){
		columns = other.columns;
		rows = other.rows;
		effective_rows = other.effective_rows;
		effective_columns = other.effective_columns;
		start_row = other.start_row;
		start_column = other.start_column;
		end_row = other.end_row;
		end_column = other.end_column;
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
		effective_rows = other.effective_rows;
		effective_columns = other.effective_columns;
		start_row = other.start_row;
		start_column = other.start_column;
		end_row = other.end_row;
		end_column = other.end_column;
		pter = other.pter;	//maybe private method to do this
		other.pter = nullptr; //same problem as above, but maybe with same class type there is no need
	}

	//MOVE ASSIGNMENT OPERATOR
	Matrix &operator=(Matrix<type> &&other) {
		std::cout<<"MOVE ASSIGNMENT INVOKED" << std::endl;
		columns = other.columns;
		rows = other.rows;
		effective_rows = other.effective_rows;
		effective_columns = other.effective_columns;
		start_row = other.start_row;
		start_column = other.start_column;
		end_row = other.end_row;
		end_column = other.end_column;
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
		std::swap(other.effective_columns, this->effective_columns);
		std::swap(other.effective_rows, this->effective_rows);
		std::swap(other.pter, this->pter);
		std::swap(other.start_column, this->start_column);
		std::swap(other.start_row, this->start_row);
		std::swap(other.end_column, this->end_column);
		std::swap(other.end_row, this->end_row);
		std::swap(other.transp, this->transp);
	}

	

	//OPERATOR () TO DIRECTLY ACCESS THE ELEMENTS
	type &operator()(unsigned row, unsigned column) {
		if(!transp)
			return pter->operator[](((row + start_row) * columns)+ column + start_column);
		else
			return pter->operator[]((column + start_column) * (rows) + (row + start_row));
	}


	const type &operator()(unsigned row, unsigned column) const {
		if(!transp)
			return pter->operator[]((row+start_row) * (columns) + column + start_column);
		else
			return pter->operator[]((column + start_column) * (rows) + (row + start_row));
	}

	//subMatrix METHOD
	Matrix subMatrix(const unsigned start_row, const unsigned start_column, const unsigned end_row,const unsigned end_column) {
		const unsigned new_eff_rows = end_row - start_row + 1;
		const unsigned new_eff_columns = end_column - start_column + 1;

		return Matrix<type>(rows, columns, new_eff_rows, new_eff_columns, start_row, start_column, end_row, end_column, transp, pter);
	}

	//TRANSPOSE METHOD
	Matrix transpose() const{
		const unsigned new_rows = effective_columns;
		const unsigned new_columns = effective_rows;
		const unsigned new_start_row = start_column;
		const unsigned new_start_column = start_row;
		const unsigned new_end_row = end_column;
		const unsigned new_end_column = end_row;
		const bool new_transp = !transp; 

		return Matrix<type>(columns, rows, new_rows, new_columns, new_start_row, new_start_column, new_end_row, new_end_column, new_transp, pter);
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
		return effective_rows;
	}

	//GET METHOD FOR COLUMNS PARAMETER
	unsigned getColumns() const {
		return effective_columns;
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

	Matrix(const unsigned rows, const unsigned columns, const unsigned eff_rows, const unsigned eff_columns, const unsigned start_row, const unsigned start_column, const unsigned end_row, const unsigned end_column, const bool transp, const std::shared_ptr<std::vector<type>> pter){
		this->rows = rows;
		this->columns = columns;
		this->effective_rows = eff_rows;
		this->effective_columns = eff_columns;
		this->start_row = start_row;
		this->start_column = start_column;
		this->transp = transp;
		this->pter = pter;
	}

	/*
	Matrix(const unsigned srw, const unsigned scl, const unsigned rws, const unsigned clms , const bool trsp, const std::shared_ptr<std::vector<type>> ptr){
		pter = ptr;
		srow = scl;
		scolumn = srw;
		rows = clms;
		columns = rws;
		transp = !(trsp);
	}
	*/


  	std::shared_ptr<std::vector<type>> pter;
	bool transp;
	unsigned columns, rows;
	unsigned start_row, start_column, end_row, end_column, effective_rows, effective_columns;
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