#ifndef MATRIX_H
#define MATRIX_H

#include "iterators.h"
#include <ostream> // std::ostream
#include <vector>
#include <iterator> // std::forward_iterator_tag
#include <memory>
#include <iostream>
#include <cassert>


template <typename T>
class Matrix
{
  public:
	typedef T type;
	typedef typename std::vector<T>::iterator iterator;
	typedef typename std::vector<T>::const_iterator const_iterator;

	typedef index_row_iterator<T> row_iterator;
	typedef const_index_row_iterator<T> const_row_iterator;

	typedef index_col_iterator<T> column_iterator;
	typedef const_index_col_iterator<T> const_column_iterator;

	//DEFAULT CONSTRUCTOR
	Matrix() : columns(0), rows(0), start_row(0), start_column(0), transp(false), pter(nullptr), diag(false){}

	//CONSTRUCTOR WHICH CONSTRUCT A Matrix FILLED WITH ZEROES ON CREATION
	explicit Matrix(const unsigned rows , const unsigned columns)  {
		this->columns = columns;
		this->rows = rows;
		effective_rows = rows;
		effective_columns = columns;
		start_row = 0;
		start_column = 0;
		diagmatr = false;
		transp = false;
		diag = false;
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
		transp = false;
		diag = false;
		diagmatr = false;
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
		transp = other.transp;
		diag = other.diag;
		diagmatr = other.diagmatr;
		pter = std::make_shared<std::vector<T>>(columns * rows);
		for (unsigned i = 0; i < (columns * rows); i++)
			pter->operator[](i) = other.pter->operator[](i);
		std::cout << "COPY CONSTRUCTOR INVOKED" <<std::endl;
	}

