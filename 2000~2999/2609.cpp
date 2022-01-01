#include <iostream>
#include <numeric>

int main() {
    int a, b;
    std::cin >> a >> b;

    int x = std::gcd(a, b);
    int y = a * b / x;

    std::cout << x << '\n' << y;

    return 0;
}