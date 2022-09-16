#include <algorithm>
#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<unsigned long long>>;
const int MOD = 1000003;

Matrix operator*(const Matrix& l, const Matrix& r) {
    Matrix result(l.size(), std::vector<unsigned long long>(r[0].size()));
    for (unsigned i = 0; i < l.size(); ++i)
        for (unsigned j = 0; j < r[0].size(); ++j)
            for (unsigned k = 0; k < r.size(); ++k)
                result[i][j] = (result[i][j] + (l[i][k] * r[k][j]) % MOD) % MOD;

    return result;
}

Matrix pow(const Matrix& m, int n) {
    if (n == 1)
        return m;
    else if (n % 2)
        return m * pow(m * m, (n - 1) / 2);
    return pow(m * m, n / 2);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, S, E, T;
    std::cin >> N >> S >> E >> T;

    Matrix weights(N, std::vector<unsigned long long>(N));
    for (auto& row : weights)
        for (auto& col : row) {
            char w;
            std::cin >> w;
            col = (w - '0');
        }

    Matrix adj(5 * N, std::vector<unsigned long long>(5 * N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 4; ++j) adj[5 * i + j][5 * i + j + 1] = 1;

        for (int j = 0; j < N; ++j)
            if (weights[i][j])
                adj[5 * (i + 1) - 1][5 * (j + 1) - weights[i][j]] = 1;
    }

    std::cout << pow(adj, T)[5 * S - 1][5 * E - 1] << '\n';

    return 0;
}