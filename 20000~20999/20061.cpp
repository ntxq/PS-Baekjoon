#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

class MonominoDomino {
   private:
    std::vector<std::vector<bool>> board =
        std::vector<std::vector<bool>>(6, std::vector<bool>(4));
    int score = 0;

    void insertSingle(int sx, int sy) {
        int nx = sx;
        while (nx < 5 && !board[nx + 1][sy]) ++nx;
        board[nx][sy] = true;
    }

    void insertVertical(int sx, int sy) {
        int nx = sx + 1;
        while (nx < 5 && !board[nx + 1][sy]) ++nx;
        board[nx - 1][sy] = board[nx][sy] = true;
    }

    void insertHorizontal(int sx, int sy) {
        int nx = sx;
        while (nx < 5 && !board[nx + 1][sy] && !board[nx + 1][sy + 1]) ++nx;
        board[nx][sy] = board[nx][sy + 1] = true;
    }

    bool shouldErase(int row) const {
        for (int i = 0; i < 4; ++i)
            if (!board[row][i]) return false;
        return true;
    }

    void pullRows(int from) {
        for (int row = from; row > 0; --row)
            for (int i = 0; i < 4; ++i) board[row][i] = board[row - 1][i];
        for (int i = 0; i < 4; ++i) board[0][i] = false;
    }

    void eraseFilled() {
        for (int row = 5; row >= 0; --row)
            while (shouldErase(row)) {
                ++score;
                pullRows(row);
            }
    }

    bool shouldEraseSpecial() const {
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 4; ++j)
                if (board[i][j]) return true;
        return false;
    }

   public:
    enum Block { SINGLE, VERTICAL, HORIZONTAL };

    void insert(int sx, int sy, Block type) {
        switch (type) {
            case SINGLE:
                insertSingle(sx, sy);
                break;
            case VERTICAL:
                insertVertical(sx, sy);
                break;
            case HORIZONTAL:
                insertHorizontal(sx, sy);
                break;
        }
        eraseFilled();

        while (shouldEraseSpecial()) pullRows(5);
    }

    int getScore() const { return score; }
    int getTiles() const {
        int count = 0;
        for (int i = 0; i < 6; ++i)
            for (int j = 0; j < 4; ++j)
                if (board[i][j]) ++count;
        return count;
    }
};

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    MonominoDomino green;
    MonominoDomino blue;

    int N;
    std::cin >> N;

    while (N--) {
        int t, x, y;
        std::cin >> t >> x >> y;

        using enum MonominoDomino::Block;
        switch (t) {
            case 1:
                green.insert(0, y, SINGLE);
                blue.insert(0, 3 - x, SINGLE);
                break;
            case 2:
                green.insert(0, y, HORIZONTAL);
                blue.insert(0, 3 - x, VERTICAL);
                break;
            case 3:
                green.insert(0, y, VERTICAL);
                blue.insert(0, 2 - x, HORIZONTAL);
                break;
        }
    }

    std::cout << green.getScore() + blue.getScore() << '\n'
              << green.getTiles() + blue.getTiles() << '\n';

    return 0;
}