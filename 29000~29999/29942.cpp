#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <vector>

void dfs(const std::string& u, std::vector<std::string>& path,
         std::map<std::string, std::vector<std::string>>& graph,
         std::set<std::string>& visited) {
    auto& neighbors = graph[u];

    switch (neighbors.size()) {
        case 0:
            path.push_back(u);
            visited.insert(u);
            return;

        case 1:
            if (visited.contains(neighbors[0]) && path.back() == neighbors[0]) {
                path.push_back(u);
                visited.insert(u);
                return;
            } else if (!visited.contains(neighbors[0])) {
                path.push_back(u);
                visited.insert(u);
                return dfs(neighbors[0], path, graph, visited);
            } else {
                return;
            }

        case 2:
            if (visited.contains(neighbors[0]) && path.back() == neighbors[0]) {
                path.push_back(u);
                visited.insert(u);
                return dfs(neighbors[1], path, graph, visited);
            } else if (visited.contains(neighbors[1]) &&
                       path.back() == neighbors[1]) {
                path.push_back(u);
                visited.insert(u);
                return dfs(neighbors[0], path, graph, visited);
            } else {
                return;
            }

        default:
            return;
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::vector<std::string> names(N);
    for (auto& s : names) std::cin >> s;

    std::map<std::string, std::vector<std::string>> graph;
    for (int i = 0; i < M; ++i) {
        std::string u, v;
        std::cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    std::vector<std::string> path;
    std::set<std::string> visited;
    for (const auto& name : names) {
        const auto& neighbors = graph[name];
        if (neighbors.size() >= 2) continue;
        dfs(name, path, graph, visited);
    }

    bool isPossible = path.size() == N;
    if (isPossible) {
        std::cout << "SAAB\n";
        for (const auto& name : path) std::cout << name << ' ';
        std::cout << '\n';
    } else {
        std::cout << "EI SAA\n";
    }

    return 0;
}
