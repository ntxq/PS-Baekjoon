#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

class Board {
   private:
    std::vector<std::vector<bool>> board;
    int rotation;

   public:
    Board() : board(5, std::vector<bool>(5)), rotation(0) {
        for (int i = 0; i < 5; ++i)
            for (int j = 0; j < 5; ++j) {
                bool b;
                std::cin >> b;
                board[i][j] = b;
            }
    }

    void setRotation(int r) { rotation = r; }

    bool get(int x, int y) const {
        switch (rotation) {
            case 0:
                return board[x][y];

            case 1:
                return board[4 - y][x];

            case 2:
                return board[4 - x][4 - y];

            case 3:
                return board[y][4 - x];

            default:
                throw std::runtime_error("Invalid rotation");
        }
    }
};

class Cube {
   private:
    std::vector<Board> boards;

    int bfs(const std::vector<int>& boardOrder,
            const std::vector<int>& boardRotations) {
        for (int i = 0; i < 5; ++i) boards[i].setRotation(boardRotations[i]);

        std::queue<std::tuple<int, int, int>> q;
        int dist[5][5][5] = {};
        std::fill(&dist[0][0][0], &dist[0][0][0] + 5 * 5 * 5,
                  std::numeric_limits<int>::max());

        if (boards[boardOrder[0]].get(0, 0)) {
            q.push({0, 0, 0});
            dist[0][0][0] = 0;
        }

        int dx[6] = {1, -1, 0, 0, 0, 0};
        int dy[6] = {0, 0, 1, -1, 0, 0};
        int dz[6] = {0, 0, 0, 0, 1, -1};

        while (!q.empty() && dist[4][4][4] == std::numeric_limits<int>::max()) {
            auto [x, y, z] = q.front();
            q.pop();

            for (int i = 0; i < 6; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                int nz = z + dz[i];

                if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5 || nz < 0 || nz >= 5)
                    continue;

                if (!boards[boardOrder[nz]].get(nx, ny)) continue;

                if (dist[x][y][z] + 1 < dist[nx][ny][nz]) {
                    dist[nx][ny][nz] = dist[x][y][z] + 1;
                    q.push({nx, ny, nz});
                }
            }
        }

        return dist[4][4][4];
    }

    int backtrack(std::vector<int>& rotations, const std::vector<int>& order) {
        if (rotations.size() == 5) return bfs(order, rotations);

        int minDist = std::numeric_limits<int>::max();
        for (int i = 0; i < 4; ++i) {
            rotations.push_back(i);
            minDist = std::min(minDist, backtrack(rotations, order));
            rotations.pop_back();
        }

        return minDist;
    }

   public:
    Cube() : boards(5) {}

    int run() {
        std::vector<int> order(5);
        std::iota(order.begin(), order.end(), 0);

        int minDist = std::numeric_limits<int>::max();
        do {
            std::vector<int> rotations;
            minDist = std::min(minDist, backtrack(rotations, order));
        } while (std::next_permutation(order.begin(), order.end()));

        return minDist;
    }
};

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    Cube cube;
    int minDist = cube.run();
    std::cout << (minDist == std::numeric_limits<int>::max() ? -1 : minDist)
              << '\n';

    return 0;
}
