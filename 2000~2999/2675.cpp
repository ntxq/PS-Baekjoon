#include <iostream>
#include <string>

int main() {
    int size;
    std::cin >> size;

    for (int i = 0; i < size; ++i) {
        int times;
        std::string str;
        std::cin >> times >> str;

        for (const char& c : str) {
            for (int j = 0; j < times; ++j) {
                std::cout << c;
            }
        }

        std::cout << '\n';
    }

    return 0;
}