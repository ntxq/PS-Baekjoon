#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> wines(N);
    for (int& i : wines) std::cin >> i;

    std::vector<std::vector<int>> DP(N, std::vector<int>(3));
    DP[0] = {0, wines[0], 0};

    for (int i = 1; i < N; ++i) {
        DP[i][0] = std::max({DP[i - 1][0], DP[i - 1][1], DP[i - 1][2]});
        DP[i][1] = DP[i - 1][0] + wines[i];
        DP[i][2] = DP[i - 1][1] + wines[i];
    }

    std::cout << std::max({DP[N - 1][0], DP[N - 1][1], DP[N - 1][2]}) << '\n';

    return 0;
}
