#include <algorithm>
#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>

std::vector<std::vector<unsigned long long>> operator*(
    const std::vector<std::vector<unsigned long long>>& lhs,
    const std::vector<std::vector<unsigned long long>>& rhs) {
    std::vector<std::vector<unsigned long long>> result(
        lhs.size(), std::vector<unsigned long long>(rhs[0].size()));
    for (size_t i = 0; i < lhs.size(); ++i) {
        for (size_t j = 0; j < rhs[0].size(); ++j) {
            for (size_t k = 0; k < lhs[0].size(); ++k) {
                result[i][j] += lhs[i][k] * rhs[k][j];
                result[i][j] %= 1000000007;
            }
        }
    }
    return result;
}

std::vector<std::vector<unsigned long long>> power(
    const std::vector<std::vector<unsigned long long>>& matrix,
    unsigned long long n) {
    if (n == 1) return matrix;

    auto result = power(matrix * matrix, n / 2);
    if (n % 2 == 1) result = result * matrix;

    return result;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<std::vector<unsigned long long>> adj{
        {0, 1, 1, 0, 0, 0, 0, 0}, {1, 0, 1, 1, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 0, 0, 0}, {0, 1, 1, 0, 1, 1, 0, 0},
        {0, 0, 1, 1, 0, 1, 0, 1}, {0, 0, 0, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 1, 0, 1}, {0, 0, 0, 0, 1, 0, 1, 0}};

    int d;
    std::cin >> d;

    std::cout << power(adj, d)[0][0] << '\n';

    return 0;
}
