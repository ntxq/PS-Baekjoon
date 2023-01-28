#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T = 0;

    int N;
    while (std::cin >> N && N) {
        std::vector<std::vector<int>> triangles;
        for (int i = 0; i < N; ++i) {
            std::vector<int> row;
            for (int j = 0; j < 1 + 2 * i; ++j) {
                int x;
                std::cin >> x;
                row.push_back(x);
            }
            triangles.push_back(row);
        }

        std::vector<std::vector<int>> prefixSums;
        for (int i = 0; i < N; ++i) {
            std::vector<int> row(1 + 2 * i);
            std::partial_sum(triangles[i].begin(), triangles[i].end(),
                             row.begin());
            prefixSums.push_back(row);
        }

        int maxSum = std::numeric_limits<int>::min();

        // ordinary triangles
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < 1 + 2 * i; j += 2) {
                int curMax = triangles[i][j];
                int curSum = triangles[i][j];

                for (int k = i + 1; k < N; ++k) {
                    int left = j;
                    int right = j + 2 * (k - i);
                    curSum += prefixSums[k][right] -
                              (left ? prefixSums[k][left - 1] : 0);
                    curMax = std::max(curMax, curSum);
                }

                maxSum = std::max(maxSum, curMax);
            }

        // inverted triangles
        for (int i = 0; i < N; ++i)
            for (int j = 1; j < 1 + 2 * i; j += 2) {
                int curMax = triangles[i][j];
                int curSum = triangles[i][j];

                int k = i - 1;
                int left = j - 2;
                int right = j;

                while (k >= 0 && left >= 0 && right < 1 + 2 * k) {
                    curSum += prefixSums[k][right] -
                              (left ? prefixSums[k][left - 1] : 0);
                    curMax = std::max(curMax, curSum);

                    --k;
                    left -= 2;
                }

                maxSum = std::max(maxSum, curMax);
            }

        std::cout << ++T << ". " << maxSum << '\n';
    }

    return 0;
}