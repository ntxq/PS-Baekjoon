
#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

long long dfs(int u, bool color, const std::vector<std::vector<int>>& adj,
              const std::vector<std::pair<int, int>>& costs) {
    static std::vector<std::pair<long long, long long>> dp(adj.size(),
                                                           {-1, -1});

    auto& ret = color ? dp[u].second : dp[u].first;
    if (ret != -1) return ret;

    if (color) {
        ret = costs[u].second;
        for (const auto v : adj[u]) ret += dfs(v, false, adj, costs);
    } else {
        ret = costs[u].first;
        for (const auto v : adj[u])
            ret +=
                std::min(dfs(v, false, adj, costs), dfs(v, true, adj, costs));
    }

    return ret;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::vector<int>> adj(N);
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
    }

    std::vector<std::pair<int, int>> costs(N);
    for (auto& cost : costs) std::cin >> cost.first >> cost.second;

    std::cout << std::min(dfs(0, false, adj, costs), dfs(0, true, adj, costs))
              << '\n';

    return 0;
}
