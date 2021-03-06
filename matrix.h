#ifndef MATRIX_H
#define MATRIX_H

#include "iterators.h"
#include <ostream> // std::ostream
#include <vector>
#include <iterator> // std::forward_iterator_tag
#include <memory>
#include <iostream>
#include <cassert>

/**
@file matrix.h
@brief Library of a 2d matrix with methods like requested in the assignment
**/

/**
@class Matrix
@brief A template class that implements a 2D matrix with some matrix operation which return other Matrix objects with the same shared memory
**/
template <typename T>
class matrix {
  public:
	typedef T type;
	typedef typename std::vector<T>::iterator iterator;
	typedef typename std::vector<T>::const_iterator const_iterator;

	typedef index_row_iterator<T> row_iterator;
	typedef const_index_row_iterator<T> const_row_iterator;

	typedef index_col_iterator<T> column_iterator;
	typedef const_index_col_iterator<T> const_column_iterator;

	/**
  	@brief Default Constructor (Must have)
  	Used when creating an Empty matrix(Useful to array constructors) 
  	**/
	matrix() : columns(0), rows(0), start_row(0), start_column(0), effective_columns(0), effective_rows(0), transp(false), pter(nullptr), diag(false), diagmatr(false), from_diag(false), from_subcovector(false){}

	/**
 	 @brief Optional Constructor
  	 Used for creating a matrix of a certain dimension, filled with zero values(Default constructor of type T)
  	**/
	explicit matrix(const unsigned rows , const unsigned columns)  {
		this->columns = columns;
		this->rows = rows;
		effective_rows = rows;
		effective_columns = columns;
		start_row = 0;
		start_column = 0;
		diagmatr = false;
		transp = false;
		diag = false;
		from_diag = false;
		from_subcovector = false;
		pter = std::make_shared<std::vector<T>>(columns * rows);
		for (type c : *pter)
			c = type();
	}

	/**
 	 @brief Optional Constructor two
  	 Used for creating a matrix of a certain dimension, filled with a value val
	@param rows number of rows of the matrix
  	@param columns number of columns of the matrix
	@param val value to fill the matrix
  	**/
	explicit matrix(const unsigned rows, const unsigned columns, const type &val) {
		this->columns = columns;
		this->rows = rows;
		effective_rows = rows;
		effective_columns = columns;
		start_row = 0;
		start_column = 0;
		transp = false;
		diag = false;
		diagmatr = false;
		from_diag = false;
		from_subcovector = false;
		pter = std::make_shared<std::vector<T>>(columns * rows);
		for(int i = 0; i <(columns * rows); i++){
			pter->operator[](i) = val;
		}
	}
	

	/**
 	 @brief Copy Constructor (MUST HAVE)
  	 It creates a deep copy of a given matrix
	@param other lvalue reference to a matrix
  	**/
	matrix(const matrix<type> &other){
		columns = other.columns;
		rows = other.rows;
		effective_rows = other.effective_rows;
		effective_columns = other.effective_columns;
		start_row = other.start_row;
		start_column = other.start_column;
		transp = false;
		diag = false;
		diagmatr = false;
		from_diag = false;
		from_subcovector = false;
		pter = std::make_shared<std::vector<T>>(columns * rows);
		for (unsigned r = 0; r < getRows(); r++){
			for (unsigned c = 0; c < getColumns(); c++)
				this->operator()(r, c) = other(r, c);
		}
	}

	/**
 	 @brief Move Constructor (MUST HAVE)
  	 It "moves" the content of a matrix into another(Never called in this project thanks to RVO)
	@param other rvalue reference to a matrix
  	**/
	matrix(matrix<T> &&other){
		columns = other.columns;
		rows = other.rows;
		effective_rows = other.effective_rows;
		effective_columns = other.effective_columns;
		start_row = other.start_row;
		start_column = other.start_column;
		diag = other.diag;
		from_diag = other.from_diag;
		diagmatr = other.diagmatr;
		from_subcovector = other.from_subcovector;
		pter = other.pter;
		other.pter = nullptr;
	}

