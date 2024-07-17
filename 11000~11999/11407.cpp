#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

void shortest_paths(int s, std::vector<int>& dist, std::vector<int>& parent,
                    const std::vector<std::vector<int>>& adj,
                    const std::vector<std::vector<int>>& cost,
                    const std::vector<std::vector<int>>& capacity) {
    std::queue<int> q;
    std::vector<bool> in_queue(dist.size(), false);

    q.push(s);
    in_queue[s] = true;
    dist[s] = 0;

    while (!q.empty()) {
        int u = q.front();
        in_queue[u] = false;
        q.pop();

        for (int v : adj[u]) {
            if (capacity[u][v] > 0 && dist[v] > dist[u] + cost[u][v]) {
                dist[v] = dist[u] + cost[u][v];
                parent[v] = u;
                if (!in_queue[v]) {
                    in_queue[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<int>> adj(N + M + 2);
    std::vector<std::vector<int>> cost(N + M + 2, std::vector<int>(N + M + 2));
    std::vector<std::vector<int>> capacity(N + M + 2,
                                           std::vector<int>(N + M + 2));

    for (int i = 1; i <= N; ++i) {
        int x;
        std::cin >> x;

        adj[0].push_back(i);
        adj[i].push_back(0);
        capacity[0][i] = x;
    }

    for (int j = N + 1; j <= N + M; ++j) {
        int x;
        std::cin >> x;

        adj[j].push_back(N + M + 1);
        adj[N + M + 1].push_back(j);
        capacity[j][N + M + 1] = x;
    }

    for (int j = N + 1; j <= N + M; ++j) {
        for (int i = 1; i <= N; ++i) {
            int x;
            std::cin >> x;

            adj[i].push_back(j);
            adj[j].push_back(i);
            capacity[i][j] = x;
        }
    }

    for (int j = N + 1; j <= N + M; ++j) {
        for (int i = 1; i <= N; ++i) {
            int x;
            std::cin >> x;

            cost[i][j] = x;
            cost[j][i] = -x;
        }
    }

    int s = 0;
    int t = N + M + 1;
    int flow = 0;
    int cur_cost = 0;

    std::vector<int> dist(N + M + 2, std::numeric_limits<int>::max());
    std::vector<int> parent(N + M + 2, -1);
    shortest_paths(s, dist, parent, adj, cost, capacity);

    do {
        int f = std::numeric_limits<int>::max();
        int cur = t;
        while (cur != s) {
            f = std::min(f, capacity[parent[cur]][cur]);
            cur = parent[cur];
        }

        flow += f;
        cur_cost += f * dist[t];
        cur = t;
        while (cur != s) {
            capacity[parent[cur]][cur] -= f;
            capacity[cur][parent[cur]] += f;
            cur = parent[cur];
        }

        std::fill(dist.begin(), dist.end(), std::numeric_limits<int>::max());
        std::fill(parent.begin(), parent.end(), -1);
        shortest_paths(s, dist, parent, adj, cost, capacity);
    } while (dist[N + M + 1] != std::numeric_limits<int>::max());

    std::cout << flow << '\n' << cur_cost << '\n';

    return 0;
}
