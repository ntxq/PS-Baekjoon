#include <iostream>

int main() {
    int max = -1, index = -1;
    for (int i = 0; i < 9; ++i) {
        int num;
        std::cin >> num;
        if (num > max) {
            max = num;
            index = i;
        }
    }

    std::cout << max << '\n' << index + 1;

    return 0;
}