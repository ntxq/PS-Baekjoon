#include <algorithm>
#include <iostream>

unsigned long long power(unsigned long long a, unsigned long long b) {
    if (b == 0)
        return 1;
    else if (b % 2)
        return a * power(a * a % 1000000007, b / 2) % 1000000007;
    else
        return power(a * a % 1000000007, b / 2) % 1000000007;
}

unsigned long long inverse(unsigned long long x, unsigned long long m) {
    return power(x, m - 2);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, k;
    std::cin >> n >> k;

    unsigned long long factorials[2]{1, 1};

    unsigned long long factorial_n = 1;
    unsigned long long factorial_k = 1;
    unsigned long long factorial_n_k = 1;

    for (int i = 1; i <= n; ++i) {
        unsigned long long factorial_i = factorials[1] * i % 1000000007;
        factorials[0] = factorials[1];
        factorials[1] = factorial_i;

        if (i == n) factorial_n = factorials[1];
        if (i == k) factorial_k = factorials[1];
        if (i == n - k) factorial_n_k = factorials[1];
    }

    std::cout << factorial_n *
                     inverse(factorial_k * factorial_n_k % 1000000007,
                             1000000007) %
                     1000000007
              << '\n';

    return 0;
}