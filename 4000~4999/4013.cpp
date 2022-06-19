#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

std::vector<std::vector<int>> adj, adj_rev, adj_scc;
std::vector<int> capacity, order, component, capacity_scc;
std::vector<bool> restaurant, visited, restaurant_scc;

void dfs(int u) {
    visited[u] = true;
    for (int v : adj[u])
        if (!visited[v]) dfs(v);

    order.push_back(u);
}

void dfs_rev(int u, int cid) {
    visited[u] = true;
    component[u] = cid;
    if (restaurant[u]) restaurant_scc[cid] = true;
    capacity_scc[cid] += capacity[u];

    for (int v : adj_rev[u])
        if (!visited[v])
            dfs_rev(v, cid);
        else if (component[v] != cid)
            adj_scc[component[v]].push_back(cid);
}

int bfs(int S) {
    std::queue<int> Q;
    std::vector<int> dist(adj_scc.size(), 0);

    Q.push(S);
    dist[S] = capacity_scc[S];

    int maxDist = 0;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        if (dist[u] > maxDist && restaurant_scc[u]) maxDist = dist[u];

        for (int v : adj_scc[u])
            if (dist[u] + capacity_scc[v] > dist[v]) {
                dist[v] = dist[u] + capacity_scc[v];
                Q.push(v);
            }
    }

    return maxDist;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    adj.resize(N + 1);
    adj_rev.resize(N + 1);

    for (int i = 0; i < M; ++i) {
        int u, v;
        std::cin >> u >> v;

        adj[u].push_back(v);
        adj_rev[v].push_back(u);
    }

    capacity.resize(N + 1);
    for (int i = 1; i <= N; ++i) std::cin >> capacity[i];

    int S, P;
    std::cin >> S >> P;

    restaurant.resize(N + 1);
    for (int i = 0; i < P; ++i) {
        int t;
        std::cin >> t;
        restaurant[t] = true;
    }

    visited.resize(N + 1);
    for (int i = 1; i <= N; ++i)
        if (!visited[i]) dfs(i);

    visited.assign(N + 1, false);
    std::reverse(order.begin(), order.end());
    component.resize(N + 1);

    int cid = 0;
    for (int u : order)
        if (!visited[u]) {
            capacity_scc.push_back(0);
            restaurant_scc.push_back(false);
            adj_scc.push_back(std::vector<int>());
            dfs_rev(u, cid++);
        }

    std::cout << bfs(component[S]) << '\n';

    return 0;
}