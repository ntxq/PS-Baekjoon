#include <algorithm>
#include <iostream>
#include <vector>

std::vector<std::vector<int>> adj;
std::vector<int> match;
std::vector<bool> used;

bool bipartiteMatch(int u) {
    if (used[u]) return false;

    used[u] = true;
    for (int v : adj[u])
        if (match[v] == -1 || bipartiteMatch(match[v])) {
            match[v] = u;
            return true;
        }

    return false;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int C;
    std::cin >> C;

    while (C--) {
        int N, M;
        std::cin >> N >> M;

        int broken = 0;
        std::vector<std::vector<bool>> tables(N, std::vector<bool>(M, false));

        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j) {
                char c;
                std::cin >> c;

                broken += c == 'x';
                tables[i][j] = c == '.';
            }

        std::vector<int> candidates;
        adj.assign(N * M, std::vector<int>());
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                if (tables[i][j]) {
                    if (j > 0 && tables[i][j - 1]) {
                        adj[i * M + j].push_back(i * M + j - 1);
                        adj[i * M + j - 1].push_back(i * M + j);
                    }

                    if (i > 0 && j > 0 && tables[i - 1][j - 1]) {
                        adj[i * M + j].push_back((i - 1) * M + j - 1);
                        adj[(i - 1) * M + j - 1].push_back(i * M + j);
                    }

                    if (j < M - 1 && tables[i][j + 1]) {
                        adj[i * M + j].push_back(i * M + j + 1);
                        adj[i * M + j + 1].push_back(i * M + j);
                    }

                    if (i > 0 && j < M - 1 && tables[i - 1][j + 1]) {
                        adj[i * M + j].push_back((i - 1) * M + j + 1);
                        adj[(i - 1) * M + j + 1].push_back(i * M + j);
                    }

                    candidates.push_back(i * M + j);
                }

        int matchCount = 0;
        match.assign(N * M, -1);

        for (int u : candidates) {
            used.assign(N * M, false);
            matchCount += bipartiteMatch(u);
        }

        int ans = N * M - broken - matchCount / 2;
        std::cout << ans << '\n';
    }

    return 0;
}