	/**
 	 @brief Move Assignment (MUST HAVE)
  	 It "moves" the content of a matrix rhs into the left side of the assignment(Never called in this thanks to RVO)
	@param other rvalue reference to the rhs matrix
  	**/
	matrix<type> &operator=(matrix<type> &&other) {
		columns = other.columns;
		rows = other.rows;
		effective_rows = other.effective_rows;
		effective_columns = other.effective_columns;
		start_row = other.start_row;
		start_column = other.start_column;
		transp = other.transp;
		diag = other.diag;
		diagmatr = other.diagmatr;
		from_diag = other.from_diag;
		from_subcovector = other.from_subcovector;
		pter = other.pter;	//maybe private method to do this
		other.pter = nullptr; //same problem as above
	}

	/**
 	 @brief Assignment Operator (MUST HAVE)
  	 It creates a deep copy of a the rhs matrix
	@param other lvalue reference to the rhs matrix
  	**/
	matrix &operator=(const matrix<type> &other){
		if (this != &other){
			matrix<T> tmp(other);
			this->swap(tmp);
		}
		return *this;
	}

	/**
 	 @brief Swap method (MUST HAVE)
  	 It swaps method from a matrix to another
	@param other lvalue reference to a matrix
  	**/
	void swap(matrix<T> &other) {
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
		std::swap(other.from_diag, this->from_diag);
		std::swap(other.from_subcovector, this->from_subcovector);
	}

	

	/**
 	@brief Operator() (MUST HAVE)
	This operator is very important, because it's the extractor of the elements of a given matrix.
	Any methods that wants to access a matrix element must use this.
	Depending on the "type" of matrix we want to access its elements from (given by some flags), this operator will behave differently(diagmatrix no because is always constant)
	The elements taken with this method can be read and overwritten
	@param row row of the element that needs to be taken
	@param column column of the element that needs to be taken
	@return lvalue reference of the retrieved element
  	**/
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

	/**
 	@brief const Operator() (MUST HAVE)
	Same as operator(), but the elements extracted with this can only be read and a diagonal matrix(which is always const by the way) must always use this.
	@param row row of the element that needs to be taken
	@param column column of the element that needs to be taken
	@return const lvalue reference of the retrieved element
  	**/
	const type &operator()(unsigned row, unsigned column) const {
		if(diagmatr == true){
			if(row != column)
				return zero;
			else{
				if(from_diag)
					return pter->operator[]((row + start_row) * (columns) + (row + start_column));
				else if(from_subcovector)
					return pter->operator[]((row*columns) + (start_row * columns + start_column));
				else
					return pter->operator[](row + (start_row * columns + start_column));
			}
		}
		else if((diag == true) && !(transp)){
			assert(column == 0);
			return pter->operator[]((row + start_row) * (columns) + (row + start_column));
		}
		else if((diag == true) && (transp == true))
			return pter->operator[]((column + start_column) * (rows) + column + start_row);
		else if((!diag && (transp == true)))
			return pter->operator[]((column + start_column) * (rows) + (row + start_row));
		else
			return pter->operator[]((row + start_row) * (columns) + column + start_column);
	}

	/**
 	@brief submatrix method (REQUESTED)
	It returns a submatrix of the matrix which called the method(using a protected constructor).
	@param start_row index of the row from which the submatrix starts
	@param start_column index of the column from which the submatrix starts
	@param end_row index of the row to which the submatrix ends
	@param end_column index of the column to which the submatrix ends
	@return a matrix which is a logical submatrix of the calling one 
  	**/
	matrix subMatrix(const unsigned start_row, const unsigned start_column, const unsigned end_row,const unsigned end_column) {
		const unsigned new_eff_rows = end_row - start_row + 1;
		const unsigned new_eff_columns = end_column - start_column + 1;
		return  matrix<type>(rows, columns, new_eff_rows, new_eff_columns, (this->start_row + start_row) ,(this->start_column + start_column), transp, diag, pter);
	}

