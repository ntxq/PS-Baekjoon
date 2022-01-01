#include <iostream>

int main() {
    int checksum = 0;
    for (int i = 0, number; i < 5; ++i) {
        std::cin >> number;
        checksum = (checksum + number * number) % 10;
    }

    std::cout << checksum;

    return 0;
}