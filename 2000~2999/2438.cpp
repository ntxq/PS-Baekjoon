#include <iostream>

int main() {
    int line;
    std::cin >> line;

    for (int i = 0; i < line; ++i) {
        for (int j = 0; j <= i; ++j) std::cout << '*';
        std::cout << '\n';
    }

    return 0;
}