	/**
 	@brief submatrix const method (REQUESTED)
	It returns a const submatrix of the const matrix which called the method(using a protected constructor) w.
	@param start_row index of the row from which the submatrix starts
	@param start_column index of the column from which the submatrix starts
	@param end_row index of the row to which the submatrix ends
	@param end_column index of the column to which the submatrix ends
	@return a matrix which is a logical submatrix of the calling one 
  	**/
	const matrix subMatrix(const unsigned start_row, const unsigned start_column, const unsigned end_row,const unsigned end_column) const{
		const unsigned new_eff_rows = end_row - start_row + 1;
		const unsigned new_eff_columns = end_column - start_column + 1;
		return matrix<type>(rows, columns, new_eff_rows, new_eff_columns, (this->start_row + start_row) ,(this->start_column + start_column), transp, diag, pter);
	}

	/**
 	@brief transpose method (REQUESTED)
	It returns a transpose matrix of the matrix which called the method(using a protected constructor).
	@return a matrix which is a logical tranpose matrix of the calling one  
  	**/
	matrix transpose(){
		const unsigned new_rows = effective_columns;
		const unsigned new_columns = effective_rows;
		const unsigned new_start_row = start_column;
		const unsigned new_start_column = start_row;
		const bool new_transp = !transp; 

		return matrix<type>(columns, rows, new_rows, new_columns, new_start_row, new_start_column, new_transp,diag, pter);
	}

	/**
 	@brief transpose const method (REQUESTED)
	It returns a const transpose matrix of the matrix which called the method(using a protected constructor).
	@return a matrix which is a logical tranpose matrix of the calling one  
  	**/
	const matrix transpose() const{
		const unsigned new_rows = effective_columns;
		const unsigned new_columns = effective_rows;
		const unsigned new_start_row = start_column;
		const unsigned new_start_column = start_row;
		const bool new_transp = !transp; 

		return matrix<type>(columns, rows, new_rows, new_columns, new_start_row, new_start_column, new_transp,diag, pter);
	}
	
	/**
 	@brief diagonal method (REQUESTED)
	It returns a "logical" extracted vector which corresponds to the diagonal of the calling matrix.
	@return a matrix which is a logical built diagonal vector of the starting matrix  
  	**/
	matrix diagonal(){
		if(!transp)
			return matrix<type>(rows, columns, std::min(effective_rows, effective_columns), 1, start_row, start_column , false, true, pter);
		else
			return matrix<type>(columns, rows, std::min(effective_rows, effective_columns), 1, start_row, start_column , false, true, pter);
	}

	/**
 	@brief diagonal const method (REQUESTED)
	It returns a "logical" extracted const vector which corresponds to the diagonal of the calling matrix.
	@return a matrix which is a logical built diagonal vector of the starting matrix  
  	**/
	const matrix diagonal() const{
		if(!transp)
			return matrix<type>(rows, columns, std::min(effective_rows, effective_columns), 1, start_row, start_column , false, true, pter);
		else
			return matrix<type>(columns, rows, std::min(effective_rows, effective_columns), 1, start_row, start_column , false, true, pter);
	}

	/**
 	@brief diagonalmatrix method (REQUESTED)
	It returns a "logical" const diagonal matrix from the calling matrix(which is a vector or covector).
	ATTENTION!!!!!!!!
	This method(alongside every method with const matrix as a return type) is kind of tricky.
	If the variable that takes the object(the lhs of an assignment or the copy constructed on) is a const matrix<type> then no problem, but if it is a auto type or matrix<type> then 
	the RVO doesen't care about it and it will move THE MATRIX<TYPE> object, which will result in a mutable diagonalMatrix.
	The fully explanation of the issue will be written on the relation file of our project, please read it.
	@return a matrix which is a logical built diagonal matrix of the starting vector/covector 
  	**/
	const matrix<type> diagonalMatrix() const {
		assert(effective_columns == 1 || effective_rows == 1);
		if(effective_columns == 1 && columns != 1)
			return matrix<type>(rows, columns, effective_rows, effective_columns, start_row, start_column, true, diag, true, pter);
		else
			return matrix<type>(rows, columns, effective_rows, effective_columns, start_row, start_column, true, diag, false, pter);
	}

