#include <iostream>

int main() {
    int a, b, c;
    std::cin >> a >> b >> c;

    int count[10]{};

    int product = a * b * c;
    while (product) {
        count[product % 10]++;
        product /= 10;
    }

    for (int i : count) std::cout << i << '\n';

    return 0;
}