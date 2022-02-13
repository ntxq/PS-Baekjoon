#include <algorithm>
#include <iostream>
#include <vector>

enum class Move { Left, Right, Up, Down };

std::vector<std::vector<int>> moveBoard(std::vector<std::vector<int>> board,
                                        Move move) {
    switch (move) {
        case Move::Left:
            for (std::size_t i = 0; i < board.size() - 1; ++i) {
                for (std::size_t j = 0; j < board[i].size(); ++j) {
                    bool moved = false;
                    for (std::size_t k = i + 1; k < board.size() && !moved;
                         ++k) {
                        if (!board[j][i] && board[j][k]) {
                            board[j][i] = board[j][k];
                            board[j][k] = 0;
                        } else if (board[j][i] && board[j][i] == board[j][k]) {
                            board[j][i] *= 2;
                            board[j][k] = 0;
                            moved = true;
                        } else if (board[j][k]) {
                            moved = true;
                        }
                    }
                }
            }
            break;

        case Move::Right:
            for (std::size_t i = board.size() - 1; i > 0; --i) {
                for (std::size_t j = 0; j < board[i].size(); ++j) {
                    bool moved = false;
                    for (std::size_t k = i - 1; k < i && !moved; --k) {
                        if (!board[j][i] && board[j][k]) {
                            board[j][i] = board[j][k];
                            board[j][k] = 0;
                        } else if (board[j][i] && board[j][i] == board[j][k]) {
                            board[j][i] *= 2;
                            board[j][k] = 0;
                            moved = true;
                        } else if (board[j][k]) {
                            moved = true;
                        }
                    }
                }
            }
            break;

        case Move::Up:
            for (std::size_t i = 0; i < board.size() - 1; ++i) {
                for (std::size_t j = 0; j < board[i].size(); ++j) {
                    bool moved = false;
                    for (std::size_t k = i + 1; k < board.size() && !moved;
                         ++k) {
                        if (!board[i][j] && board[k][j]) {
                            board[i][j] = board[k][j];
                            board[k][j] = 0;
                        } else if (board[i][j] && board[i][j] == board[k][j]) {
                            board[i][j] *= 2;
                            board[k][j] = 0;
                            moved = true;
                        } else if (board[k][j]) {
                            moved = true;
                        }
                    }
                }
            }
            break;

        case Move::Down:
            for (std::size_t i = board.size() - 1; i > 0; --i) {
                for (std::size_t j = 0; j < board[i].size(); ++j) {
                    bool moved = false;
                    for (std::size_t k = i - 1; k < i && !moved; --k) {
                        if (!board[i][j] && board[k][j]) {
                            board[i][j] = board[k][j];
                            board[k][j] = 0;
                        } else if (board[i][j] && board[i][j] == board[k][j]) {
                            board[i][j] *= 2;
                            board[k][j] = 0;
                            moved = true;
                        } else if (board[k][j]) {
                            moved = true;
                        }
                    }
                }
            }
            break;

        default:
            break;
    }

    return board;
}

int backtrack(const std::vector<std::vector<int>>& board, int level = 0) {
    int max = 0;
    if (level == 5) {
        for (const auto& row : board)
            for (const auto& col : row)
                if (col > max) max = col;

        return max;
    }

    for (Move m : {Move::Left, Move::Right, Move::Up, Move::Down})
        if (int curMax = backtrack(moveBoard(board, m), level + 1);
            curMax > max)
            max = curMax;

    return max;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> board(n, std::vector<int>(n));
    for (auto& row : board)
        for (auto& col : row) std::cin >> col;

    std::cout << backtrack(board);

    return 0;
}