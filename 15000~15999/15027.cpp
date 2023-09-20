#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <string>
#include <vector>

long long bfs(const std::vector<std::vector<std::pair<int, int>>>& graph) {
    std::vector<int> cur;
    std::vector<int> next;

    std::vector<int> visited(graph.size(), std::numeric_limits<int>::max());
    std::vector<int> dist(graph.size(), std::numeric_limits<int>::max());

    next.push_back(0);
    visited[0] = 0;
    dist[0] = 0;

    while (!next.empty()) {
        cur.swap(next);

        while (!cur.empty()) {
            int u = cur.back();
            cur.pop_back();

            for (const auto& [v, d] : graph[u]) {
                if (visited[v] == std::numeric_limits<int>::max()) {
                    visited[v] = visited[u] + 1;
                    dist[v] = d;
                    next.push_back(v);
                } else if (visited[v] == visited[u] + 1) {
                    dist[v] = std::min(dist[v], d);
                }
            }
        }
    }

    if (std::any_of(visited.begin(), visited.end(),
                    [](int v) { return v == std::numeric_limits<int>::max(); }))
        return -1;
    else
        return std::accumulate(dist.begin(), dist.end(), 0LL);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::map<std::string, int> languageIdx;
    languageIdx["English"] = 0;
    for (int i = 0; i < N; ++i) {
        std::string language;
        std::cin >> language;
        languageIdx[language] = i + 1;
    }

    std::vector<std::vector<std::pair<int, int>>> graph(N + 1);
    for (int i = 0; i < M; ++i) {
        std::string u, v;
        int d;

        std::cin >> u >> v >> d;
        graph[languageIdx[u]].push_back({languageIdx[v], d});
        graph[languageIdx[v]].push_back({languageIdx[u], d});
    }

    if (long long cost = bfs(graph); cost != -1)
        std::cout << cost << '\n';
    else
        std::cout << "Impossible\n";

    return 0;
}
