#include <algorithm>
#include <functional>
#include <numeric>

#include "matrix/Matrix.hpp"

// Constructors

Matrix::Matrix() : 
    m_mat()
{}

Matrix::Matrix(std::size_t n, double value) :
    m_mat(n, Vector(n, value))
{}

Matrix::Matrix(std::size_t row, std::size_t col, double value) :
    m_mat(row, Vector(col, value))
{}

// Operators

Matrix& Matrix::operator+=(const Matrix& other) {
    checkMatDimOp(*this, other);
    std::transform(
        begin(), end(),
        other.cbegin(),
        begin(), std::plus<Vector>()
    );
    return *this;
}

Matrix& Matrix::operator+=(const Vector& other) {
    checkVectMatDimOp(other, *this);
    std::for_each(begin(), end(), [other](Vector& v){v += other;});
    return *this;
}

Matrix& Matrix::operator+=(double value) {
    std::for_each(begin(), end(), [value](Vector& v){v += value;});
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    checkMatDimOp(*this, other);
    std::transform(
        begin(), end(),
        other.cbegin(),
        begin(), std::minus<Vector>()
    );
    return *this;
}

Matrix& Matrix::operator-=(const Vector& other) {
    checkVectMatDimOp(other, *this);
    std::for_each(begin(), end(), [other](Vector& v){v -= other;});
    return *this;
}

Matrix& Matrix::operator-=(double value) {
    std::for_each(begin(), end(), [value](Vector& v){v -= value;});
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
    checkMatDimOp(*this, other);
    std::transform(
        begin(), end(),
        other.cbegin(),
        begin(), std::multiplies<Vector>()
    );
    return *this;
}

Matrix& Matrix::operator*=(const Vector& other) {
    checkVectMatDimOp(other, *this);
    std::for_each(begin(), end(), [other](Vector& v){v -= other;});
    return *this;
}

Matrix& Matrix::operator*=(double value) {
    std::for_each(begin(), end(), [value](Vector& v){v *= value;});
    return *this;
}

Matrix& Matrix::operator/=(const Matrix& other) {
    checkMatDimOp(*this, other);
    std::transform(
        begin(), end(),
        other.cbegin(),
        begin(), std::divides<Vector>()
    );
    return *this;
}

Matrix& Matrix::operator/=(const Vector& other) {
    checkVectMatDimOp(other, *this);
    std::for_each(begin(), end(), [other](Vector& v){v /= other;});
    return *this;
}

Matrix& Matrix::operator/=(double value) {
    std::for_each(begin(), end(), [value](Vector& v){v /= value;});
    return *this;
}

Vector& Matrix::operator[](unsigned int i) {
    return m_mat[i];
}

const Vector& Matrix::operator[](unsigned int i) const {
    return m_mat[i];
}

// Other members 

std::pair<std::size_t, std::size_t> Matrix::size() const {
    return std::pair<std::size_t, std::size_t>(nbRows(), nbCols());
}

std::size_t Matrix::nbRows() const {
    return m_mat.size();
}

std::size_t Matrix::nbCols() const {
    return m_mat[0].size();
}

Matrix Matrix::dot(const Matrix& other) const {
    Matrix result(nbRows(), other.nbCols());
    std::transform(
        cbegin(), cend(),
        result.begin(),
        [other](const Vector& v){return v.dot(other);}
    );
    return result;
}

Vector Matrix::dot(const Vector& other) const {
    return std::inner_product(cbegin(), cend(), other.cbegin(), Vector(nbRows()));
}

Matrix Matrix::transpose() const {
    Matrix result(nbCols(), nbRows());
    for (unsigned int i = 0; i < nbRows(); i++) {
        for (unsigned int j = 0; j < nbCols(); j++) {
            result[j][i] = m_mat[i][j];
        }
    }
    return result;
}

std::vector<Vector>::iterator Matrix::begin() {
    return m_mat.begin();
}

std::vector<Vector>::const_iterator Matrix::begin() const {
    return m_mat.cbegin();
}

std::vector<Vector>::iterator Matrix::end() {
    return m_mat.end();
}

