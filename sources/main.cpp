#include <iostream>

#include "vector/Vector.hpp"
#include "matrix/Matrix.hpp"
#include "ndarray/NDArray.hpp"

int main() {
    NDArray<int> a({ 2, 3, 4 }, 1);
    std::cout << a << std::endl;
    a.reshape({2, 12});
    std::cout << a << std::endl;
    a += 1;
    std::cout << a << std::endl;
    a -= NDArray<int>({ 2, 12 }, 1);
    std::cout << a << std::endl;
    std::cout << "Hello World!" << std::endl;
    return 0;
}