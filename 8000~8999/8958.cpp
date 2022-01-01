#include <iostream>
#include <string>

int main() {
    int size;
    std::cin >> size;

    for (int i = 0; i < size; ++i) {
        std::string test;
        std::cin >> test;

        int sum = 0;
        int curScore = 0;

        for (const char& c : test) {
            if (c == 'O')
                sum += ++curScore;
            else
                curScore = 0;
        }

        std::cout << sum << '\n';
    }

    return 0;
}