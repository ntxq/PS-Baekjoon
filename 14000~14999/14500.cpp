#include <algorithm>
#include <iostream>
#include <vector>

int findMax(int n, int m, const std::vector<std::vector<int>>& paper) {
    int max = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if (i < n - 3) {
                if (int s = paper[i][j] + paper[i + 1][j] + paper[i + 2][j] +
                            paper[i + 3][j];
                    s > max)
                    max = s;
            }

            if (j < m - 3) {
                if (int s = paper[i][j] + paper[i][j + 1] + paper[i][j + 2] +
                            paper[i][j + 3];
                    s > max)
                    max = s;
            }

            if (i < n - 1 && j < m - 1) {
                if (int s = paper[i][j] + paper[i][j + 1] + paper[i + 1][j] +
                            paper[i + 1][j + 1];
                    s > max)
                    max = s;
            }

            if (i < n - 2 && j < m - 1) {
                if (int s = paper[i][j] + paper[i][j + 1] + paper[i + 1][j] +
                            paper[i + 2][j];
                    s > max)
                    max = s;

                if (int s = paper[i][j] + paper[i + 1][j] + paper[i + 2][j] +
                            paper[i + 2][j + 1];
                    s > max)
                    max = s;

                if (int s = paper[i][j] + paper[i][j + 1] +
                            paper[i + 1][j + 1] + paper[i + 2][j + 1];
                    s > max)
                    max = s;

                if (int s = paper[i][j + 1] + paper[i + 1][j + 1] +
                            paper[i + 2][j] + paper[i + 2][j + 1];
                    s > max)
                    max = s;

                if (int s = paper[i][j] + paper[i + 1][j] +
                            paper[i + 1][j + 1] + paper[i + 2][j + 1];
                    s > max)
                    max = s;

                if (int s = paper[i][j + 1] + paper[i + 1][j] +
                            paper[i + 1][j + 1] + paper[i + 2][j];
                    s > max)
                    max = s;

                if (int s = paper[i][j] + paper[i + 1][j] +
                            paper[i + 1][j + 1] + paper[i + 2][j];
                    s > max)
                    max = s;

                if (int s = paper[i][j + 1] + paper[i + 1][j] +
                            paper[i + 1][j + 1] + paper[i + 2][j + 1];
                    s > max)
                    max = s;
            }

            if (i < n - 1 && j < m - 2) {
                if (int s = paper[i][j] + paper[i][j + 1] + paper[i][j + 2] +
                            paper[i + 1][j];
                    s > max)
                    max = s;
                if (int s = paper[i][j] + paper[i][j + 1] + paper[i][j + 2] +
                            paper[i + 1][j + 2];
                    s > max)
                    max = s;

                if (int s = paper[i][j] + paper[i + 1][j] +
                            paper[i + 1][j + 1] + paper[i + 1][j + 2];
                    s > max)
                    max = s;

                if (int s = paper[i][j + 2] + paper[i + 1][j] +
                            paper[i + 1][j + 1] + paper[i + 1][j + 2];
                    s > max)
                    max = s;

                if (int s = paper[i][j] + paper[i][j + 1] +
                            paper[i + 1][j + 1] + paper[i + 1][j + 2];
                    s > max)
                    max = s;

                if (int s = paper[i][j + 1] + paper[i][j + 2] +
                            paper[i + 1][j] + paper[i + 1][j + 1];
                    s > max)
                    max = s;

                if (int s = paper[i][j] + paper[i][j + 1] + paper[i][j + 2] +
                            paper[i + 1][j + 1];
                    s > max)
                    max = s;

                if (int s = paper[i][j + 1] + paper[i + 1][j] +
                            paper[i + 1][j + 1] + paper[i + 1][j + 2];
                    s > max)
                    max = s;
            }
        }

    return max;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> paper(n, std::vector<int>(m));
    for (auto& row : paper)
        for (auto& col : row) std::cin >> col;

    std::cout << findMax(n, m, paper);

    return 0;
}