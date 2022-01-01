#include <iomanip>
#include <iostream>

int main() {
    int size;
    std::cin >> size;

    int max = 0;
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        int score;
        std::cin >> score;

        sum += score;
        if (score > max) max = score;
    }

    std::cout << std::setprecision(2) << std::fixed
              << (static_cast<double>(sum) * 100 / max / size);

    return 0;
}