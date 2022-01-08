#include <iostream>
#include <vector>

std::vector<int> sieve(int m, int n) {
    std::vector<bool> isPrime(n + 1, true);
    for (int i = 2; i * i <= n; ++i)
        if (isPrime[i - 1])
            for (int j = 2; i * j <= n; ++j) isPrime[i * j - 1] = false;

    std::vector<int> primes;
    for (int i = m - 1; i < n; ++i)
        if (isPrime[i] && i) primes.push_back(i + 1);

    return primes;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int m, n;
    std::cin >> m >> n;

    for (const int& i : sieve(m, n)) std::cout << i << '\n';

    return 0;
}