#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

std::vector<unsigned long long> sieve(unsigned long long n) {
    std::vector<unsigned long long> primes;
    std::vector<bool> isPrime(std::sqrt(n) + 2, true);

    isPrime[0] = isPrime[1] = false;
    for (unsigned long long i = 2; i <= std::sqrt(n) + 1; ++i)
        if (isPrime[i]) {
            primes.push_back(i);
            for (unsigned long long j = i * i; j <= std::sqrt(n) + 1; j += i)
                isPrime[j] = false;
        }

    return primes;
}

bool isPrime(unsigned long long n) {
    for (unsigned long long i = 2; i * i <= n; ++i)
        if (n % i == 0) return false;

    return true;
}

unsigned long long power(unsigned long long a, unsigned long long b) {
    if (b == 0)
        return 1;
    else if (b % 2)
        return a * power(a * a, b / 2);
    else
        return power(a * a, b / 2);
}

unsigned long long totient(unsigned long long n) {
    std::vector<unsigned long long> primes = sieve(n);
    unsigned long long result = 1;

    for (unsigned long long p : primes) {
        unsigned long long exp = 0;
        while (n % p == 0) {
            ++exp;
            n /= p;
        }

        if (exp) result *= power(p, exp - 1) * (p - 1);
    }

    if (n > 1 && isPrime(n)) result *= (n - 1);

    return result;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    unsigned long long n;
    std::cin >> n;

    std::cout << totient(n) << '\n';

    return 0;
}
