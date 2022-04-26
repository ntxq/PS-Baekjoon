#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

std::vector<bool> dijktra(
    int s, int g, int h,
    const std::vector<std::vector<std::pair<int, int>>>& graph) {
    std::vector<int> dist(graph.size(), std::numeric_limits<int>::max());
    std::vector<bool> valid(graph.size());
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        pq;

    dist[s] = 0;
    valid[s] = false;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d != dist[u]) continue;

        for (auto [v, w] : graph[u]) {
            if (d + w < dist[v]) {
                dist[v] = d + w;
                if ((u == g && v == h) || (u == h && v == g))
                    valid[v] = true;
                else
                    valid[v] = valid[u];
                pq.push({dist[v], v});
            } else if (d + w == dist[v] &&
                       ((u == g && v == h) || (u == h && v == g) ||
                        (valid[u] && !valid[v]))) {
                valid[v] = true;
                pq.push({dist[v], v});
            }
        }
    }

    return valid;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int n, m, t;
        std::cin >> n >> m >> t;

        int s, g, h;
        std::cin >> s >> g >> h;

        std::vector<std::vector<std::pair<int, int>>> graph(n + 1);
        for (int i = 0; i < m; ++i) {
            int a, b, d;
            std::cin >> a >> b >> d;

            graph[a].push_back({b, d});
            graph[b].push_back({a, d});
        }

        std::vector<bool> valid(dijktra(s, g, h, graph));
        std::vector<int> answer;
        for (int i = 0; i < t; ++i) {
            int x;
            std::cin >> x;

            if (valid[x]) answer.push_back(x);
        }
        std::sort(answer.begin(), answer.end());

        for (int i : answer) std::cout << i << ' ';
        std::cout << '\n';
    }

    return 0;
}