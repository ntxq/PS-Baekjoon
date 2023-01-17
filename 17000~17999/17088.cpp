#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int backtrack(std::size_t idx, std::vector<int>& A, int diff, int count) {
    if (idx == A.size()) return count;

    int minCount = std::numeric_limits<int>::max();
    int curDiff = A[idx] - A[idx - 1];

    if (curDiff == diff) {
        minCount = std::min(minCount, backtrack(idx + 1, A, diff, count));
    } else if (curDiff == diff + 1) {
        A[idx]--;
        minCount = std::min(minCount, backtrack(idx + 1, A, diff, count + 1));
        A[idx]++;
    } else if (curDiff == diff - 1) {
        A[idx]++;
        minCount = std::min(minCount, backtrack(idx + 1, A, diff, count + 1));
        A[idx]--;
    }

    return minCount;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> A(N);
    for (auto& i : A) std::cin >> i;

    if (N == 1) {
        std::cout << 0 << '\n';
    } else {
        int dx[9][2] = {{0, 0},  {0, 1},  {0, -1}, {1, 0},  {1, 1},
                        {1, -1}, {-1, 0}, {-1, 1}, {-1, -1}};

        int minCount = std::numeric_limits<int>::max();
        for (int i = 0; i < 9; ++i) {
            A[0] += dx[i][0];
            A[1] += dx[i][1];
            int count = (dx[i][0] != 0) + (dx[i][1] != 0);

            minCount = std::min(minCount, backtrack(2, A, A[1] - A[0], count));

            A[0] -= dx[i][0];
            A[1] -= dx[i][1];
        }

        std::cout << (minCount == std::numeric_limits<int>::max() ? -1
                                                                  : minCount)
                  << '\n';
    }

    return 0;
}