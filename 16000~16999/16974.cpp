#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<long long> levels(51);
    std::vector<long long> dp(51);

    levels[0] = 1;
    dp[0] = 1;
    for (int i = 1; i < 51; ++i) {
        levels[i] = 2 * levels[i - 1] + 3;
        dp[i] = 2 * dp[i - 1] + 1;
    }

    long long N, X;
    std::cin >> N >> X;

    long long count = 0;
    while (X) {
        if (X == levels[N]) {
            X -= levels[N];
            count += dp[N];
        } else if (X > levels[N - 1]) {
            X -= levels[N - 1] + 1;
            count += dp[N - 1];
            N -= 1;
            if (X) {
                X -= 1;
                count += 1;
            }
        } else {
            X -= 1;
            N -= 1;
        }
    }

    std::cout << count << '\n';

    return 0;
}