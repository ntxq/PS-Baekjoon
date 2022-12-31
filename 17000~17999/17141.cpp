#include <bitset>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using Board = std::vector<std::vector<bool>>;
using Result = std::vector<std::vector<int>>;

Result bfs(const Board& board, const int sx, const int sy, const int N) {
    std::queue<std::pair<int, int>> q;
    Result result(N, std::vector<int>(N, std::numeric_limits<int>::max()));

    q.push({sx, sy});
    result[sx][sy] = 0;

    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (0 <= nx && nx < N && 0 <= ny && ny < N && !board[nx][ny] &&
                result[x][y] + 1 < result[nx][ny]) {
                result[nx][ny] = result[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    return result;
}

int backtrack(const Board& board, const std::vector<Result>& results, int count,
              int N) {
    std::vector<bool> permutations(results.size(), false);
    std::fill(permutations.begin(), permutations.begin() + count, true);
    std::sort(permutations.begin(), permutations.end());

    int maxTime = std::numeric_limits<int>::max();
    do {
        Result curMin(N, std::vector<int>(N, std::numeric_limits<int>::max()));
        for (unsigned i = 0; i < permutations.size(); ++i)
            if (permutations[i])
                for (int j = 0; j < N; ++j)
                    for (int k = 0; k < N; ++k)
                        curMin[j][k] = std::min(curMin[j][k], results[i][j][k]);

        int curMax = 0;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (!board[i][j]) curMax = std::max(curMax, curMin[i][j]);
        maxTime = std::min(maxTime, curMax);
    } while (std::next_permutation(permutations.begin(), permutations.end()));

    return maxTime == std::numeric_limits<int>::max() ? -1 : maxTime;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    Board board(N, std::vector<bool>(N, false));
    std::vector<std::pair<int, int>> candidates;

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            int x;
            std::cin >> x;

            board[i][j] = x == 1;
            if (x == 2) candidates.push_back({i, j});
        }

    std::vector<Result> results;
    for (const auto& [x, y] : candidates)
        results.push_back(bfs(board, x, y, N));

    std::cout << backtrack(board, results, M, N) << '\n';

    return 0;
}
