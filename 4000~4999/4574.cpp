#include <iostream>
#include <string>
#include <vector>

std::vector<std::vector<int>> board(9, std::vector<int>(9));
std::vector<std::vector<bool>> rows(9, std::vector<bool>(9, false));
std::vector<std::vector<bool>> cols(9, std::vector<bool>(9, false));
std::vector<std::vector<bool>> squares(9, std::vector<bool>(9, false));

std::vector<std::vector<bool>> domino(9, std::vector<bool>(9));

void insert(char row, int col, int num) {
    int r = row - 'A';
    int c = col - 1;
    int n = num - 1;

    board[r][c] = num;
    rows[r][n] = true;
    cols[c][n] = true;
    squares[(r / 3) * 3 + c / 3][n] = true;
}

void remove(char row, int col, int num) {
    int r = row - 'A';
    int c = col - 1;
    int n = num - 1;

    board[r][c] = 0;
    rows[r][n] = false;
    cols[c][n] = false;
    squares[(r / 3) * 3 + c / 3][n] = false;
}

bool check(int row, int col, int num) {
    return 0 <= row && row < 9 && 0 <= col && col < 9 && !board[row][col] &&
           !rows[row][num] && !cols[col][num] &&
           !squares[(row / 3) * 3 + col / 3][num];
}

bool backtrack(int idx) {
    if (idx == 81) return true;

    int row = idx / 9;
    int col = idx % 9;

    if (board[row][col]) return backtrack(idx + 1);

    for (int i = 0; i < 9; ++i)
        if (check(row, col, i))
            for (int j = 0; j < 9; ++j)
                if (i != j && !domino[i][j] && !domino[j][i]) {
                    if (check(row, col + 1, j)) {
                        insert(row + 'A', col + 1, i + 1);
                        insert(row + 'A', col + 2, j + 1);
                        domino[i][j] = true;

                        if (backtrack(idx + 1)) return true;

                        domino[i][j] = false;
                        remove(row + 'A', col + 1, i + 1);
                        remove(row + 'A', col + 2, j + 1);
                    }

                    if (check(row + 1, col, j)) {
                        insert(row + 'A', col + 1, i + 1);
                        insert(row + 'A' + 1, col + 1, j + 1);
                        domino[i][j] = true;

                        if (backtrack(idx + 1)) return true;

                        domino[i][j] = false;
                        remove(row + 'A', col + 1, i + 1);
                        remove(row + 'A' + 1, col + 1, j + 1);
                    }
                }

    return false;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T = 0;
    int N;
    while (std::cin >> N && N) {
        board.assign(9, std::vector<int>(9));
        rows.assign(9, std::vector<bool>(9, false));
        cols.assign(9, std::vector<bool>(9, false));
        squares.assign(9, std::vector<bool>(9, false));
        domino.assign(9, std::vector<bool>(9));

        for (int i = 0; i < N; ++i) {
            int num;
            char row;
            int col;

            std::cin >> num >> row >> col;
            insert(row, col, num);

            int num2;
            char row2;
            int col2;

            std::cin >> num2 >> row2 >> col2;
            insert(row2, col2, num2);

            domino[num - 1][num2 - 1] = true;
        }

        for (int i = 1; i < 10; ++i) {
            char row;
            int col;

            std::cin >> row >> col;
            insert(row, col, i);
        }

        backtrack(0);
        std::cout << "Puzzle " << ++T << '\n';
        for (auto& row : board) {
            for (auto& col : row) {
                std::cout << col;
            }
            std::cout << '\n';
        }
    }

    return 0;
}
