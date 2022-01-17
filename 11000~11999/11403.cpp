#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::vector<bool>> adj(n, std::vector<bool>(n));
    for (auto& v : adj) {
        for (int i = 0; i < n; ++i) {
            bool edge;
            std::cin >> edge;

            v[i] = edge;
        }
    }

    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (!adj[i][j] && adj[i][k] && adj[k][j]) adj[i][j] = true;

    for (const auto& u : adj) {
        for (const auto& v : u) std::cout << v << ' ';
        std::cout << '\n';
    }

    return 0;
}