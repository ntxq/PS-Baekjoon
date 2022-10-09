#include <algorithm>
#include <iostream>
#include <vector>

using Path = std::vector<std::vector<int>>;
using Paths = std::vector<Path>;

using Count = std::vector<std::vector<long long>>;
using Counts = std::vector<Count>;

const int MOD = 1000000007;

Count operator*(const Count& a, const Count& b) {
    Count c(a.size(), std::vector<long long>(b[0].size()));
    for (unsigned i = 0; i < a.size(); ++i) {
        for (unsigned j = 0; j < b[0].size(); ++j) {
            for (unsigned k = 0; k < a[0].size(); ++k) {
                c[i][j] += a[i][k] * b[k][j];
                c[i][j] %= MOD;
            }
        }
    }
    return c;
}

Count expSquaring(const Count& count, int n) {
    if (n == 0) {
        Count c(count.size(), std::vector<long long>(count.size()));
        for (unsigned i = 0; i < count.size(); ++i) {
            c[i][i] = 1;
        }
        return c;
    } else if (n == 1)
        return count;
    else if (n % 2)
        return count * expSquaring(count * count, n / 2);
    else
        return expSquaring(count * count, n / 2);
}

Counts countPaths(const Paths& paths, int T, int N) {
    Counts result(T + 1, std::vector<std::vector<long long>>(
                             N, std::vector<long long>(N)));

    for (int i = 0; i < N; ++i) result[0][i][i] = 1;

    for (int t = 1; t <= T; ++t)
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                for (int k = 0; k < N; ++k)
                    result[t][i][j] =
                        (result[t][i][j] +
                         result[t - 1][i][k] * paths[t - 1][k][j]) %
                        MOD;

    return result;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T, N, D;
    std::cin >> T >> N >> D;

    Paths paths(T, Path(N, std::vector<int>(N)));
    for (int i = 0; i < T; ++i) {
        int M;
        std::cin >> M;

        for (int j = 0; j < M; ++j) {
            int u, v, w;
            std::cin >> u >> v >> w;
            paths[i][u - 1][v - 1] = w;
        }
    }

    auto counts(countPaths(paths, T, N));
    auto result = expSquaring(counts.back(), D / T) * counts[D % T];

    for (const auto& row : result) {
        for (const auto& col : row) std::cout << col << ' ';
        std::cout << '\n';
    }

    return 0;
}