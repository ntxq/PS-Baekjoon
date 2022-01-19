#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

int findFish(int& x, int& y, int size, int n,
             std::vector<std::vector<int>>& fish, std::vector<int>& fishCount) {
    std::vector<std::vector<int>> visited(n, std::vector<int>(n));
    std::queue<std::pair<int, int>> q;

    q.push({x, y});
    visited[x][y] = 1;

    bool found = false;
    while (!q.empty() & !found) {
        unsigned curSize = q.size();

        for (unsigned l = 0; l < curSize; ++l) {
            auto [i, j] = q.front();
            q.pop();

            if (i > 0 && !visited[i - 1][j] && fish[i - 1][j] <= size) {
                q.push({i - 1, j});
                visited[i - 1][j] = visited[i][j] + 1;

                if (fish[i - 1][j] && fish[i - 1][j] < size) found = true;
            }

            if (j > 0 && !visited[i][j - 1] && fish[i][j - 1] <= size) {
                q.push({i, j - 1});
                visited[i][j - 1] = visited[i][j] + 1;

                if (fish[i][j - 1] && fish[i][j - 1] < size) found = true;
            }

            if (i < n - 1 && !visited[i + 1][j] && fish[i + 1][j] <= size) {
                q.push({i + 1, j});
                visited[i + 1][j] = visited[i][j] + 1;

                if (fish[i + 1][j] && fish[i + 1][j] < size) found = true;
            }

            if (j < n - 1 && !visited[i][j + 1] && fish[i][j + 1] <= size) {
                q.push({i, j + 1});
                visited[i][j + 1] = visited[i][j] + 1;

                if (fish[i][j + 1] && fish[i][j + 1] < size) found = true;
            }
        }
    }

    if (found) {
        int curX = n, curY = n;
        while (!q.empty()) {
            auto [i, j] = q.front();
            q.pop();

            if (fish[i][j] && fish[i][j] < size) {
                if (i < curX || (i == curX && j < curY)) {
                    curX = i;
                    curY = j;
                }
            }
        }

        --fishCount[fish[curX][curY]];
        fish[curX][curY] = 0;
        x = curX;
        y = curY;
    }

    return visited[x][y] - 1;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> water(n, std::vector<int>(n));
    std::vector<int> fishCount(7);

    int x, y;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int num;
            std::cin >> num;

            if (num == 9) {
                x = i;
                y = j;
                water[i][j] = 0;
            } else {
                ++fishCount[num];
                water[i][j] = num;
            }
        }
    }

    int time = 0;
    int size = 2;
    int growth = 0;
    for (int i = 1; i < 7; ++i) {
        while (fishCount[i]) {
            int dist = findFish(x, y, size, n, water, fishCount);
            if (!dist) break;

            time += dist;
            ++growth;

            if (growth == size) {
                growth = 0;
                ++size;
            }
        }
    }

    std::cout << time;

    return 0;
}