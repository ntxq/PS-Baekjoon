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

        std::vector<std::vector<int>> mines(10001, std::vector<int>(10001));
        for (int i = 0; i < N; ++i) {
            int x, y;
            std::cin >> x >> y;
            mines[x][y] = 1;
        }

        for (int i = 0; i < 10001; ++i)
            for (int j = 0; j < 10001; ++j)
                if (i > 0 && j > 0)
                    mines[i][j] +=
                        mines[i - 1][j] + mines[i][j - 1] - mines[i - 1][j - 1];
                else if (i > 0)
                    mines[i][j] += mines[i - 1][j];
                else if (j > 0)
                    mines[i][j] += mines[i][j - 1];

        int maxCnt = 0;
        for (int i = 10; i < 10001; ++i)
            for (int j = 10; j < 10001; ++j) {
                int cnt = 0;
                if (i > 10 && j > 10)
                    cnt = mines[i][j] - mines[i - 11][j] - mines[i][j - 11] +
                          mines[i - 11][j - 11];
                else if (i > 10)
                    cnt = mines[i][j] - mines[i - 11][j];
                else if (j > 10)
                    cnt = mines[i][j] - mines[i][j - 11];
                else
                    cnt = mines[i][j];

                maxCnt = std::max(maxCnt, cnt);
            }

        std::cout << maxCnt << '\n';
    }

    return 0;
}