std::vector<Vector>::const_iterator Matrix::end() const {
    return m_mat.cend();
}

std::vector<Vector>::const_iterator Matrix::cbegin() const {
    return m_mat.cbegin();
}

std::vector<Vector>::const_iterator Matrix::cend() const {
    return m_mat.cend();
}

// Functions

void checkMatDimOp(const Matrix& m1, const Matrix& m2) {
    if (m1.size() != m2.size()) {
        throw("Matrix do not have the same dimensions.");
    }
    return;
}

void checkVectMatDimOp(const Vector& v, const Matrix& m) {
    if (v.size() != m.nbCols()) {
        throw("Vector and Matrix do not have the right dimensions.");
    }
    return;
}

void checkMatVectDimDot(const Matrix& m, const Vector& v) {
    if (m.nbCols() != v.size()) {
        throw("Vector and Matrix do not have the right dimensions for dot product.");
    }
    return;
}

void checkMatDimDot(const Matrix& m1, const Matrix& m2) {
    if (m1.nbCols() != m2.nbRows()) {
        throw("Matrices do not have the right dimensions for dot product.");
    }
    return;
}

Matrix operator+(const Matrix& m1, const Matrix& m2) {
    Matrix result(m1);
    result += m2;
    return result;
}

Matrix operator+(const Matrix& m, const Vector& v) {
    Matrix result(m);
    result += v;
    return result;
}

Matrix operator+(const Vector& v, const Matrix& m) {
    Matrix result(m);
    result += v;
    return result;
}

Matrix operator+(const Matrix& m, double value) {
    Matrix result(m);
    result += value;
    return result;
}

Matrix operator+(double value, const Matrix& m) {
    Matrix result(m);
    result += value;
    return result;
}

Matrix operator-(const Matrix& m1, const Matrix& m2) {
    Matrix result(m1);
    result -= m2;
    return result;
}

Matrix operator-(const Matrix& m, const Vector& v) {
    Matrix result(m);
    result -= v;
    return result;
}

Matrix operator-(const Vector& v, const Matrix& m) {
    Matrix result(m);
    result -= v;
    return result;
}

Matrix operator-(const Matrix& m, double value) {
    Matrix result(m);
    result -= value;
    return result;
}

Matrix operator-(double value, const Matrix& m) {
    Matrix result(m);
    result -= value;
    return result;
}

Matrix operator*(const Matrix& m1, const Matrix& m2) {
    Matrix result(m1);
    result *= m2;
    return result;
}

Matrix operator*(const Matrix& m, const Vector& v) {
    Matrix result(m);
    result *= v;
    return result;
}

Matrix operator*(const Vector& v, const Matrix& m) {
    Matrix result(m);
    result *= v;
    return result;
}

Matrix operator*(const Matrix& m, double value) {
    Matrix result(m);
    result *= value;
    return result;
}

Matrix operator*(double value, const Matrix& m) {
    Matrix result(m);
    result *= value;
    return result;
}

Matrix operator/(const Matrix& m1, const Matrix& m2) {
    Matrix result(m1);
    result /= m2;
    return result;
}

Matrix operator/(const Matrix& m, const Vector& v) {
    Matrix result(m);
    result /= v;
    return result;
}

Matrix operator/(const Vector& v, const Matrix& m) {
    Matrix result(m);
    result /= v;
    return result;
}

Matrix operator/(const Matrix& m, double value) {
    Matrix result(m);
    result /= value;
    return result;
}

Matrix operator/(double value, const Matrix& m) {
    Matrix result(m);
    result /= value;
    return result;
}

std::pair<std::size_t, std::size_t> size(const Matrix& m) {
    return m.size();
}

Matrix dot(const Matrix& m1, const Matrix& m2) {
    return m1.dot(m2);
}

Vector dot(const Matrix& m, const Vector& v) {
    return m.dot(v);
}

Vector dot(const Vector& v, const Matrix& m) {
    return v.dot(m);
}

Matrix transpose(const Matrix& m) {
    return m.transpose();
}