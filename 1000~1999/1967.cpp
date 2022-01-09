#include <iostream>
#include <utility>
#include <vector>

std::pair<int, int> treeWidth(
    int root, const std::vector<std::vector<std::pair<int, int>>>& adj) {
    int maxWidth = 0, maxHeight = 0;
    for (const auto& [child, dist] : adj[root]) {
        auto [width, height] = treeWidth(child, adj);
        height += dist;

        if (int splitDist = maxHeight + height; splitDist > maxWidth)
            maxWidth = splitDist;
        if (height > maxHeight) maxHeight = height;
        if (width > maxWidth) maxWidth = width;
    }

    return {maxWidth, maxHeight};
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::vector<std::pair<int, int>>> adj(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;

        adj[u - 1].push_back({v - 1, w});
    }

    std::cout << treeWidth(0, adj).first;

    return 0;
}