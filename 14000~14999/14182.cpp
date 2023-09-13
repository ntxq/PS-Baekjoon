#include <algorithm>
#include <iostream>
#include <numeric>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int income;
    while (std::cin >> income && income) {
        if (1000000 < income && income <= 5000000)
            income *= 0.9;
        else if (5000000 < income)
            income *= 0.8;

        std::cout << income << '\n';
    }

    return 0;
}
