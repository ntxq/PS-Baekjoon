#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int avg = 0;
    for (int i = 0; i < 5; ++i) {
        int score;
        std::cin >> score;

        if (score < 40)
            avg += 8;
        else
            avg += score / 5;
    }

    std::cout << avg << '\n';

    return 0;
}