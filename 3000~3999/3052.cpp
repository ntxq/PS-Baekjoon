#include <iostream>
#include <string>

int main() {
    bool cases[42]{};

    for (int i = 0; i < 10; ++i) {
        int number;
        std::cin >> number;

        cases[number % 42] = true;
    }

    int sum = 0;
    for (int i = 0; i < 42; ++i) {
        if (cases[i]) ++sum;
    }

    std::cout << sum;

    return 0;
}