#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    unsigned long long a, b, c;
    std::cin >> a >> b >> c;

    unsigned long long sum = 1;
    while (b) {
        if (b % 2) {
            sum = (sum * a) % c;
        }
        a = (a * a) % c;
        b /= 2;
    }

    std::cout << sum;

    return 0;
}