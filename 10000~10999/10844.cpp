#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    unsigned long long DP[10] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    for (int i = 1; i < N; ++i) {
        unsigned long long next[10];
        next[0] = DP[1];
        next[9] = DP[8];
        for (int j = 1; j < 9; ++j)
            next[j] = (DP[j - 1] + DP[j + 1]) % 1000000000;
        std::copy(next, next + 10, DP);
    }

    unsigned long long ans = 0;
    for (int i = 0; i < 10; ++i)
        ans = (ans + DP[i]) % 1000000000;

    std::cout << ans << '\n';

    return 0;
}
