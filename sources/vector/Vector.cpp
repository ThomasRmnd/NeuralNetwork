#include <algorithm>
#include <functional>
#include <numeric>

#include "vector/Vector.hpp"

// Constructors

Vector::Vector() : 
    m_vec() 
{}

Vector::Vector(std::size_t n, double value) :
    m_vec(n, value)
{}

// Operators

Vector& Vector::operator+=(const Vector& other) {
    checkVectDimOp(*this, other);
    std::transform(
        begin(), end(), 
        other.cbegin(),
        begin(), std::plus<double>()
    );
    return *this;
}

Vector& Vector::operator+=(double value) {
    std::for_each(begin(), end(), [value](double& d){d += value;});
    return *this;
}

Vector& Vector::operator-=(const Vector& other) {
    checkVectDimOp(*this, other);
    std::transform(
        begin(), end(),
        other.cbegin(),
        begin(), std::minus<double>()
    );
    return *this;
}

Vector& Vector::operator-=(double value) {
    std::for_each(begin(), end(), [value](double& d){d -= value;});
    return *this;
}

Vector& Vector::operator*=(const Vector& other) {
    checkVectDimOp(*this, other);
    std::transform(
        begin(), end(),
        other.cbegin(),
        begin(), std::multiplies<double>()
    );
    return *this;
}

Vector& Vector::operator*=(double value) {
    std::for_each(begin(), end(), [value](double& d){d *= value;});
    return *this;
}

Vector& Vector::operator/=(const Vector& other) {
    checkVectDimOp(*this, other);
    std::transform(
        begin(), end(),
        other.cbegin(),
        begin(), std::divides<double>()
    );
    return *this;
}

Vector& Vector::operator/=(double value) {
    std::for_each(begin(), end(), [value](double& d){d /= value;});
    return *this;
}

double& Vector::operator[](unsigned int i) {
    return m_vec[i];
}

const double& Vector::operator[](unsigned int i) const {
    return m_vec[i];
}

// Other members 

std::size_t Vector::size() const {
    return m_vec.size();
}

double Vector::dot(const Vector& other) const {
    checkVectDimOp(*this, other);
    return std::inner_product(cbegin(), cend(), other.cbegin(), 0.);
}

Vector Vector::dot(const Matrix& other) const {
    checkVectMatDimDot(*this, other);
    return std::inner_product(cbegin(), cend(), other.cbegin(), Vector(size()));
}

std::vector<double>::iterator Vector::begin() {
    return m_vec.begin();
}

std::vector<double>::const_iterator Vector::begin() const {
    return m_vec.cbegin();
}

std::vector<double>::iterator Vector::end() {
    return m_vec.end();
}

std::vector<double>::const_iterator Vector::end() const {
    return m_vec.cend();
}

std::vector<double>::const_iterator Vector::cbegin() const {
    return m_vec.cbegin();
}

std::vector<double>::const_iterator Vector::cend() const {
    return m_vec.cend();
}

// Friend functions 



// Functions

void checkVectDimOp(const Vector& v1, const Vector& v2) {
    if (v1.size() != v2.size()) {
        throw("Vectors do not have the same dimension.");
    }
    return;
}

void checkVectMatDimDot(const Vector& v, const Matrix& m) {
    if (v.size() != m.nbRows()) {
        throw("Vector and Matrix do not have the same dimension.");
    }
    return;
}

Vector operator+(const Vector& v1, const Vector& v2) {
    checkVectDimOp(v1, v2);
    Vector result(v1);
    result += v2;
    return result;
}

Vector operator+(const Vector& v, double value) {
    Vector result(v);
    result += value;
    return result;
}

Vector operator+(double value, const Vector& v) {
    Vector result(v);
    result += value;
    return result;
}

Vector operator+(const Vector& v) {
    return v;
}

Vector operator-(const Vector& v1, const Vector& v2) {
    checkVectDimOp(v1, v2);
    Vector result(v1);
    result -= v2;
    return result;
}

Vector operator-(const Vector& v, double value) {
    Vector result(v);
    result -= value;
    return result;
}

Vector operator-(double value, const Vector& v) {
    Vector result(v);
    result -= value;
    return result;
}

Vector operator-(const Vector& v) {
    Vector result(v);
    std::for_each(result.begin(), result.end(), [](double& d){d = -d;});
    return result;
}

Vector operator*(const Vector& v1, const Vector& v2) {
    Vector result(v1);
    result *= v2;
    return result;
}

Vector operator*(const Vector& v, double value) {
    Vector result(v);
    result *= value;
    return result;
}

Vector operator*(double value, const Vector& v) {
    Vector result(v);
    result *= value;
    return result;
}

Vector operator/(const Vector& v1, const Vector& v2) {
    Vector result(v1);
    result /= v2;
    return result;
}

Vector operator/(const Vector& v, double value) {
    Vector result(v);
    result /= value;
    return result;
}

Vector operator/(double value, const Vector& v) {
    Vector result(v);
    result /= value;
    return result;
}

std::size_t size(const Vector& v) {
    return v.size();
}

double dot(const Vector& v1, const Vector& v2) {
    return std::inner_product(v1.cbegin(), v1.cend(), v2.cbegin(), 0.);
}