#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

void dfs(int v, int& time, const std::vector<std::vector<int>>& edges,
         std::vector<bool>& visited,
         std::vector<std::pair<int, int>>& finishTime) {
    visited[v] = true;
    ++time;
    for (int w : edges[v])
        if (!visited[w]) dfs(w, time, edges, visited, finishTime);

    finishTime[v].first = ++time;
}

void dfsTranspose(int v, const std::vector<std::vector<int>>& edges,
                  std::vector<bool>& visited, std::vector<int>& scc) {
    visited[v] = true;
    scc.push_back(v);
    for (int w : edges[v])
        if (!visited[w]) dfsTranspose(w, edges, visited, scc);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int v, e;
    std::cin >> v >> e;

    std::vector<std::vector<int>> edges(v);
    std::vector<std::vector<int>> reverseEdges(v);
    for (int i = 0; i < e; ++i) {
        int a, b;
        std::cin >> a >> b;

        edges[a - 1].push_back(b - 1);
        reverseEdges[b - 1].push_back(a - 1);
    }

    int time = 0;
    std::vector<bool> visited(v);
    std::vector<std::pair<int, int>> finishTime(v);

    for (int i = 0; i < v; ++i) finishTime[i].second = i;

    for (int i = 0; i < v; ++i)
        if (!visited[i]) dfs(i, time, edges, visited, finishTime);

    std::sort(finishTime.begin(), finishTime.end(),
              [](auto& a, auto& b) { return a.first > b.first; });

    std::vector<std::vector<int>> scc;
    visited.assign(v, false);

    for (int i = 0; i < v; ++i) {
        int v = finishTime[i].second;
        if (!visited[v]) {
            scc.push_back({});
            dfsTranspose(v, reverseEdges, visited, scc.back());
        }
    }

    for (unsigned i = 0; i < scc.size(); ++i)
        std::sort(scc[i].begin(), scc[i].end());
    std::sort(scc.begin(), scc.end());

    std::cout << scc.size() << '\n';
    for (unsigned i = 0; i < scc.size(); ++i) {
        for (int v : scc[i]) std::cout << v + 1 << ' ';
        std::cout << -1 << '\n';
    }

    return 0;
}
