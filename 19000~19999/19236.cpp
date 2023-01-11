#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

class Fish;
class Shark;

using Fishes = std::vector<Fish>;
using Board = std::vector<std::vector<int>>;

class Fish {
    friend Shark;

   private:
    static constexpr int dx[8]{-1, -1, 0, 1, 1, 1, 0, -1};
    static constexpr int dy[8]{0, -1, -1, -1, 0, 1, 1, 1};

    int x, y, dir;
    bool isAlive;

    void rotate() { dir = (dir + 1) % 8; }
    bool canMove(Board& board) const {
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        return 0 <= nx && nx < 4 && 0 <= ny && ny < 4 && board[nx][ny] != 16;
    }
    void move(Fishes& fishes, Board& board) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        if (board[nx][ny] == -1) {
            std::swap(board[x][y], board[nx][ny]);

            x = nx;
            y = ny;
        } else {
            Fish& other = fishes[board[nx][ny]];
            std::swap(board[x][y], board[nx][ny]);

            std::swap(x, other.x);
            std::swap(y, other.y);
        }
    }

   public:
    Fish() = default;
    Fish(int x, int y, int dir) : x(x), y(y), dir(dir), isAlive(true){};

    operator bool() const { return isAlive; }
    void run(Fishes& fishes, Board& board) {
        bool isMoved = false;
        for (int i = 0; i < 8 && !isMoved; ++i)
            if (canMove(board)) {
                move(fishes, board);
                isMoved = true;
            } else {
                rotate();
            }
    }
};

class Shark {
   private:
    static constexpr int dx[8]{-1, -1, 0, 1, 1, 1, 0, -1};
    static constexpr int dy[8]{0, -1, -1, -1, 0, 1, 1, 1};

    int score;
    int x, y, dir;
    bool isAlive;

   public:
    Shark(Fishes& fishes, Board& board) : score(board[0][0] + 1) {
        Fish& target = fishes[board[0][0]];

        score = board[0][0] + 1;
        x = 0;
        y = 0;
        dir = target.dir;
        target.isAlive = false;
        board[0][0] = 16;
    };

    operator bool() const { return isAlive; }
    bool canMove(int dist, Board& board) const {
        int nx = x + dx[dir] * dist;
        int ny = y + dy[dir] * dist;

        return 0 <= nx && nx < 4 && 0 <= ny && ny < 4 && board[nx][ny] != -1;
    }
    void move(int dist, Fishes& fishes, Board& board) {
        int nx = x + dx[dir] * dist;
        int ny = y + dy[dir] * dist;

        // std::cout << "Moving to " << nx << " " << ny << '\n';
        Fish& target = fishes[board[nx][ny]];
        board[x][y] = -1;

        score += board[nx][ny] + 1;
        x = target.x;
        y = target.y;
        dir = target.dir;
        target.isAlive = false;

        board[nx][ny] = 16;
    }

    int getScore() const { return score; }
};

int run(Shark sh, Fishes fishes, Board board) {
    for (int i = 0; i < 16; ++i)
        if (fishes[i]) fishes[i].run(fishes, board);

    int maxScore = sh.getScore();
    for (int i = 1; i < 5; ++i)
        if (sh.canMove(i, board)) {
            Shark nSh = sh;
            Fishes nFishes = fishes;
            Board nBoard = board;

            nSh.move(i, nFishes, nBoard);
            maxScore = std::max(maxScore, run(nSh, nFishes, nBoard));
        }

    return maxScore;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    Fishes fishes(16);
    Board board(4);

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            int a, b;
            std::cin >> a >> b;

            fishes[a - 1] = Fish(i, j, b - 1);
            board[i].push_back(a - 1);
        }

    Shark shark(fishes, board);

    std::cout << run(shark, fishes, board) << '\n';

    return 0;
}