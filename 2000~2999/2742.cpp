#include <iostream>

int main() {
    int base;
    std::cin >> base;

    while (base) std::cout << base-- << '\n';

    return 0;
}