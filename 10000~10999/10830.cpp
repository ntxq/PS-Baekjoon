#include <iostream>
#include <vector>

std::vector<std::vector<int>> operator*(
    const std::vector<std::vector<int>>& lhs,
    const std::vector<std::vector<int>>& rhs) {
    std::vector<std::vector<int>> result(lhs.size(),
                                         std::vector<int>(rhs[0].size()));
    for (unsigned i = 0; i < lhs.size(); ++i)
        for (unsigned j = 0; j < rhs[0].size(); ++j)
            for (unsigned k = 0; k < rhs.size(); ++k)
                result[i][j] = (result[i][j] + lhs[i][k] * rhs[k][j]) % 1000;

    return result;
}

void power(std::vector<std::vector<int>>& matrix, unsigned long long exp,
           const std::vector<std::vector<int>> original) {
    if (exp == 1) return;

    power(matrix, exp / 2, original);
    matrix = matrix * matrix;

    if (exp % 2) matrix = matrix * original;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    unsigned long long b;
    std::cin >> n >> b;

    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
    for (auto& i : matrix)
        for (auto& j : i) std::cin >> j;

    power(matrix, b, matrix);
    for (int i = 0; i < n; ++i) {
        if (i) std::cout << '\n';
        for (int j = 0; j < n; ++j)
            if (j)
                std::cout << ' ' << (matrix[i][j] % 1000);
            else
                std::cout << (matrix[i][j] % 1000);
    }

    return 0;
}