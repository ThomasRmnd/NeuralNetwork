#pragma once

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>
#include <ranges>

template<typename T>
class NDArray {

private:

    // Members 

    std::vector<T> m_data;
    std::vector<std::size_t> m_shape;

    // Private methods

    void delete_unessecary_dimensions(std::vector<std::size_t>& shape) {
        shape | std::views::filter([](std::size_t s){return s > 1;});
        return;
    }

    bool is_sub_shape(cons std::vector<std::size_t>& shape) const {
        if (shape.size() > m_shape.size()) {
            return false;
        }
        for (std::size_t i = 0; i < (m_shape.size() - shape.size()); i++) {
            bool is_equal = true;
            for (std::size_t j = 0; j < shape.size(); j++) {
                if (shape[j] != m_shape[i + j]) {
                    is_equal = false;
                    break;
                }
            }
            if (is_equal) {
                return true;
            }
        }
        return false;
    }

public:

    // Constructors

    NDArray() : m_data(), m_shape() {};

    NDArray(std::vector<std::size_t> shape, const T& value = T()) {
        std::size_t size = std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<std::size_t>());
        m_data.resize(size, value);
        reshape(shape);
    };

    NDArray(const std::vector<T>& data) : m_data(data), m_shape(1, data.size()) {};



    // Operators

    T& operator()(const std::vector<std::size_t>& indices) {
        if (indices.size() != m_shape.size()) {
            throw std::invalid_argument("Number of indices does not match dimension of NDArray.");
        }
        std::size_t index = 0;
        for (std::size_t i = 0; i < indices.size(); i++) {
            if (indices[i] >= m_shape[i]) {
                throw std::invalid_argument("Index out of range.");
            }
            index *= m_shape[i];
            index += indices[i];
        }
        return m_data[index];
    };

    const T& operator()(const std::vector<std::size_t>& indices) const {
        if (indices.size() != m_shape.size()) {
            throw std::invalid_argument("Number of indices does not match dimension of NDArray.");
        }
        std::size_t index = 0;
        for (std::size_t i = 0; i < indices.size(); i++) {
            if (indices[i] >= m_shape[i]) {
                throw std::invalid_argument("Index out of range.");
            }
            index *= m_shape[i];
            index += indices[i];
        }
        return m_data[index];
    };

    NDArray<T>& operator+=(const T& value) {
        std::for_each(m_data.begin(), m_data.end(), [&value](T& t) {t += value;});
        return *this;
    }

    NDArray<T>& operator-=(const T& value) {
        std::for_each(m_data.begin(), m_data.end(), [&value](T& t) {t -= value;});
        return *this;
    }

    NDArray<T>& operator*=(const T& value) {
        std::for_each(m_data.begin(), m_data.end(), [&value](T& t) {t *= value;});
        return *this;
    }

    NDArray<T>& operator/=(const T& value) {
        std::for_each(m_data.begin(), m_data.end(), [&value](T& t) {t /= value;});
        return *this;
    }

    NDArray<T>& operator+=(const NDArray<T>& other) {
        if (m_shape != other.m_shape) {
            throw std::invalid_argument("Cannot add NDArrays with different shapes.");
        }
        std::transform(m_data.begin(), m_data.end(), other.m_data.begin(), m_data.begin(), std::plus<T>());
        return *this;
    }

    NDArray<T>& operator-=(const NDArray<T>& other) {
        if (m_shape != other.m_shape) {
            throw std::invalid_argument("Cannot subtract NDArrays with different shapes.");
        }
        std::transform(m_data.begin(), m_data.end(), other.m_data.begin(), m_data.begin(), std::minus<T>());
        return *this;
    }

    NDArray<T>& operator*=(const NDArray<T>& other) {
        if (m_shape != other.m_shape) {
            throw std::invalid_argument("Cannot multiply NDArrays with different shapes.");
        }
        std::transform(m_data.begin(), m_data.end(), other.m_data.begin(), m_data.begin(), std::multiplies<T>());
        return *this;
    }

    NDArray<T>& operator/=(const NDArray<T>& other) {
        if (m_shape != other.m_shape) {
            throw std::invalid_argument("Cannot divide NDArrays with different shapes.");
        }
        std::transform(m_data.begin(), m_data.end(), other.m_data.begin(), m_data.begin(), std::divides<T>());
        return *this;
    }



    // Methods

    void reshape(std::vector<std::size_t> shape) {
        delete_unessecary_dimensions(shape);
        std::size_t size = std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<std::size_t>());
        if (size != m_data.size()) {
            throw std::invalid_argument("Cannot reshape NDArray to given shape.");
        }
        m_shape.clear();
        for (std::size_t s : shape) {
            m_shape.push_back(s);
        }
        return;
    };

    void clear() {
        m_data.clear();
        m_shape.clear();
        return;
    }

    std::size_t dim() const {
        return m_shape.size();
    };

    std::size_t size() const {
        return m_data.size();
    };

    std::vector<std::size_t> shape() const {
        return m_shape;
    };

    // Friend functions

    friend std::ostream& operator<< <T>(std::ostream& os, const NDArray<T>& a);

};

template<typename T>
std::ostream& operator<<(std::ostream& os, const NDArray<T>& a) {
    os << "NDArray(" << a.dim() << "D, " << a.size() << " elements, shape: ";
    for (std::size_t i = 0; i < a.dim(); i++) {
        os << a.shape()[i];
        if (i < a.dim() - 1) {
            os << "x";
        }
    }
    os << ")" << std::endl;
    for (std::size_t i = 0; i < a.size(); i++) {
        os << a.m_data[i] << " ";
    }
    return os;
}