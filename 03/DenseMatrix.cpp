#include <iostream>
#include "DenseMatrix.hpp"

using std::cout;
using std::endl;

double DenseMatrix::eps = 0.00001;

void DenseMatrix::changeEps(double value)
{
    DenseMatrix::eps = value;
}

DenseMatrix::DenseMatrix(size_t m, size_t n)
{
    n_str = m;
    n_clm = n;
    shift_str = new size_t (0);
    matrix = new double [m * n];
    for(size_t i = 0; i < n_str; i++)
        for(size_t j = 0; j < n_clm; j++)
            matrix[i*n_clm + j] = 0;
}

DenseMatrix::DenseMatrix(const DenseMatrix & mat)
{
    n_str = mat.n_str;
    n_clm = mat.n_clm;
    shift_str = new size_t (0);
    matrix = new double [n_str * n_clm];
    for(size_t i = 0; i < n_str; i++)
        for(size_t j = 0; j < n_clm; j++)
            matrix[i*n_clm + j] = mat.matrix[i*n_clm + j];
}

DenseMatrix::~DenseMatrix()
{
    delete [] matrix;
    delete shift_str;
}

size_t DenseMatrix::num_rows() const
{
    return n_str;
}

size_t DenseMatrix::num_columns() const
{
    return n_clm;
}

void DenseMatrix::set(size_t str, size_t clm, double val)
{
    if (str >= n_str || clm >= n_clm)
        throw "Error!!! There is out of bounds matrix";
    
    matrix[str*n_clm + clm] = val;
}

double DenseMatrix::get(size_t str, size_t clm) const
{
    if (str >= n_str || clm >= n_clm)
        throw "Error!!! There is out of bounds matrix";
    return matrix[str*n_clm + clm];
}

double DenseMatrix::next_elem_row(size_t str, size_t & clm) const
{
    ++clm;
    while (clm < n_clm && abs(matrix[str*n_clm + clm]) < eps)
        ++clm;
    if (clm < n_clm)
        return matrix[str*n_clm + clm];
    return 0;
}

double DenseMatrix::next_elem_clm(size_t & str, size_t clm) const
{
    ++str;
    while (str < n_str && abs(matrix[str*n_clm + clm]) < eps)
        ++str;
    if (str < n_str)
        return matrix[str*n_clm + clm];
    return 0;
}

DenseMatrix & DenseMatrix::operator =(const DenseMatrix & mat)
{
    if (this == &mat)
        return *this;
    if (n_str != mat.n_str || n_clm != mat.n_clm)
        throw "Error!!! It's impossible to assign matrices of different sizes";
    for (size_t i = 0; i < n_str; i++)
        for (size_t j = 0; j < n_clm; j++)
            matrix[i*n_clm + j] = mat.matrix[i*n_clm + j];
    return *this;
}

bool operator ==(const DenseMatrix & mat1, const DenseMatrix & mat2)
{
    if (mat1.n_str != mat2.n_str || mat1.n_clm != mat2.n_clm)
        throw "Error!!! It's impossible to compare matrices of different sizes";
    for (size_t i = 0; i < mat1.n_str; i++)
        for (size_t j = 0; j < mat1.n_clm; j++)
            if (std::abs(mat1.matrix[i*mat1.n_clm + j] -
                        mat2.matrix[i*mat2.n_clm + j] ) > mat1.eps
                )
            return false;
    return true;
}

bool operator !=(const DenseMatrix & mat1, const DenseMatrix & mat2)
{
    return !(mat1 == mat2);
}

DenseMatrix operator +(const DenseMatrix & mat1, const DenseMatrix & mat2)
{
    if (mat1.n_str != mat2.n_str || mat1.n_clm != mat2.n_clm)
        throw "It's impossible to add matrices of a given sizes";
    DenseMatrix temp(mat1.n_str, mat2.n_clm);
    for (size_t i = 0; i < mat1.n_str; i++)
        for (size_t j = 0; j < mat1.n_clm; j++)
            temp.matrix[i*temp.n_clm + j] = mat1.matrix[i*mat1.n_clm + j] + 
                                            mat2.matrix[i*mat2.n_clm + j];
    return temp;
}

DenseMatrix operator *(const DenseMatrix & mat1, const DenseMatrix & mat2)
{
    if (mat1.n_clm != mat2.n_str)
        throw "It's impossible to multiply matrices of a given sizes";

    DenseMatrix temp(mat1.n_str, mat2.n_clm);
    for (size_t i = 0; i < temp.n_str; i++)
        for (size_t j = 0; j < temp.n_clm; j++)
            for (size_t k = 0; k < mat1.n_clm; k++)
                temp.matrix[i*temp.n_clm + j] += mat1.matrix[i*mat1.n_clm + k] *
                                            mat2.matrix[k*mat2.n_clm + j];
    
    return temp;
}

// адресная арифметика
DenseMatrix & operator +(DenseMatrix & mat, size_t str)
{
    mat.shift_str[0] += str;
    return mat;
}

