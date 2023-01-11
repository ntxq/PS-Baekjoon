#include <algorithm>
#include <iostream>
#include <numeric>
#include <optional>
#include <variant>
#include <vector>

class Shark;
class Smell;

using Sharks = std::vector<Shark>;
using Board = std::vector<std::vector<std::variant<int, Smell>>>;
using Pos = std::tuple<int, int, int>;

struct Smell {
    int sharkId;
    int duration;
};

class Shark {
   private:
    int px = -1;
    int py = -1;

    int x;
    int y;
    int dir;
    int id;
    bool isAlive;

    int priorities[4][4];

    int N;
    static constexpr int dx[4] = {-1, 1, 0, 0};
    static constexpr int dy[4] = {0, 0, -1, 1};

    std::optional<Pos> getEmptyPos(const Board& board) const {
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[priorities[dir][i]];
            int ny = y + dy[priorities[dir][i]];

            if (0 <= nx && nx < N && 0 <= ny && ny < N &&
                std::holds_alternative<Smell>(board[nx][ny]) &&
                std::get<Smell>(board[nx][ny]).sharkId == -1) {
                return Pos{nx, ny, priorities[dir][i]};
            }
        }

        return std::nullopt;
    }

    Pos getMyPos(const Board& board) const {
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[priorities[dir][i]];
            int ny = y + dy[priorities[dir][i]];

            if (0 <= nx && nx < N && 0 <= ny && ny < N &&
                std::holds_alternative<Smell>(board[nx][ny]) &&
                std::get<Smell>(board[nx][ny]).sharkId == id)
                return Pos{nx, ny, priorities[dir][i]};
        }

        return Pos{x, y, dir};
    }

    Pos getPos(const Board& board) const {
        if (auto pos = getEmptyPos(board)) return pos.value();
        return getMyPos(board);
    }

   public:
    Shark() = default;
    Shark(int x, int y, int id, int N)
        : x(x), y(y), id(id), isAlive(true), N(N) {}

    void setDir(int d) { dir = d; }

    void setPriority(int input[4][4]) {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j) priorities[i][j] = input[i][j] - 1;
    }

    void move(Board& board) {
        auto [nx, ny, nDir] = getPos(board);

        px = x;
        py = y;
        x = nx;
        y = ny;
        dir = nDir;
    }

    void update(Board& board, Sharks& sharks) {
        board[px][py] = Smell{id, 1};

        if (auto sh = std::get_if<int>(&board[x][y]); sh && sharks[*sh].id > id)
            sharks[*sh].isAlive = false;
        board[x][y] = id;
    }

    operator bool() const { return isAlive; }
};

bool isOver(const Sharks& sharks) {
    for (unsigned i = 1; i < sharks.size(); ++i)
        if (sharks[i]) return false;
    return true;
}

void updateSmell(Board& board, int K) {
    for (unsigned i = 0; i < board.size(); ++i)
        for (unsigned j = 0; j < board.size(); ++j)
            if (auto smell = std::get_if<Smell>(&board[i][j])) {
                if (smell->duration == K)
                    smell->sharkId = -1;
                else
                    smell->duration++;
            }
}

int run(Board& board, Sharks& sharks, int K) {
    int time = 0;
    while (!isOver(sharks) && time <= 1000) {
        for (unsigned i = sharks.size() - 1; i < sharks.size(); --i)
            if (sharks[i]) sharks[i].move(board);
        for (unsigned i = sharks.size() - 1; i < sharks.size(); --i)
            if (sharks[i]) sharks[i].update(board, sharks);
        updateSmell(board, K);
        ++time;
    }

    return time > 1000 ? -1 : time;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M, K;
    std::cin >> N >> M >> K;

    Board board(N, std::vector<std::variant<int, Smell>>(N, Smell(-1, K)));
    Sharks sharks(M);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            int id;
            std::cin >> id;
            if (id) {
                board[i][j] = id - 1;
                sharks[id - 1] = Shark(i, j, id - 1, N);
            }
        }

    for (int i = 0; i < M; ++i) {
        int d;
        std::cin >> d;
        sharks[i].setDir(d - 1);
    }

    for (int i = 0; i < M; ++i) {
        int input[4][4];
        for (int j = 0; j < 4; ++j)
            for (int k = 0; k < 4; ++k) std::cin >> input[j][k];
        sharks[i].setPriority(input);
    }

    std::cout << run(board, sharks, K) << '\n';

    return 0;
}