#include <iostream>
#include <string>

int main() {
    std::string str;
    std::cin >> str >> str;

    int sum = 0;
    for (const char& c : str) sum += c - '0';

    std::cout << sum;

    return 0;
}