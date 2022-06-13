#include <algorithm>
#include <iostream>
#include <string>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string line;
    while (std::getline(std::cin, line)) std::cout << line << '\n';

    return 0;
}