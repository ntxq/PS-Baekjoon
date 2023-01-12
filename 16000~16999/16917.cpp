#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int spicy, fried, half;
    std::cin >> spicy >> fried >> half;

    spicy = std::min(spicy, half * 2);
    fried = std::min(fried, half * 2);

    int x, y;
    std::cin >> x >> y;

    int pure = x * spicy + y * fried;
    int mixed = std::min(x, y) * 2 * half + (x - std::min(x, y)) * spicy +
                (y - std::min(x, y)) * fried;

    std::cout << std::min(pure, mixed) << '\n';

    return 0;
}