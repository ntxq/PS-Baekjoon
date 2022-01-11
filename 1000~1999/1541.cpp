#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int number;
    char operation;

    std::cin >> number;
    std::vector<int> sequence{number};

    while (std::cin >> operation >> number)
        if (operation == '+')
            sequence.back() += number;
        else
            sequence.push_back(number);

    number = sequence[0];
    for (unsigned i = 1; i < sequence.size(); ++i) number -= sequence[i];

    std::cout << number;

    return 0;
}