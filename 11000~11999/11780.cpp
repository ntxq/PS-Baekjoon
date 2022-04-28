#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

void findRoute(int u, int v, std::vector<int>& path,
               const std::vector<std::vector<int>>& P) {
    if (P[u][v] == u) {
        path.push_back(u);
        path.push_back(v);
        return;
    }

    findRoute(u, P[u][v], path, P);
    path.pop_back();
    findRoute(P[u][v], v, path, P);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    const int MAX = std::numeric_limits<int>::max();

    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<int>> P(N + 1, std::vector<int>(N + 1, -1));
    std::vector<std::vector<int>> dist(N + 1, std::vector<int>(N + 1, MAX));
    for (int i = 0; i < M; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;

        dist[a][b] = (dist[a][b] < c) ? dist[a][b] : c;
        P[a][b] = a;
    }

    for (int i = 1; i <= N; ++i) {
        dist[i][i] = 0;
        P[i][i] = i;
    }

    for (int k = 1; k <= N; ++k)
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j) {
                if (dist[i][k] != MAX && dist[k][j] != MAX &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    P[i][j] = k;
                }
            }

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) std::cout << (dist[i][j] == MAX ? 0 : dist[i][j]) << ' ';
        std::cout << '\n';
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (i == j || dist[i][j] == MAX) {
                std::cout << "0\n";
                continue;
            }

            std::vector<int> path;
            findRoute(i, j, path, P);

            std::cout << path.size() << ' ';
            for (int i : path) std::cout << i << ' ';
            std::cout << '\n';
        }
    }

    return 0;
}