#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int N;
        std::cin >> N;

        std::vector<int> knapsack(N * 100 + 1, std::numeric_limits<int>::max());
        knapsack[0] = 0;

        int total = 0;
        for (int i = 0; i < N; ++i) {
            int a, b;
            std::cin >> a >> b;

            total += a;
            for (int j = total; j >= a; --j)
                if (knapsack[j - a] != std::numeric_limits<int>::max())
                    knapsack[j] = std::min(knapsack[j], knapsack[j - a] + b);
        }

        int minTime = total;
        for (int i = 0; i <= total; ++i)
            minTime = std::min(minTime, std::max(total - i, knapsack[i]));
        std::cout << minTime << '\n';
    }

    return 0;
}