DenseMatrix & operator +(size_t str, DenseMatrix & mat)
{
    mat.shift_str[0] += str;
    return mat;
}

DenseMatrix & operator -(DenseMatrix & mat, size_t str)
{
    mat.shift_str[0] -= str;
    return mat;
}

DenseMatrix & operator -(size_t str, DenseMatrix & mat)
{
    mat.shift_str[0] -= str;
    return mat;
}

DenseMatrix const & operator +(DenseMatrix const & mat, size_t str)
{
    mat.shift_str[0] += str;
    return mat;
}

DenseMatrix const & operator +(size_t str, DenseMatrix const & mat)
{
    mat.shift_str[0] += str;
    return mat;
}

DenseMatrix const & operator -(DenseMatrix const & mat, size_t str)
{
    mat.shift_str[0] -= str;
    return mat;
}

DenseMatrix const & operator -(size_t str, DenseMatrix const & mat)
{
    mat.shift_str[0] -= str;
    return mat;
}

RowDense DenseMatrix::operator [](size_t idx)
{
    if (idx >= n_str)
        throw "Error!!! There is out of bounds matrix";
    *shift_str = idx;
    RowDense row(this);
    return row;
}

RowDenseConst DenseMatrix::operator [](size_t idx) const
{
    if (idx >= n_str)
        throw "Error!!! There is out of bounds matrix";
    *shift_str = idx;
    RowDenseConst row(this);
    return row;
}

RowDense DenseMatrix::operator *()
{
    RowDense row(this);
    return row;
}

RowDenseConst DenseMatrix::operator *() const
{
    RowDenseConst row(this);
    return row;
}

//RowDense
RowDense::RowDense(DenseMatrix *mat)
{
    clm = new size_t(0);
    matrix = mat;
}

RowDense::~RowDense()
{
    delete clm;
}

RowDense const & operator +(const RowDense & row, size_t idx)
{
    row.clm[0] += idx;
    return row;
}

RowDense const & operator +(size_t idx, const RowDense & row)
{
    row.clm[0] += idx;
    return row;
}

RowDense const & operator -(const RowDense & row, size_t idx)
{
    row.clm[0] -= idx;
    return row;
}

RowDense const & operator -(size_t idx, const RowDense & row)
{
    row.clm[0] -= idx;
    return row;
}

double & RowDense::operator *() const
{
    size_t str = matrix->shift_str[0];
    matrix->shift_str[0] = 0;
    if (str >= matrix->n_str || *clm >= matrix->n_clm)
        throw "Error!!! There is out of bounds matrix";
    return matrix->matrix[str*matrix->n_clm + *clm];
}

double & RowDense::operator [](size_t idx)
{
    size_t str = matrix->shift_str[0];
    matrix->shift_str[0] = 0;
    if (str >= matrix->n_str || idx >= matrix->n_clm)
        throw "Error!!! There is out of bounds matrix";
    return matrix->matrix[str*matrix->n_clm + idx];
}

// RowDenseConst

RowDenseConst::RowDenseConst(const DenseMatrix *mat)
{
    clm = new size_t(0);
    matrix = mat;
}

RowDenseConst::~RowDenseConst()
{
    delete clm;
}

RowDenseConst const & operator +(const RowDenseConst & row, size_t idx)
{
    row.clm[0] += idx;
    return row;
}

RowDenseConst const & operator +(size_t idx, const RowDenseConst & row)
{
    row.clm[0] += idx;
    return row;
}

RowDenseConst const & operator -(const RowDenseConst & row, size_t idx)
{
    row.clm[0] -= idx;
    return row;
}

RowDenseConst const & operator -(size_t idx, const RowDenseConst & row)
{
    row.clm[0] -= idx;
    return row;
}

double RowDenseConst::operator *() const
{
    size_t str = matrix->shift_str[0];
    matrix->shift_str[0] = 0;
    if (str >= matrix->n_str || *clm >= matrix->n_clm)
        throw "Error!!! There is out of bounds matrix";
    return matrix->matrix[str*matrix->n_clm + *clm];
}

double RowDenseConst::operator [](size_t idx)
{
    size_t str = matrix->shift_str[0];
    matrix->shift_str[0] = 0;
    if (str >= matrix->n_str || idx >= matrix->n_clm)
        throw "Error!!! There is out of bounds matrix";
    return matrix->matrix[str*matrix->n_clm + idx];
}

std::ostream& operator<<(std::ostream &os, const DenseMatrix& matrix) {
	for (size_t i = 0; i < matrix.n_str; i++){
        for (size_t j = 0; j < matrix.n_clm; j++)
            os << matrix.matrix[i*matrix.n_clm + j] << ' ';
        os << '\n';
    }
    return os;
}

DenseMatrix & operator *=(DenseMatrix &matrix, size_t num){
    for (size_t i = 0; i < matrix.n_str; i++){
        for (size_t j = 0; j < matrix.n_clm; j++)
            matrix.matrix[i*matrix.n_clm + j] *= num;
    }
    return matrix;
}
