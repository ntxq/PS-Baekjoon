#include <algorithm>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    int w;
    std::cin >> w;

    std::vector<std::pair<int, int>> events(w);
    for (auto& event : events) std::cin >> event.first >> event.second;

    std::vector<std::vector<int>> dp(w + 1, std::vector<int>(w + 1, 0));
    std::vector<std::vector<bool>> move(w + 1, std::vector<bool>(w + 1, false));

    for (int i = w - 1; i >= 0; --i) {
        for (int j = w - 1; j >= 0; --j) {
            int nextEvent = std::max(i, j);
            auto nextLoc = events[nextEvent];

            auto curLoc1 = ((i == 0) ? std::make_pair(1, 1) : events[i - 1]);
            auto curLoc2 = ((j == 0) ? std::make_pair(n, n) : events[j - 1]);

            int dist1 = std::abs(nextLoc.first - curLoc1.first) +
                        std::abs(nextLoc.second - curLoc1.second) +
                        dp[nextEvent + 1][j];
            int dist2 = std::abs(nextLoc.first - curLoc2.first) +
                        std::abs(nextLoc.second - curLoc2.second) +
                        dp[i][nextEvent + 1];

            if (dist1 < dist2) {
                dp[i][j] = dist1;
                move[i][j] = true;
            } else {
                dp[i][j] = dist2;
                move[i][j] = false;
            }
        }
    }

    std::cout << dp[0][0] << '\n';

    int i = 0, j = 0;
    while (i < w && j < w) {
        if (move[i][j]) {
            std::cout << 1 << '\n';
            i = std::max(i, j) + 1;
        } else {
            std::cout << 2 << '\n';
            j = std::max(i, j) + 1;
        }
    }

    return 0;
}
