#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

const int MAX = 1000000;
const int MOD = 1000000009;

std::vector<int> sumThree() {
    std::vector<int> DP(MAX + 1);

    DP[0] = 1;
    for (int i = 1; i <= MAX; ++i)
        for (int j = 1; j < 4 && j <= i; ++j) {
            DP[i] += DP[i - j];
            DP[i] %= MOD;
        }

    return DP;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<int> DP = sumThree();

    int T;
    std::cin >> T;

    while (T--) {
        int N;
        std::cin >> N;

        std::cout << DP[N] << '\n';
    }

    return 0;
}