	/**
 	@brief Destructor(MUST HAVE)
	When a matrix object goes out of scope, this is automatically called, freeing the memory occupied by that same matrix.The vector contents will be deleted in case it goes out of scope (handled by shared_ptr) 
  	**/
	~matrix(){
		columns = 0;
		rows = 0;
		start_row = 0;
		start_column = 0;
		effective_columns = 0;
		effective_rows = 0;
	}
	

	/**
 	@brief getRows method
	It return the number of effective rows which the current matrix have
	@return  effective rows of the matrix
  	**/
	unsigned getRows() const {
		return effective_rows;
	}

	/**
 	@brief getColumns method
	It return the number of effective columns which the current matrix have
	@return  effective columns of the matrix
  	**/
	unsigned getColumns() const {
		return effective_columns;
	}

	/**
 	@brief begin method
	Returns the first iterator used to iterate over the whole vector object
	@return iterator to the first element contained in the vector
  	**/
	iterator begin() { return pter->begin();}
	
 	/**
 	@brief end method
	Returns the last iterator used to iterate over the whole vector object
	@return iterator that represent the end(logic) of the vector
  	**/
	iterator end() { return pter->end(); }
	
	/**
 	@brief begin const method
	Returns the first iterator used to iterate over the whole vector object, but the element that the iterator points to is read-only
	@return const iterator to the first element contained in the vector
  	**/
	const_iterator begin() const { return pter->begin(); }
	
	/**
 	@brief end const method
	Returns the last iterator used to iterate over the whole vector object
	@return const iterator to the end(logic) of the vector
  	**/
	const_iterator end() const { return pter->end(); }

	/**
 	@brief row_begin method
	Returns the first iterator used to iterate over a single row given as a parameter
	@param i row which the iteration will be perfomed on
	@return iterator to the first element contained in the vector
  	**/
	row_iterator row_begin(unsigned i) { return row_iterator(*this, i, 0); }   
	
	/**
 	@brief row_end method
	Returns the last iterator used to iterate over a single row given as a parameter
	@param i row which the iteration will be perfomed on
	@return iterator that represent the end(logic) of the row
  	**/
	row_iterator row_end(unsigned i) { return row_iterator(*this, i + 1, 0); } 
	
	/**
 	@brief row_begin const method
	Returns the first iterator used to iterate over a single row given as a parameter, but the element that is pointed by the iterator is immutable
	@param i row which the iteration will be perfomed on
	@return iterator to the first element contained in the vector
  	**/
	const_row_iterator row_begin(unsigned i) const { return const_row_iterator(*this, i, 0); }
	
	/**
 	@brief row_end const method
	Returns the last iterator used to iterate over a single row given as a parameter
	@param i row which the iteration will be perfomed on
	@return iterator to the end(logic) of the row
  	**/
	const_row_iterator row_end(unsigned i) const { return const_row_iterator(*this, i + 1, 0); }

	/**
 	@brief row_begin method
	Returns the first iterator used to iterate over the current considered matrix by rows
	@return iterator to the first element of the current matrix
  	**/
	row_iterator row_begin() { return row_iterator(*this, 0, 0); }   
	
	/**
 	@brief row_end method
	Returns the last iterator used to iterate over the current considered matrix by rows
	@return iterator to the end(logic) of the current matrix
  	**/
	row_iterator row_end() { return row_iterator(*this, effective_rows, 0); } 
	
	/**
 	@brief row_begin const method
	Returns the first iterator used to iterate over the current considered matrix by rows, but the element pointed cannot be modified(const)
	@return const_row_iterator to the first element of the current matrix
  	**/
	const_row_iterator row_begin() const { return const_row_iterator(*this, 0, 0); }
	
	/**
 	@brief row_end const method
	Returns the last iterator used to iterate over the current considered matrix by rows, but the element pointed cannot be modified(const)
	@return const_row_iterator that represent the logic end of the current matrix
  	**/
	const_row_iterator row_end() const { return const_row_iterator(*this, effective_rows, 0); }

	/**
 	@brief col_begin method
	Returns the first iterator used to iterate  over a single column
	@param i column that needs to be iterated
	@return column_iterator of the first element of the column
  	**/
	column_iterator col_begin(unsigned i) { return column_iterator(*this, 0, i); }
	
