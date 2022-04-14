#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

void backtrack(unsigned x, int result, const std::vector<int>& A,
               std::vector<int>& O, int& min, int& max) {
    if (x == A.size()) {
        if (result < min) min = result;
        if (result > max) max = result;
        return;
    }

    if (!x) {
        if (O[0]) {
            --O[0];
            backtrack(2, A[0] + A[1], A, O, min, max);
            ++O[0];
        }

        if (O[1]) {
            --O[1];
            backtrack(2, A[0] - A[1], A, O, min, max);
            ++O[1];
        }

        if (O[2]) {
            --O[2];
            backtrack(2, A[0] * A[1], A, O, min, max);
            ++O[2];
        }

        if (O[3]) {
            --O[3];
            backtrack(2, A[0] / A[1], A, O, min, max);
            ++O[3];
        }
    } else {
        if (O[0]) {
            --O[0];
            backtrack(x + 1, result + A[x], A, O, min, max);
            ++O[0];
        }

        if (O[1]) {
            --O[1];
            backtrack(x + 1, result - A[x], A, O, min, max);
            ++O[1];
        }

        if (O[2]) {
            --O[2];
            backtrack(x + 1, result * A[x], A, O, min, max);
            ++O[2];
        }

        if (O[3]) {
            --O[3];
            backtrack(x + 1, result / A[x], A, O, min, max);
            ++O[3];
        }
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> A(N);
    for (int& i : A) std::cin >> i;

    std::vector<int> O(4);
    for (int& i : O) std::cin >> i;

    int min = std::numeric_limits<int>::max();
    int max = std::numeric_limits<int>::min();

    backtrack(0, 0, A, O, min, max);

    std::cout << max << '\n' << min;

    return 0;
}
