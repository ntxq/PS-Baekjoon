#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <set>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<bool>> adj(N, std::vector<bool>(N, true));
    for (int i = 0; i < M; ++i) {
        int a, b;
        std::cin >> a >> b;
        --a;
        --b;

        adj[a][b] = false;
        adj[b][a] = false;
    }

    int count = 0;
    for (int i = 0; i < N; ++i)
        for (int j = i + 1; j < N; ++j)
            for (int k = j + 1; k < N; ++k)
                if (adj[i][j] && adj[j][k] && adj[k][i]) ++count;

    std::cout << count << '\n';

    return 0;
}