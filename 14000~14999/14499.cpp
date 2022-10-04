#include <algorithm>
#include <iostream>
#include <optional>
#include <vector>

class Dice {
   private:
    std::vector<std::vector<int>> board;
    const int N, M;

    int x, y;
    int top, front, right, left, back, bottom;

    constexpr static int dx[4] = {1, -1, 0, 0};
    constexpr static int dy[4] = {0, 0, -1, 1};

   public:
    enum Direction { EAST, WEST, NORTH, SOUTH };
    Dice(int N, int M, const std::vector<std::vector<int>>& board, int x, int y)
        : board(board),
          N(N),
          M(M),
          x(x),
          y(y),
          top(),
          front(),
          right(),
          left(),
          back(),
          bottom() {}

    std::optional<int> roll(Direction d) {
        int nx = x + dx[d];
        int ny = y + dy[d];

        if (nx < 0 || nx >= M || ny < 0 || ny >= N) return std::nullopt;

        switch (d) {
            case EAST:
                std::swap(top, left);
                std::swap(left, bottom);
                std::swap(bottom, right);
                break;
            case WEST:
                std::swap(top, right);
                std::swap(right, bottom);
                std::swap(bottom, left);
                break;
            case NORTH:
                std::swap(top, back);
                std::swap(back, bottom);
                std::swap(bottom, front);
                break;
            case SOUTH:
                std::swap(top, front);
                std::swap(front, bottom);
                std::swap(bottom, back);
                break;
        }

        x = nx;
        y = ny;
        if (board[y][x] == 0)
            board[y][x] = bottom;
        else {
            bottom = board[y][x];
            board[y][x] = 0;
        }

        return top;
    }
};

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M, x, y, K;
    std::cin >> N >> M >> y >> x >> K;

    std::vector<std::vector<int>> board(N, std::vector<int>(M));
    for (auto& i : board)
        for (auto& j : i) std::cin >> j;

    Dice dice(N, M, board, x, y);
    for (int i = 0; i < K; ++i) {
        int d;
        std::cin >> d;
        auto res = dice.roll(static_cast<Dice::Direction>(d - 1));
        if (res.has_value()) std::cout << res.value() << '\n';
    }

    return 0;
}