	/**
 	@brief col_end method
	Returns the last iterator used to iterate over a single column
	@param i column that needs to be iterated
	@return column_iterator representing the logic end of the column
  	**/
	column_iterator col_end(unsigned i) { return column_iterator(*this, 0, i + 1); }

	/**
 	@brief col_begin const method
	Returns the first iterator used to iterate  over a single column, whose element pointed cannot be modified
	@param i column that needs to be iterated
	@return const_column_iterator of the first element of the column
  	**/
	const_column_iterator col_begin(unsigned i) const { return const_column_iterator(*this, 0, i); }

	/**
 	@brief col_end const method
	Returns the last iterator used to iterate  over a single column
	@param i column that needs to be iterated
	@return const_column_iterator of the logic end of the column
  	**/
	const_column_iterator col_end(unsigned i) const { return const_column_iterator(*this, 0, i + 1); }
	
	/**
 	@brief col_begin method
	Returns the first iterator to the first element of current matrix, used to iterate by column 
	@return column_iterator of the first element of the current matrix
  	**/
	column_iterator col_begin() {return column_iterator(*this, 0, 0); }
	
	/**
 	@brief col_end method
	Returns the iterator to the end  of current matrix, used to iterate by column 
	@return column_iterator of the logic end of the current matrix
  	**/
	column_iterator col_end() {return column_iterator(*this, 0, effective_columns); }
	
	/**
 	@brief col_begin const method
	Returns the first iterator to the first element of current matrix, used to iterate by column, that cannot modify the elements
	@return const_column_iterator of the first element of the current matrix
  	**/
	const_column_iterator col_begin() const {return const_column_iterator(*this, 0, 0); }
	
	/**
 	@brief col_end const method
	Returns the last iterator current matrix, used to iterate by column
	@return const_column_iterator of logic end of the current matrix
  	**/
	const_column_iterator col_end() const {return const_column_iterator(*this, 0, effective_columns); }
	
    private:

	//Constructor used by matrix operation transpose,submatrix and diagonal
	matrix(const unsigned rows, const unsigned columns, const unsigned eff_rows, const unsigned eff_columns, const unsigned start_row, const unsigned start_column, const bool transp, const bool diag, const std::shared_ptr<std::vector<type>> pter){
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
		this->from_subcovector = false;
	}

	//Constructor used by matrix operation diagonalmatrix
	matrix(const unsigned rows, const unsigned columns, const unsigned effective_rows, const unsigned effective_columns, const unsigned start_row, const unsigned start_column, const bool diagmatr, const bool from_diag, const bool from_subcovector, const std::shared_ptr<std::vector<type>> pter){
		this->diagmatr = diagmatr;
		this->rows = rows;
		this->columns = columns;
		this->effective_rows = std::max(effective_rows, effective_columns);
		this->effective_columns = std::max(effective_rows, effective_columns);
		this->transp = false;
		this->diag = false;
		this->start_row = start_row;
		this->start_column = start_column;
		this->pter = pter;
		this->from_diag = from_diag;
		this->from_subcovector = from_subcovector;

	}


  	std::shared_ptr<std::vector<type>> pter; //shared_ptr to share the memory between the object
	bool transp, diag, diagmatr, from_diag, from_subcovector; //Flags to identify the type of matrix the instance represents
	unsigned columns, rows;  //Rows and column of the WHOLE matrix(not eventually modified by submatrix/diagonal method but by diagonalmatrix and transpose of course yes)
	unsigned start_row, start_column, effective_rows, effective_columns; //Parameters needed to define the current submatrix dimension
	const type zero = type(); //Logic zero that has to be returned when accessing a non-diagonal element in a diagonal matrix
};


/**
Overload of stream operator that permits printing a matrix object

@param os output stream
@param ma matrix to stamp
@return lvalue reference to output stream
*/
template <typename T>
std::ostream &operator<<(std::ostream &os, const matrix<T> &ma)
{
	for (unsigned r = 0; r < ma.getRows(); r++){
		for (unsigned c = 0; c < ma.getColumns(); c++){
			os << "[" << ma(r, c) << "] ";
		}
		os << std::endl;
	}
	return os;
}


#endif