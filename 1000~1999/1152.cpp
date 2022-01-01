#include <iostream>
#include <string>

int main() {
    int count = 0;
    std::string word;
    while (std::cin >> word) ++count;

    std::cout << count;

    return 0;
}