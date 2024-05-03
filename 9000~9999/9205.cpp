#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int N;
        std::cin >> N;

        std::vector<std::pair<int, int>> locs(N + 2);
        for (auto& [x, y] : locs) std::cin >> x >> y;

        std::queue<int> q;
        std::vector<bool> visited(N + 2);

        q.push(0);
        visited[0] = true;

        while (!q.empty() && !visited[N + 1]) {
            int cur = q.front();
            q.pop();

            auto [cur_x, cur_y] = locs[cur];
            for (int i = 0; i < N + 2; ++i) {
                if (visited[i]) continue;

                auto [nx, ny] = locs[i];
                int dist = std::abs(cur_x - nx) + std::abs(cur_y - ny);

                if (dist <= 50 * 20) {
                    q.push(i);
                    visited[i] = true;
                }
            }
        }

        std::cout << (visited[N + 1] ? "happy" : "sad") << '\n';
    }

    return 0;
}
