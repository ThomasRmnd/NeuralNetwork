#pragma once 

#include <vector>

#include "matrix/Matrix.hpp"

class Matrix;

class Vector {

private:

    std::vector<double> m_vec;

public:

    // Constructors
    Vector();
    Vector(std::size_t n, double value = 0.);
    Vector(const Vector& other) = default;

    // Destructors
    ~Vector() = default;

    // Operators
    Vector& operator=(const Vector& other) = default;
    Vector& operator+=(const Vector& other);
    Vector& operator+=(double value);
    Vector& operator-=(const Vector& other);
    Vector& operator-=(double value);
    Vector& operator*=(const Vector& other); // not the dot product
    Vector& operator*=(double value);
    Vector& operator/=(const Vector& other);
    Vector& operator/=(double value);
    double& operator[](unsigned int i);
    const double& operator[](unsigned int i) const;

    // Other members
    std::size_t size() const;
    double dot(const Vector& other) const;
    Vector dot(const Matrix& other) const;
    std::vector<double>::iterator begin();
    std::vector<double>::const_iterator begin() const;
    std::vector<double>::iterator end();
    std::vector<double>::const_iterator end() const;
    std::vector<double>::const_iterator cbegin() const;
    std::vector<double>::const_iterator cend() const;

    // Friend functions

};

// Functions
void checkVectDimOp(const Vector& v1, const Vector& v2);
void checkVectMatDimDot(const Vector& v, const Matrix& m);
Vector operator+(const Vector& v1, const Vector& v2);
Vector operator+(const Vector& v, double value);
Vector operator+(double value, const Vector& v);
Vector operator+(const Vector& v);
Vector operator-(const Vector& v1, const Vector& v2);
Vector operator-(const Vector& v, double value);
Vector operator-(double value, const Vector& v);
Vector operator-(const Vector& v);
Vector operator*(const Vector& v1, const Vector& v2);
Vector operator*(const Vector& v, double value);
Vector operator*(double value, const Vector& v);
Vector operator/(const Vector& v1, const Vector& v2);
Vector operator/(const Vector& v, double value);
Vector operator/(double value, const Vector& v);
std::size_t size(const Vector& v);
double dot(const Vector& v1, const Vector& v2);