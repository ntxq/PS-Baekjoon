#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int K;
    std::cin >> K;

    for (int k = 0; k < K; ++k) {
        int V, E;
        std::cin >> V >> E;

        std::vector<std::vector<int>> graph(V + 1);
        for (int i = 0; i < E; ++i) {
            int u, v;
            std::cin >> u >> v;

            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        bool isBipartite = true;

        std::vector<int> level(V + 1);
        for (int i = 1; i <= V && isBipartite; ++i)
            if (!level[i]) {
                std::queue<int> q;
                level[i] = 1;
                q.push(i);

                while (!q.empty() && isBipartite) {
                    int u = q.front();
                    q.pop();

                    for (int v : graph[u])
                        if (!level[v]) {
                            level[v] = level[u] + 1;
                            q.push(v);
                        } else if (level[v] == level[u]) {
                            isBipartite = false;
                            break;
                        }
                }
            }

        std::cout << (isBipartite ? "YES" : "NO") << '\n';
    }

    return 0;
}