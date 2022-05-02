#include <algorithm>
#include <iostream>
#include <vector>

typedef std::vector<int> Row;
typedef std::vector<Row> Matrix;

void dfs(int x, int p, Row& size, const Matrix& adj) {
    size[x] = 1;

    for (int y : adj[x])
        if (y != p) {
            dfs(y, x, size, adj);
            size[x] += size[y];
        }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, R, Q;
    std::cin >> N >> R >> Q;

    Matrix adj(N + 1);
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        std::cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    Row size(N + 1);
    dfs(R, 0, size, adj);

    for (int i = 0; i < Q; ++i) {
        int x;
        std::cin >> x;

        std::cout << size[x] << '\n';
    }

    return 0;
}