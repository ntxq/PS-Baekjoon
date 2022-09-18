#include <algorithm>
#include <iostream>
#include <vector>

const long long MOD = 1000000007;

long long pow(long long b, long long e) {
    if (e == 0) return 1;
    if (e == 1) return b;
    if (e % 2) return (b * pow(b * b % MOD, e / 2)) % MOD;
    return pow(b * b % MOD, e / 2);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<long long> A(N);
    for (auto& i : A) std::cin >> i;
    std::sort(A.begin(), A.end());

    long long score = 0;
    for (int i = 0; i < N; ++i) {
        const long long maxCount = pow(2, i);
        score = (score + ((A[i] * maxCount) % MOD)) % MOD;

        const long long minCount = pow(2, N - i - 1);
        score = (score - ((A[i] * minCount) % MOD)) % MOD;
    }

    score = (score + MOD) % MOD;
    std::cout << score << '\n';

    return 0;
}