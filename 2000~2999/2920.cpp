#include <iostream>
#include <string>

int main() {
    int number;
    std::cin >> number;

    if (number == 1) {
        for (int i = 2; i < 9; ++i) {
            std::cin >> number;
            if (number != i) {
                std::cout << "mixed";
                return 0;
            }
        }

        std::cout << "ascending";
    } else if (number == 8) {
        for (int i = 7; i > 1; --i) {
            std::cin >> number;
            if (number != i) {
                std::cout << "mixed";
                return 0;
            }
        }

        std::cout << "descending";
    } else {
        std::cout << "mixed";
    }

    return 0;
}