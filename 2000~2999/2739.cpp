#include <iostream>

int main() {
    int base;
    std::cin >> base;

    for (int i = 1; i < 10; ++i)
        std::cout << base << " * " << i << " = " << base * i << '\n';

    return 0;
}