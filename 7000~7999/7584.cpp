#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    char c;
    while (std::cin >> c && c != '#') {
        std::cin.ignore();

        std::string s;
        std::getline(std::cin, s);

        auto L = (s.size() + 1) / 2;

        if (L == 9) {
            std::cout << "Draw\n";
        } else if (L % 2) {
            std::cout << (c == 'O' ? "O\n" : "X\n");
        } else {
            std::cout << (c == 'X' ? "O\n" : "X\n");
        }
    }

    return 0;
}
