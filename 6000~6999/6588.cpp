#include <array>
#include <iostream>
#include <vector>

constexpr int SIEVE_SIZE = 1000001;

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::array<bool, SIEVE_SIZE> sieve;
    sieve.fill(true);
    sieve[0] = sieve[1] = false;
    for (int i = 2; i * i < SIEVE_SIZE; ++i)
        if (sieve[i])
            for (int j = i * i; j < SIEVE_SIZE; j += i) sieve[j] = false;

    int N;
    while (std::cin >> N && N) {
        int idx = 3;
        while (!sieve[idx] || !sieve[N - idx]) idx += 2;
        std::cout << N << " = " << idx << " + " << N - idx << '\n';
    }

    return 0;
}