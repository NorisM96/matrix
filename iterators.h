#ifndef _MATRIX_ITERATORS_H_
#define _MATRIX_ITERATORS_H_

#include"matrix_forward.h"

template<typename T>
class index_col_iterator {
	
    public:
	
	/*!TODO
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
	*/
	
	index_col_iterator(matrix<T> &mat, unsigned r, unsigned c) : 
			mtrx(mat), row_pos(r), col_pos(c) {}

    private:
	const matrix<T>& mtrx;
	unsigned row_pos, col_pos;    
};

template<typename T>
class const_index_col_iterator {
	
    public:
	
	/*!TODO
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
	*/
	
	const_index_col_iterator(const matrix<T> &mat, unsigned r, unsigned c) : 
			mtrx(mat), row_pos(r), col_pos(c) {}

    private:
	const matrix<T>& mtrx;
	unsigned row_pos, col_pos;    
};

template<typename T>
class index_row_iterator {
	
    public:
	
	/*!TODO
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
	*/
	
	index_row_iterator(matrix<T> &mat, unsigned r, unsigned c) : 
			mtrx(mat), row_pos(r), col_pos(c) {}

    private:
	const matrix<T>& mtrx;
	unsigned row_pos, col_pos;    
};

template<typename T>
class const_index_row_iterator {
	
    public:
	
	/*!TODO
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
	*/
	
	const_index_row_iterator(const matrix<T> &mat, unsigned r, unsigned c) : 
			mtrx(mat), row_pos(r), col_pos(c) {}

    private:
	const matrix<T>& mtrx;
	unsigned row_pos, col_pos;    
};

#endif