#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++i) {
        int n;
        std::cin >> n;

        std::vector<std::vector<int>> stickers(2, std::vector<int>(n));
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < n; ++k) std::cin >> stickers[j][k];

        for (int j = 1; j < n; ++j) {
            for (int k = 0; k < 2; ++k) {
                if (j == 1) {
                    stickers[k][j] = stickers[!k][j - 1] + stickers[k][j];
                } else {
                    stickers[k][j] =
                        std::max(stickers[!k][j - 2], stickers[!k][j - 1]) +
                        stickers[k][j];
                }
            }
        }

        std::cout << std::max(stickers[0][n - 1], stickers[1][n - 1]) << '\n';
    }

    return 0;
}