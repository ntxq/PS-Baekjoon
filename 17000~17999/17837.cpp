#include <algorithm>
#include <deque>
#include <iostream>

struct Piece {
    int x, y, dir;
};

struct State {
    int x, y;
    std::vector<int> members;

    State() : x(-1), y(-1) {}
    State(int x, int y) : x(x), y(y) {}

    void flip(int piece) {
        auto it = std::find(members.begin(), members.end(), piece);
        std::reverse(it, members.end());
    }

    friend bool move(State& from, State& to, std::vector<Piece>& pieces,
                     int piece) {
        const int tx = to.x, ty = to.y;

        auto it = std::find(from.members.begin(), from.members.end(), piece);
        std::for_each(it, from.members.end(), [&](int p) {
            pieces[p].x = tx;
            pieces[p].y = ty;
        });
        std::move(it, from.members.end(), std::back_inserter(to.members));
        from.members.erase(it, from.members.end());

        return to.members.size() >= 4;
    }
};

int flipDir(int dir) {
    switch (dir) {
        case 0:
            return 1;
        case 1:
            return 0;
        case 2:
            return 3;
        case 3:
            return 2;
    }

    return -1;
}

bool moveWhite(State& from, State& to, std::vector<Piece>& pieces, int piece) {
    return move(from, to, pieces, piece);
}

bool moveRed(State& from, State& to, std::vector<Piece>& pieces, int piece) {
    bool isFinished = move(from, to, pieces, piece);
    to.flip(piece);
    return isFinished;
}

int run(std::vector<Piece>& pieces, std::vector<std::vector<int>>& board,
        std::vector<std::vector<State>>& states, const int N, const int K) {
    int turn = 0;
    bool isFinished = false;

    int dx[] = {0, 0, -1, 1};
    int dy[] = {1, -1, 0, 0};

    while (turn <= 1000 && !isFinished) {
        ++turn;

        for (int i = 0; i < K; ++i) {
            auto [x, y, dir] = pieces[i];
            int nx = x + dx[dir], ny = y + dy[dir];

            if (0 <= nx && nx < N && 0 <= ny && ny < N && board[nx][ny] == 0)
                isFinished |=
                    moveWhite(states[x][y], states[nx][ny], pieces, i);
            else if (0 <= nx && nx < N && 0 <= ny && ny < N &&
                     board[nx][ny] == 1)
                isFinished |= moveRed(states[x][y], states[nx][ny], pieces, i);
            else if (0 > nx || nx >= N || 0 > ny || ny >= N ||
                     board[nx][ny] == 2) {
                pieces[i].dir = dir = flipDir(dir);
                nx = x + dx[dir], ny = y + dy[dir];

                if (0 <= nx && nx < N && 0 <= ny && ny < N &&
                    board[nx][ny] == 0)
                    isFinished |=
                        moveWhite(states[x][y], states[nx][ny], pieces, i);
                else if (0 <= nx && nx < N && 0 <= ny && ny < N &&
                         board[nx][ny] == 1)
                    isFinished |=
                        moveRed(states[x][y], states[nx][ny], pieces, i);
            }
        }
    }

    return isFinished ? turn : -1;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, K;
    std::cin >> N >> K;

    std::vector<Piece> pieces(K);
    std::vector<std::vector<int>> board(N, std::vector<int>(N));
    std::vector<std::vector<State>> states(N);

    for (auto& row : board)
        for (auto& cell : row) std::cin >> cell;

    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j) states[i].emplace_back(i, j);}

    for (int i = 0; i < K; ++i) {
        int x, y, dir;
        std::cin >> x >> y >> dir;
        --x, --y, --dir;

        pieces[i] = {x, y, dir};
        states[x][y].members.push_back(i);
    }

    std::cout << run(pieces, board, states, N, K) << '\n';

    return 0;
}
