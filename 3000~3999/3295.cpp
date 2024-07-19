#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

bool try_kuhn(int u, std::vector<int>& mt, std::vector<bool>& used,
              const std::vector<std::vector<int>>& adj) {
    if (used[u]) return false;

    used[u] = true;
    for (int v : adj[u])
        if (mt[v] == -1 || try_kuhn(mt[v], mt, used, adj)) {
            mt[v] = u;
            return true;
        }

    return false;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int N, M;
        std::cin >> N >> M;

        std::vector<std::vector<int>> adj(N);
        for (int i = 0; i < M; ++i) {
            int u, v;
            std::cin >> u >> v;
            adj[u].push_back(v);
        }

        std::vector<int> mt(N, -1);
        std::vector<bool> used(N);

        int cnt = 0;
        for (int i = 0; i < N; ++i) {
            std::fill(used.begin(), used.end(), false);
            cnt += try_kuhn(i, mt, used, adj);
        }

        std::cout << cnt << '\n';
    }

    return 0;
}
