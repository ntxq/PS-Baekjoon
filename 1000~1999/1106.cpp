#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int C, N;
    std::cin >> C >> N;

    std::vector<int> knapsack(C + 101, std::numeric_limits<int>::max());

    knapsack[0] = 0;
    for (int i = 0; i < N; ++i) {
        int cost, weight;
        std::cin >> cost >> weight;

        for (int j = weight; j < knapsack.size(); ++j)
            if (knapsack[j - weight] != std::numeric_limits<int>::max())
                knapsack[j] =
                    std::min(knapsack[j], knapsack[j - weight] + cost);
    }

    std::cout << *std::min_element(knapsack.begin() + C, knapsack.end())
              << '\n';

    return 0;
}
