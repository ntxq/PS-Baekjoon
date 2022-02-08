#include <algorithm>
#include <iostream>
#include <vector>

int dfs(int s, std::vector<int>& visited, const std::vector<int>& adj) {
    int next = s;
    while (!visited[next]) {
        visited[next] = 1;
        next = adj[next];
    }

    if (visited[next] == 1) {
        int loop = next;
        while (visited[loop] != 2) {
            visited[loop] = 2;
            loop = adj[loop];
        }
    }

    int count = 0;
    while (visited[s] == 1) {
        visited[s] = 2;
        s = adj[s];
        ++count;
    }

    return count;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++i) {
        int n;
        std::cin >> n;

        std::vector<int> adj(n);
        for (int j = 0; j < n; ++j) {
            std::cin >> adj[j];
            --adj[j];
        }

        std::vector<int> visited(n);

        int count = 0;
        for (int j = 0; j < n; ++j)
            if (!visited[j]) count += dfs(j, visited, adj);

        std::cout << count << '\n';
    }

    return 0;
}