#include <iostream>
#include <queue>
#include <utility>
#include <vector>

std::pair<int, int> bfs(int n, int k) {
    std::vector<std::pair<int, int>> dist(n < k ? 2 * k + 1 : n + 1);
    std::queue<int> q;

    q.push(n);
    dist[n] = {1, 1};

    while (!q.empty() && !dist[k].first) {
        size_t curSize = q.size();

        for (std::size_t i = 0; i < curSize; ++i) {
            int x = q.front();
            q.pop();

            if (x < 2 * k) {
                if (!dist[x + 1].first) {
                    dist[x + 1] = {dist[x].first + 1, dist[x].second};
                    q.push(x + 1);
                } else if (dist[x + 1].first == dist[x].first + 1)
                    dist[x + 1].second += dist[x].second;
            }

            if (x > 0) {
                if (!dist[x - 1].first) {
                    dist[x - 1] = {dist[x].first + 1, dist[x].second};
                    q.push(x - 1);
                } else if (dist[x - 1].first == dist[x].first + 1)
                    dist[x - 1].second += dist[x].second;
            }

            if (x <= k) {
                if (!dist[2 * x].first) {
                    dist[2 * x] = {dist[x].first + 1, dist[x].second};
                    q.push(2 * x);
                } else if (dist[2 * x].first == dist[x].first + 1)
                    dist[2 * x].second += dist[x].second;
            }
        }
    }

    return dist[k];
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, k;
    std::cin >> n >> k;

    auto [dist, count] = bfs(n, k);
    std::cout << dist - 1 << '\n' << count;

    return 0;
}