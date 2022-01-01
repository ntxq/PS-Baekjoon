#include <iomanip>
#include <iostream>

int main() {
    int a, b;
    std::cin >> a >> b;

    std::cout << std::setprecision(10) << static_cast<double>(a) / b;

    return 0;
}