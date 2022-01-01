#include <iostream>

int main() {
    int year;
    std::cin >> year;

    std::cout << ((!(year % 4) && (year % 100)) || !(year % 400));

    return 0;
}