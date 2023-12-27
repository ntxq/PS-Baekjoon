#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <string>
#include <vector>

int bfs(std::vector<int>& is_working, int target) {
    std::vector<int> dist(101, std::numeric_limits<int>::max());
    std::queue<int> q;

    for (int i = 1; i < 10; ++i)
        if (is_working[i]) {
            dist[i] = 1;
            q.push(i);

            for (int j = 0; j < 10; ++j)
                if (is_working[j] && 2 < dist[i * 10 + j]) {
                    dist[i * 10 + j] = 2;
                    q.push(i * 10 + j);
                }
        }

    if (is_working[0] && is_working[1]) dist[100] = 3;

    while (!q.empty() && dist[target] == std::numeric_limits<int>::max()) {
        int u = q.front();
        q.pop();

        for (int i = 1; i < 10; ++i) {
            int v = u * i;
            if (is_working[i] && v <= 100 && dist[u] + 2 < dist[v]) {
                dist[v] = dist[u] + 2;
                q.push(v);
            }
        }
    }

    return dist[target] == std::numeric_limits<int>::max() ? -1
                                                           : dist[target] + 1;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    for (int i = 1; i <= T; ++i) {
        std::vector<int> is_working(10);
        for (int& i : is_working) std::cin >> i;

        int target;
        std::cin >> target;

        int dist = bfs(is_working, target);
        std::cout << "Case #" << i << ": ";
        if (dist == -1)
            std::cout << "Impossible\n";
        else
            std::cout << dist << '\n';
    }

    return 0;
}
