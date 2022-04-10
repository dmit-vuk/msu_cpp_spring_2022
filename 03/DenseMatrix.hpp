#ifndef DENSE_MATRIX
#define DENSE_MATRIX

#include <iostream>
#include <cstddef>

class RowDense;
class RowDenseConst;

class DenseMatrix
{
    size_t n_str, n_clm;
    size_t *shift_str;
    double *matrix;
public:
    static double eps;
    
    DenseMatrix(size_t, size_t);
    DenseMatrix(const DenseMatrix &);
    ~DenseMatrix();
    DenseMatrix & operator = (const DenseMatrix &);
    
    static void changeEps(double value);
    double get(size_t, size_t) const;
    void   set(size_t, size_t, double);
    size_t num_rows() const;
    size_t num_columns() const;
    double next_elem_row(size_t, size_t &) const;
    double next_elem_clm(size_t &, size_t) const;
    
    friend bool operator ==(const DenseMatrix & left, const DenseMatrix & right);
    friend bool operator !=(const DenseMatrix & left, const DenseMatrix & right);
    friend DenseMatrix operator +(const DenseMatrix &, const DenseMatrix &);
    friend DenseMatrix operator *(const DenseMatrix &, const DenseMatrix &);
    
    friend DenseMatrix & operator +(DenseMatrix &, size_t);
    friend DenseMatrix & operator +(size_t, DenseMatrix &);
    friend DenseMatrix & operator -(DenseMatrix &, size_t);
    friend DenseMatrix & operator -(size_t, DenseMatrix &);
    
    friend DenseMatrix const & operator +(DenseMatrix const &, size_t);
    friend DenseMatrix const & operator +(size_t, DenseMatrix const &);
    friend DenseMatrix const & operator -(DenseMatrix const &, size_t);
    friend DenseMatrix const & operator -(size_t, DenseMatrix const &);
    
    friend std::ostream& operator<<(std::ostream &os, const DenseMatrix& matrix);
    friend DenseMatrix & operator *=(DenseMatrix &, size_t);
    
    friend RowDense;
    friend RowDenseConst;
    RowDense operator [](size_t);
    RowDense operator *();
    RowDenseConst operator [](size_t) const;
    RowDenseConst operator *() const;
};

class RowDense
{
    DenseMatrix *matrix;
    size_t *clm;
public:
    friend RowDense const & operator +(const RowDense &, size_t);
    friend RowDense const & operator +(size_t, const RowDense &);    
    friend RowDense const & operator -(const RowDense &, size_t);
    friend RowDense const & operator -(size_t, const RowDense &);
    
    double & operator *() const;
    double & operator [](size_t);
    RowDense(DenseMatrix *);
    ~RowDense();
};


class RowDenseConst
{
    const DenseMatrix *matrix;
    size_t *clm;
public:
    friend RowDenseConst const & operator +(const RowDenseConst &, size_t);
    friend RowDenseConst const & operator +(size_t, const RowDenseConst &);
    friend RowDenseConst const & operator -(const RowDenseConst &, size_t);
    friend RowDenseConst const & operator -(size_t, const RowDenseConst &);
    
    double operator *() const;
    double operator [](size_t);
    RowDenseConst(const DenseMatrix *);
    ~RowDenseConst();
};

#endif
