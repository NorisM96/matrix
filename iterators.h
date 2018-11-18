#ifndef MATRIX_ITERATORS_H_
#define MATRIX_ITERATORS_H_

#include"matrix_forward.h"

template<typename T>
class index_col_iterator {
	
    public:
	
	index_col_iterator& operator ++() {
		++row;
		if (row == mat.getRows()) {
			row = 0;
			++column;
		}
		
		return *this;
	}
	
	T& operator *() {
		return mat(row, column);
	}
	
	bool operator == (const index_col_iterator& other) const {
		return row == other.row && column == other.column;
	}

	bool operator != (const index_col_iterator& other) const {
		return row != other.row || column != other.column;
	}
	
	index_col_iterator(Matrix<T> &m, unsigned r, unsigned c) : 
			mat(m), row(r), column(c) {}

	index_col_iterator(MatrixTranspose<T> &m, unsigned r, unsigned c) : 
			mat(m), row(r), column(c) {}

    private:
	Matrix<T>& mat;
	unsigned row, column;    
};

template<typename T>
class const_index_col_iterator {
	
    public:
	
	const_index_col_iterator& operator ++() {
		++row;
		if (row == mat.getRows()) {
			row = 0;
			++column;
		}
		
		return *this;
	}
	
	const T& operator *() {
		return mat(row, column);
	}
	
	bool operator == (const const_index_col_iterator& other) const {
		return row == other.row && column == other.column;
	}

	bool operator != (const const_index_col_iterator& other) const {
		return row != other.row || column != other.column;
	}
	
	const_index_col_iterator(const Matrix<T> &m, unsigned r, unsigned c) : 
			mat(m), row(r), column(c) {}

    private:
	const Matrix<T>& mat;
	unsigned row, column;    
};


/*
template<typename T>
class index_row_iterator {
	
    public:
	
	
	index_col_iterator& operator ++() {
		++row;
		if (row == mat.getRows()) {
			row = 0;
			++col;
		}#include<iterator>

		return *this;
	}
	
	T& operator *() {
		return mat(row, col);
	}
	
	bool operator == (const index_col_iterator& rhs) const {
		return row == rhs.row && col == rhs.col;
	}
	bool operator != (const index_col_iterator& rhs) const {
		return row != rhs.row || col != rhs.col;
	}
	
	
	index_row_iterator(Matrix<T> &mat, unsigned r, unsigned c) : 
			mtrx(mat), row_pos(r), col_pos(c) {}

    private:
	const Matrix<T>& mtrx;
	unsigned row_pos, col_pos;    
};

template<typename T>
class const_index_row_iterator {
	
    public:
	
	
	index_col_iterator& operator ++() {
		++row;
		if (row == mat.getRows()) {
			row = 0;
			++col;
		}#include<iterator>

		return *this;
	}
	
	T& operator *() {
		return mat(row, col);
	}
	
	bool operator == (const index_col_iterator& rhs) const {
		return row == rhs.row && col == rhs.col;
	}
	bool operator != (const index_col_iterator& rhs) const {
		return row != rhs.row || col != rhs.col;
	}
	
	
	const_index_row_iterator(const Matrix<T> &mat, unsigned r, unsigned c) : 
			mtrx(mat), row_pos(r), col_pos(c) {}

    private:
	const Matrix<T>& mtrx;
	unsigned row_pos, col_pos;    
};
*/

#endif