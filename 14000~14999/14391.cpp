#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int N, M;
std::vector<std::vector<bool>> bitmask;
std::vector<std::vector<int>> numbers;

int calcScore() {
    int score = 0;

    for (int i = 0; i < N; ++i) {
        int curNum = 0;
        for (int j = 0; j < M; ++j) {
            if (bitmask[i][j]) {
                curNum = curNum * 10 + numbers[i][j];
            } else {
                score += curNum;
                curNum = 0;
            }
        }
        score += curNum;
    }

    for (int j = 0; j < M; ++j) {
        int curNum = 0;
        for (int i = 0; i < N; ++i) {
            if (!bitmask[i][j]) {
                curNum = curNum * 10 + numbers[i][j];
            } else {
                score += curNum;
                curNum = 0;
            }
        }
        score += curNum;
    }

    return score;
}

int backtrack(int idx) {
    if (idx == N * M) return calcScore();

    int row = idx / M;
    int col = idx % M;

    int curMax = backtrack(idx + 1);
    bitmask[row][col] = true;
    curMax = std::max(curMax, backtrack(idx + 1));
    bitmask[row][col] = false;

    return curMax;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::cin >> N >> M;

    bitmask.assign(N, std::vector<bool>(M, false));
    numbers.assign(N, std::vector<int>(M));
    for (auto& row : numbers)
        for (auto& elem : row) {
            char c;
            std::cin >> c;
            elem = c - '0';
        }

    std::cout << backtrack(0) << '\n';

    return 0;
}