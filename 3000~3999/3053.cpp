#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numbers>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int R;
    std::cin >> R;

    std::cout << std::fixed << std::setprecision(6) << (R * R * std::numbers::pi) << '\n' << (2 * R * R) << '\n';

    return 0;
}
