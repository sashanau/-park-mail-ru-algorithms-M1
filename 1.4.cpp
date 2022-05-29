#include <iostream>

size_t invert_bit(size_t n, size_t k){
    size_t temp = 1;
    temp = temp << k;
    n ^= temp;
    return (n);
}

int main() {
    size_t n, k;
    std::cin >> n >> k;
    std::cout << invert_bit(n, k) << std::endl;
}