#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int maximumScore(const std::vector<int>& scores) {
    std::vector<std::pair<int, int>> dp(scores.size());

    if (scores.size() == 1) return scores[0];

    dp[0] = {scores[0], 0};
    dp[1] = {scores[1], scores[0] + scores[1]};

    for (unsigned i = 2; i < scores.size(); ++i) {
        dp[i].first = std::max(dp[i - 2].first, dp[i - 2].second) + scores[i];
        dp[i].second = dp[i - 1].first + scores[i];
    }

    return std::max(dp[scores.size() - 1].first, dp[scores.size() - 1].second);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int size;
    std::cin >> size;

    std::vector<int> scores(size);
    for (int& i : scores) std::cin >> i;

    std::cout << maximumScore(scores);

    return 0;
}