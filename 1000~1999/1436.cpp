#include <iostream>

bool isDemonNumber(int number) {
    if (number < 666) return false;

    while (number) {
        if (number % 1000 == 666) return true;

        number /= 10;
    }

    return false;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    int number = 0;
    for (int cnt = 0; cnt < n; ++number)
        if (isDemonNumber(number)) ++cnt;

    std::cout << number - 1;

    return 0;
}