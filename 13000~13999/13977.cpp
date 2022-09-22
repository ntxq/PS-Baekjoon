#include <iostream>

const long long MAX = 4000000;
const long long MOD = 1000000007;

long long factorial[MAX + 1];
long long inverse[MAX + 1];

long long power(long long a, long long b) {
    if (b == 0) return 1;
    if (b == 1) return a % MOD;
    if (b % 2) return (a * power(a * a % MOD, b / 2)) % MOD;
    return power(a * a % MOD, b / 2);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    factorial[0] = 1;
    for (int i = 1; i <= MAX; ++i) factorial[i] = (factorial[i - 1] * i) % MOD;

    inverse[MAX] = power(factorial[MAX], MOD - 2);
    for (int i = MAX - 1; i >= 0; --i)
        inverse[i] = (inverse[i + 1] * (i + 1)) % MOD;

    int M;
    std::cin >> M;

    for (int i = 0; i < M; ++i) {
        int N, K;
        std::cin >> N >> K;

        std::cout << (factorial[N] * inverse[K] % MOD) * inverse[N - K] % MOD
                  << '\n';
    }

    return 0;
}