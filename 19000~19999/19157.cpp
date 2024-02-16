#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, Q;
    std::cin >> N >> Q;

    std::vector<int> row(N);
    std::vector<int> col(N);
    for (auto& r : row) std::cin >> r;
    for (auto& c : col) std::cin >> c;
    std::transform(row.begin(), row.end(), row.begin(),
                   [](int x) { return x % 2; });
    std::transform(col.begin(), col.end(), col.begin(),
                   [](int x) { return x % 2; });

    std::vector<int> row_sum(N);
    std::vector<int> col_sum(N);
    row_sum[0] = 0;
    col_sum[0] = 0;
    for (int i = 1; i < N; ++i) {
        row_sum[i] = row_sum[i - 1] + (row[i - 1] != row[i]);
        col_sum[i] = col_sum[i - 1] + (col[i - 1] != col[i]);
    }

    for (int i = 0; i < Q; ++i) {
        int sx, sy, tx, ty;
        std::cin >> sx >> sy >> tx >> ty;
        --sx, --sy, --tx, --ty;

        if (row_sum[sx] == row_sum[tx] && col_sum[sy] == col_sum[ty])
            std::cout << "YES\n";
        else
            std::cout << "NO\n";
    }

    return 0;
}
