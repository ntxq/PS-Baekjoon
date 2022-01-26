#include <iostream>
#include <utility>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> graph(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) std::cin >> graph[i][j];

    std::vector<std::vector<int>> dpH(n, std::vector<int>(n));
    std::vector<std::vector<int>> dpV(n, std::vector<int>(n));
    std::vector<std::vector<int>> dpD(n, std::vector<int>(n));

    dpH[0][1] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i + 1 < n && !graph[i + 1][j])
                dpV[i + 1][j] += dpV[i][j] + dpD[i][j];

            if (i + 1 < n && j + 1 < n && !graph[i + 1][j] &&
                !graph[i][j + 1] && !graph[i + 1][j + 1])
                dpD[i + 1][j + 1] += dpH[i][j] + dpV[i][j] + dpD[i][j];

            if (j + 1 < n && !graph[i][j + 1])
                dpH[i][j + 1] += dpH[i][j] + dpD[i][j];
        }
    }

    std::cout << dpH[n - 1][n - 1] + dpV[n - 1][n - 1] + dpD[n - 1][n - 1];

    return 0;
}