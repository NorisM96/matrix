#ifndef _MATRIX_ITERATORS_H_
#define _MATRIX_ITERATORS_H_

#include<iterator>


template<typename T>

class index_col_iterator {
	
    public:
	
	index_col_iterator& operator ++() {
		++row;
		if (row == mat.getRows()) {
			row = 0;
			++col;
		}
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
	
	index_col_iterator(matrix<T> &chs, unsigned r, unsigned c) : 
			ref(chs), row(r), col(c) {}

    private:

    matrix<T>& mat;
	unsigned row, col;
};

template<typename T>
class const_index_col_iterator {
	public:
	
	const_index_col_iterator& operator ++() {
		++row;
		if (row == mat.getRows()) {
			row = 0;
			++col;
		}
		return *this;
	}
	
	const T& operator *() {
		return mat(row, col);
	}
	
	bool operator == (const const_index_col_iterator& rhs) const {
		return row == rhs.row && col == rhs.col;
	}
	bool operator != (const const_index_col_iterator& rhs) const {
		return row != rhs.row || col != rhs.col;
	}
	
	const_index_col_iterator(const matrix<T> & matref, unsigned r, unsigned c) : 
			mat(matref), row(r), col(c) {}

    private:
    
    const matrix<T>& mat;
	unsigned row, col;
};



template<typename T>
class index_row_iterator {
	public:
	
	index_row_iterator& operator ++() {
		++col;
		if (col == mat.getRows()) {
			col  = 0;
			++row;
		}
		return *this;
	}
	
	T& operator *() {
		return mat(row, col);
	}
	
	bool operator == (const index_row_iterator& rhs) const {
		return row == rhs.row && col == rhs.col;
	}
	bool operator != (const index_row_iterator& rhs) const {
		return row != rhs.row || col != rhs.col;
	}
	
	index_row_iterator(matrix<T> &chs, unsigned r, unsigned c) : 
			ref(chs), row(r), col(c) {}
    
    private:

    matrix<T>& mat;
	unsigned row, col;
};

template<typename T>
class const_index_row_iterator {
	
	public:
	
	const_index_row_iterator& operator ++() {
		++col;
		if (col == mat.getColumns()) {
			col = 0;
			++row;
		}
		return *this;
	}
	
	const T& operator *() {
		return mat(row, col);
	}
	
	bool operator == (const const_index_row_iterator& rhs) const{
		return row == rhs.row && col==X.cur_col;
	}
	bool operator != (const const_index_row_iterator& rhs) const {
		return row != rhs.row || col != rhs.col;
	}
	
	const_index_row_iterator(const matrix<T> &chs, unsigned r, unsigned c) : 
			mat(chs), row(r), col(c) {}

    private:

    const matrix<T>& mat;
	unsigned row, col;
};

#endif