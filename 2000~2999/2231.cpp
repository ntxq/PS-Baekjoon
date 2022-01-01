#include <iostream>

int getDigitSum(int x) {
    int sum = x;
    while (x > 0) {
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int x;
    std::cin >> x;

    for (int i = 1; i <= x; ++i) {
        int sum = getDigitSum(i);
        if (sum == x) {
            std::cout << i;
            return 0;
        }
    }

    std::cout << 0;

    return 0;
}