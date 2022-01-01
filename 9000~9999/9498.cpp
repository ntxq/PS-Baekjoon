#include <iostream>

int main() {
    int score;
    std::cin >> score;

    char letter =
        (score < 60
             ? 'F'
             : (score < 70 ? 'D'
                           : (score < 80 ? 'C' : (score < 90 ? 'B' : 'A'))));

    std::cout << letter;

    return 0;
}