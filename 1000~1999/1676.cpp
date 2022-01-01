#include <cmath>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int base;
    std::cin >> base;

    int count = 0;
    for (int i = 1; std::pow(5, i) <= base; ++i) count += base / std::pow(5, i);

    std::cout << count;

    return 0;
}