	//MOVE COSTRUCTOR
/*	Matrix(Matrix<T> &&other){
		std::cout << "MOVE CONSTUCTOR INVOKED" <<std::endl;
		columns = other.columns;
		rows = other.rows;
		effective_rows = other.effective_rows;
		effective_columns = other.effective_columns;
		start_row = other.start_row;
		start_column = other.start_column;
		diag = other.diag;
		pter = other.pter;	//maybe private method to do this
		other.pter = nullptr; //same problem as above, but maybe with same class type there is no need
	}

	//MOVE ASSIGNMENT OPERATOR
	Matrix<type> &operator=(Matrix<type> &&other) {
		std::cout<<"MOVE ASSIGNMENT INVOKED" << std::endl;
		columns = other.columns;
		rows = other.rows;
		effective_rows = other.effective_rows;
		effective_columns = other.effective_columns;
		start_row = other.start_row;
		start_column = other.start_column;
		transp = other.transp;
		diag = other.diag;
		pter = other.pter;	//maybe private method to do this
		other.pter = nullptr; //same problem as above
	}
*/
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
		std::swap(other.transp, this->transp);
		std::swap(other.transp, this->diag);
		std::swap(other.diagmatr, this->diagmatr);
	}

	

	//OPERATOR () TO DIRECTLY ACCESS THE ELEMENTS
	type &operator()(unsigned row, unsigned column) {
		if((diag == true) && !transp){
			assert(column == 0);
			return pter->operator[]((row + start_row) * (columns) + (row + start_column));
		}
		else if((diag == true) && (transp == true)){
			assert(row == 0);
			return pter->operator[]((column + start_column) * (rows) + (column + start_row));
		}
		else if((!diag && (transp == true)))
			return pter->operator[]((column + start_column) * (rows) + (row + start_row));
		else
			return pter->operator[]((row+start_row) * (columns) + (column + start_column));
	}


	const type &operator()(unsigned row, unsigned column) const {
		if(diagmatr == true){
			if(row != column)
				return zero;
			else{
				if(from_diag)
					return pter->operator[]((row + start_row) * (columns) + (row + start_column));
				else
					return pter->operator[](row + (start_row * columns + start_column));
			}
		}
		else if((diag == true) && !(transp)){
			assert(column == 0);
			return pter->operator[]((row + start_row) * (columns) + (row + start_column));
		}
		else if((diag == true) && (transp == true)){
			return pter->operator[]((column + start_column) * (rows) + column + start_row);
		}
		else if((!diag && (transp == true)))
			return pter->operator[]((column + start_column) * (rows) + (row + start_row));
		else
			return pter->operator[]((row + start_row) * (columns) + column + start_column);
	}

	//subMatrix METHOD
	Matrix subMatrix(const unsigned start_row, const unsigned start_column, const unsigned end_row,const unsigned end_column) {
		const unsigned new_eff_rows = end_row - start_row + 1;
		const unsigned new_eff_columns = end_column - start_column + 1;
		return Matrix<type>(rows, columns, new_eff_rows, new_eff_columns, (this->start_row + start_row) ,(this->start_column + start_column), transp, diag, pter);
	}

	//TRANSPOSE METHOD
	Matrix transpose() const{
		const unsigned new_rows = effective_columns;
		const unsigned new_columns = effective_rows;
		const unsigned new_start_row = start_column;
		const unsigned new_start_column = start_row;
		const bool new_transp = !transp; 

		return Matrix<type>(columns, rows, new_rows, new_columns, new_start_row, new_start_column, new_transp,diag, pter);
	}
	//DIAGONAL METHOD(MUST RETURN A VECTOR WITH ELEMENT = TO DIAGONAL OF THE Matrix)
	Matrix diagonal() const {
		if(!transp)
			return Matrix<type>(rows, columns, std::min(effective_rows, effective_columns), 1, start_row, start_column , false, true, pter);
		else
			return Matrix<type>(columns, rows, std::min(effective_rows, effective_columns), 1, start_row, start_column , false, true, pter);
	}

	//DIAGONAL Matrix METHOD(MUST BE USED ONLY BY VECTOR CLASS AND IT RETURNS A DIAGONAL Matrix WHOSE ELEMENTS BELONGS TO THE VECTOR )
	const Matrix<type> diagonalMatrix() const {
		assert(effective_columns == 1 || effective_rows == 1);
		return Matrix<type>(*this, true, diag);
	}

	//DESTRUCTOR
	~Matrix(){
		columns = 0;
		rows = 0;
		start_row = 0;
		start_column = 0;
		effective_columns = 0;
		effective_rows = 0;
		std::vector<type>().swap(*pter);
	}
	

	//GET METHOD FOR ROWS PARAMETER
	unsigned getRows() const {
		return effective_rows;
	}

	//GET METHOD FOR COLUMNS PARAMETER
	unsigned getColumns() const {
		return effective_columns;
	}

	//iterators that start from the beginning of the vector and iterate on it
	iterator begin() { return pter->begin();}
	iterator end() { return pter->end(); }
	const_iterator begin() const { return pter->begin(); }
	const_iterator end() const { return pter->end(); }

	//iterators that start from the beginning of the matrix and iterate on the whole 
	//matrix by rows
	row_iterator row_begin(unsigned i) { return row_iterator(*this, i, 0); }   
	row_iterator row_end(unsigned i) { return row_iterator(*this, i + 1, 0); } 
	const_row_iterator row_begin(unsigned i) const { return row_iterator(*this, i, 0); }
	const_row_iterator row_end(unsigned i) const { return row_iterator(*this, i + 1, 0); }

	//iterators that iterate on a single or multiple columns 
	row_iterator row_begin() { return row_iterator(*this, 0, 0); }   
	row_iterator row_end() { return row_iterator(*this, effective_rows, 0); } 
	const_row_iterator row_begin() const { return row_iterator(*this, 0, 0); }
	const_row_iterator row_end() const { return row_iterator(*this, effective_rows, 0); }

	//iterators that iterate on a single or multiple columns 
	column_iterator col_begin(unsigned i) { return column_iterator(*this, 0, i); }
	column_iterator col_end(unsigned i) { return column_iterator(*this, 0, i + 1); } //questa potrebbe andare come no, il tempo ce lo dirà
	const_column_iterator col_begin(unsigned i) const { return column_iterator(*this, 0, i); }
	column_iterator col_end(unsigned i) const { return column_iterator(*this, 0, i + 1); }
	
	//iterators that start from the beginning of the matrix and iterate on the whole 
	//matrix by columns
	column_iterator col_begin() {return column_iterator(*this, 0, 0); }
	column_iterator col_end() {return column_iterator(*this, 0, effective_columns); }
	const_column_iterator col_begin() const {return column_iterator(*this, 0, 0); }
	const_column_iterator col_end() const {return column_iterator(*this, 0, effective_columns); }
	
	//KILL ME PLEASE , OKAY
    protected:

	Matrix(const unsigned rows, const unsigned columns, const unsigned eff_rows, const unsigned eff_columns, const unsigned start_row, const unsigned start_column, const bool transp, const bool diag, const std::shared_ptr<std::vector<type>> pter){
		this->rows = rows;
		this->columns = columns;
		this->effective_rows = eff_rows;
		this->effective_columns = eff_columns;
		this->start_row = start_row;
		this->start_column = start_column;
		this->transp = transp;
		this->diag = diag;
		this->pter = pter;
		this->diagmatr = false;
		this->from_diag = false;
	}

	Matrix(const Matrix<type> &vec, const bool diagmatr, const bool from_diag){
		this->diagmatr = diagmatr;
		rows = vec.rows;
		columns = vec.columns;
		effective_rows = std::max(vec.effective_rows, vec.effective_columns);
		effective_columns = std::max(vec.effective_rows, vec.effective_columns);
		transp = false;
		diag = false;
		start_row = vec.start_row;
		start_column = vec.start_column;
		pter = vec.pter;
		this->from_diag = from_diag;
	}


  	std::shared_ptr<std::vector<type>> pter;
	bool transp, diag, diagmatr, from_diag;
	unsigned columns, rows;
	unsigned start_row, start_column, effective_rows, effective_columns;
	const type zero = type();
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