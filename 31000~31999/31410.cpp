#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    long long N;
    std::cin >> N;

    std::vector<std::pair<long long, long long>> poisons(N);
    for (int i = 0; i < N; ++i)
        std::cin >> poisons[i].first >> poisons[i].second;
    std::sort(poisons.begin(), poisons.end());

    long long ltor = poisons[0].second;
    for (int i = 1; i < N; ++i) {
        ltor += poisons[i].second;
        ltor += (poisons[i].first - poisons[i - 1].first) * i;
    }

    long long rtol = poisons[N - 1].second;
    for (int i = N - 2; i >= 0; --i) {
        rtol += poisons[i].second;
        rtol += (poisons[i + 1].first - poisons[i].first) * (N - i - 1);
    }

    std::vector<long long> dp(N);
    dp[0] = std::min(
        ltor + poisons[0].first - poisons[0].second - poisons[N - 1].first,
        rtol - poisons[0].second -
            (N - 1) * (poisons[1].first - poisons[0].first));
    dp[N - 1] = std::min(
        ltor - poisons[N - 1].second -
            (N - 1) * (poisons[N - 1].first - poisons[N - 2].first),
        rtol + poisons[0].first - poisons[N - 1].first - poisons[N - 1].second);

    for (int i = 1; i < N - 1; ++i)
        dp[i] = std::min(
            ltor + poisons[i].first - poisons[i].second - poisons[N - 1].first,
            rtol - poisons[i].first - poisons[i].second + poisons[0].first);

    std::cout << *std::min_element(dp.begin(), dp.end()) << '\n';

    return 0;
}
