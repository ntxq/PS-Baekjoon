#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

const int MAX_N = 61;

void backtrack(int x, int y, std::vector<std::vector<bool>>& visited) {
    std::vector<int> dx{-1, 0, 1, 0};
    std::vector<int> dy{0, 1, 0, -1};
    std::vector<std::string> dir{"SOUTH", "EAST", "NORTH", "WEST"};

    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (0 <= nx && nx < MAX_N && 0 <= ny && ny < MAX_N &&
            !visited[nx][ny]) {
            std::cout << dir[i] << std::endl;

            std::string response;
            std::cin >> response;

            visited[nx][ny] = true;
            if (response == "EMPTY") {
                backtrack(nx, ny, visited);
                std::cout << dir[(i + 2) % 4] << std::endl;
                std::cin >> response;  // Ignore response
            }
        }
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<std::vector<bool>> visited(MAX_N,
                                           std::vector<bool>(MAX_N, false));
    visited[30][30] = true;
    backtrack(30, 30, visited);

    return 0;
}
