#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> dx{-1, 0, 1};
    std::vector<int> dy{-1, 0, 1};
    std::vector<std::vector<long long>> dist{
        {2, 1, 2},
        {1, 0, 1},
        {2, 1, 2},
    };

    int prevX, prevY;
    std::cin >> prevX >> prevY;

    while (N--) {
        int curX, curY;
        std::cin >> curX >> curY;

        std::vector<std::vector<long long>> newDist(
            3,
            std::vector<long long>(3, std::numeric_limits<long long>::max()));

        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                if (dx[i] * dy[j] != 0) continue;

                long long vx = curX + dx[i];
                long long vy = curY + dy[j];

                for (int k = 0; k < 3; ++k)
                    for (int l = 0; l < 3; ++l) {
                        if (dx[k] * dy[l] != 0) continue;

                        long long ux = prevX + dx[k];
                        long long uy = prevY + dy[l];

                        long long d =
                            std::abs(vx - ux) + std::abs(vy - uy) + dist[k][l];
                        newDist[i][j] = std::min(newDist[i][j], d);
                    }
            }

        prevX = curX;
        prevY = curY;
        dist = std::move(newDist);
    }

    long long minDist = std::numeric_limits<long long>::max();
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) minDist = std::min(minDist, dist[i][j]);
    std::cout << minDist << '\n';

    return 0;
}
