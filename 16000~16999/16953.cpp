#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

int bfs(unsigned long long a, unsigned long long b) {
    std::queue<std::pair<unsigned long long, int>> q;

    q.push({a, 1});

    int bDist = 0;
    bool found = false;
    while (!q.empty() && !found) {
        auto [cur, dist] = q.front();
        q.pop();

        if (unsigned long long next = cur * 2; next <= b) {
            q.push({next, dist + 1});

            if (next == b) {
                bDist = dist + 1;
                found = true;
            }
        }

        if (unsigned long long next = cur * 10 + 1; next <= b) {
            q.push({next, dist + 1});

            if (next == b) {
                bDist = dist + 1;
                found = true;
            }
        }
    }

    return found ? bDist : -1;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    unsigned long long a, b;
    std::cin >> a >> b;

    std::cout << bfs(a, b);

    return 0;
}