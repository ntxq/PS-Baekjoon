#include <iostream>
#include <vector>

int nQueen(unsigned n, unsigned k, std::vector<bool>& row,
           std::vector<bool>& lDiagonal, std::vector<bool>& rDiagonal) {
    if (k == n) return 1;

    int count = 0;
    for (unsigned i = 0; i < n; ++i)
        if (!row[i] && !lDiagonal[i + k] && !rDiagonal[i - k + n - 1]) {
            row[i] = true;
            lDiagonal[i + k] = true;
            rDiagonal[i - k + n - 1] = true;
            count += nQueen(n, k + 1, row, lDiagonal, rDiagonal);
            row[i] = false;
            lDiagonal[i + k] = false;
            rDiagonal[i - k + n - 1] = false;
        }

    return count;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::vector<bool> row(n, false);
    std::vector<bool> lDiagonal(2 * n - 1, false);
    std::vector<bool> rDiagonal(2 * n - 1, false);

    std::cout << nQueen(n, 0, row, lDiagonal, rDiagonal);

    return 0;
}