#include <iostream>

bool isPrime(int x) {
    if (x == 0 || x == 1) return false;

    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0) return false;

    return true;
}

int main() {
    std::cin.tie(nullptr);

    int size;
    std::cin >> size;

    int count = 0;
    for (int i = 0; i < size; ++i) {
        int x;
        std::cin >> x;

        if (isPrime(x)) ++count;
    }

    std::cout << count;

    return 0;
}