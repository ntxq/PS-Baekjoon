#include <algorithm>
#include <deque>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

struct Piece {
    int x, y, dir;
};

class State {
   private:
    int top;
    int bottom;
    int size;

   public:
    State() : top(-1), bottom(-1), size(0) {}
    State(int i) : top(i), bottom(i), size(1) {}

    int getBottom() const { return bottom; }
    int getTop() const { return top; }

    void flip() { std::swap(top, bottom); }
    void clear() {
        top = bottom = -1;
        size = 0;
    }

    friend bool move(State& from, State& to) {
        if (to.bottom == -1) {
            to.bottom = from.bottom;
            to.top = from.top;
            to.size = from.size;
            from.clear();
        } else {
            to.top = from.top;
            to.size += from.size;
            from.clear();
        }

        return to.size >= 4;
    }
};

int flipDir(int dir) {
    switch (dir) {
        case 1:
            return 2;
            break;

        case 2:
            return 1;
            break;

        case 3:
            return 4;
            break;

        case 4:
            return 3;
            break;

        default:
            return -1;
            break;
    }
}

int run(std::vector<Piece>& pieces, std::vector<std::vector<State>>& states,
        std::vector<std::vector<int>>& board, const int N, const int K) {
    int turn = 0;
    bool isFinished = false;

    int dx[] = {0, 0, 0, -1, 1};
    int dy[] = {0, 1, -1, 0, 0};

    while (!isFinished && turn <= 1000) {
        for (int i = 0; i < K && !isFinished; ++i) {
            auto [x, y, dir] = pieces[i];
            if (states[x][y].getBottom() != i) continue;

            int nx = x + dx[dir];
            int ny = y + dy[dir];

            // White
            if (0 <= nx && nx < N && 0 <= ny && ny < N && board[nx][ny] == 0) {
                int top = states[x][y].getTop();
                pieces[top] = {nx, ny, pieces[top].dir};

                isFinished |= move(states[x][y], states[nx][ny]);

                pieces[i] = {nx, ny, dir};
            }
            // Red
            else if (0 <= nx && nx < N && 0 <= ny && ny < N &&
                     board[nx][ny] == 1) {
                int top = states[x][y].getTop();
                pieces[top] = {nx, ny, pieces[top].dir};

                states[x][y].flip();
                isFinished |= move(states[x][y], states[nx][ny]);

                pieces[i] = {nx, ny, dir};
            }
            // Blue or Out of bound
            else if (nx < 0 || nx >= N || ny < 0 || ny >= N ||
                     board[nx][ny] == 2) {
                pieces[i].dir = flipDir(dir);
                nx = x + dx[pieces[i].dir];
                ny = y + dy[pieces[i].dir];

                if (0 <= nx && nx < N && 0 <= ny && ny < N) {
                    if (board[nx][ny] == 0) {
                        int top = states[x][y].getTop();
                        pieces[top] = {nx, ny, pieces[top].dir};

                        isFinished |= move(states[x][y], states[nx][ny]);

                        pieces[i] = {nx, ny, pieces[i].dir};
                    } else if (board[nx][ny] == 1) {
                        int top = states[x][y].getTop();
                        pieces[top] = {nx, ny, pieces[top].dir};
    
                        states[x][y].flip();
                        isFinished |= move(states[x][y], states[nx][ny]);

                        pieces[i] = {nx, ny, pieces[i].dir};
                    }
                }
            }
        }
        ++turn;
    }

    return isFinished ? turn : -1;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, K;
    std::cin >> N >> K;

    std::vector<Piece> pieces(K);
    std::vector<std::vector<State>> states(N, std::vector<State>(N));
    std::vector<std::vector<int>> board(N, std::vector<int>(N));

    for (auto& row : board)
        for (auto& cell : row) std::cin >> cell;

    for (int i = 0; i < K; ++i) {
        int x, y, dir;
        std::cin >> x >> y >> dir;
        --x, --y;

        pieces[i] = {x, y, dir};
        states[x][y] = State(i);
    }

    std::cout << run(pieces, states, board, N, K) << '\n';

    return 0;
}
