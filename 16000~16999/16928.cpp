#include <iostream>
#include <queue>
#include <vector>

int bfs(const std::vector<int>& path) {
    std::vector<int> dist(101);
    std::queue<int> q;

    q.push(1);
    dist[1] = 0;

    while (!q.empty() && !dist[100]) {
        int cur = q.front();
        q.pop();

        for (int i = 1; i < 7; ++i) {
            if (int next = cur + i;
                next < 101 && path[next] && !dist[path[next]]) {
                dist[path[next]] = dist[cur] + 1;
                q.push(path[next]);
            } else if (next < 101 && !path[next] && !dist[next]) {
                dist[next] = dist[cur] + 1;
                q.push(next);
            }
        }
    }

    return dist[100];
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> path(101);
    for (int i = 0; i < n + m; ++i) {
        int u, v;
        std::cin >> u >> v;

        path[u] = v;
    }

    std::cout << bfs(path);

    return 0;
}