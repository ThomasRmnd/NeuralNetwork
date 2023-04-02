#pragma once

#include <utility>
#include <vector>

#include "vector/Vector.hpp"

class Vector;

class Matrix {

private:

    std::vector<Vector> m_mat;

public:

    // Constructors
    Matrix();
    Matrix(std::size_t n, double value = 0.);
    Matrix(std::size_t row, std::size_t col, double value = 0.);
    Matrix(const Matrix& other) = default;

    // Destructors
    ~Matrix() = default;

    // Operators
    Matrix& operator=(const Matrix& other) = default;
    Matrix& operator+=(const Matrix& other);
    Matrix& operator+=(const Vector& other);
    Matrix& operator+=(double value);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator-=(const Vector& other);
    Matrix& operator-=(double value);
    Matrix& operator*=(const Matrix& other);
    Matrix& operator*=(const Vector& other);
    Matrix& operator*=(double value);
    Matrix& operator/=(const Matrix& other);
    Matrix& operator/=(const Vector& other);
    Matrix& operator/=(double value);
    Vector& operator[](unsigned int i);
    const Vector& operator[](unsigned int i) const;

    // Other members
    std::pair<std::size_t, std::size_t> size() const;
    std::size_t nbRows() const;
    std::size_t nbCols() const;
    Matrix dot(const Matrix& other) const;
    Vector dot(const Vector& other) const;
    Matrix transpose() const;
    std::vector<Vector>::iterator begin();
    std::vector<Vector>::const_iterator begin() const;
    std::vector<Vector>::iterator end();
    std::vector<Vector>::const_iterator end() const;
    std::vector<Vector>::const_iterator cbegin() const;
    std::vector<Vector>::const_iterator cend() const;

    // Friend functions

};

// Functions
void checkMatDimOp(const Matrix& m1, const Matrix& m2);
void checkVectMatDimOp(const Vector& v, const Matrix& m);
void checkMatVectDimDot(const Matrix& m, const Vector& v);
void checkMatDimDot(const Matrix& m1, const Matrix& m2);
Matrix operator+(const Matrix& m1, const Matrix& m2);
Matrix operator+(const Matrix& m, const Vector& v);
Matrix operator+(const Vector& v, const Matrix& m);
Matrix operator+(const Matrix& m, double value);
Matrix operator+(double value, const Matrix& m);
Matrix operator-(const Matrix& m1, const Matrix& m2);
Matrix operator-(const Matrix& m, const Vector& v);
Matrix operator-(const Vector& v, const Matrix& m);
Matrix operator-(const Matrix& m, double value);
Matrix operator-(double value, const Matrix& m);
Matrix operator*(const Matrix& m1, const Matrix& m2);
Matrix operator*(const Matrix& m, const Vector& v);
Matrix operator*(const Vector& v, const Matrix& m);
Matrix operator*(const Matrix& m, double value);
Matrix operator*(double value, const Matrix& m);
Matrix operator/(const Matrix& m1, const Matrix& m2);
Matrix operator/(const Matrix& m, const Vector& v);
Matrix operator/(const Vector& v, const Matrix& m);
Matrix operator/(const Matrix& m, double value);
Matrix operator/(double value, const Matrix& m);
std::pair<std::size_t, std::size_t> size(const Matrix& m);
Matrix dot(const Matrix& m1, const Matrix& m2);
Vector dot(const Matrix& m, const Vector& v);
Vector dot(const Vector& v, const Matrix& m);
Matrix transpose(const Matrix& m);