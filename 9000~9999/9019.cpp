#include <algorithm>
#include <iostream>
#include <queue>
#include <string>

std::string bfs(int a, int b) {
    std::vector<std::string> dist(10000);
    std::queue<int> q;

    q.push(a);
    dist[a] = 'B';

    while (!q.empty() && dist[b].empty()) {
        int cur = q.front();
        q.pop();

        if (int d = (cur * 2) % 10000; dist[d].empty()) {
            dist[d] = dist[cur] + 'D';
            q.push(d);
        }

        if (int s = (cur + 9999) % 10000; dist[s].empty()) {
            dist[s] = dist[cur] + 'S';
            q.push(s);
        }

        if (int l = (cur * 10 + (cur / 1000)) % 10000; dist[l].empty()) {
            dist[l] = dist[cur] + 'L';
            q.push(l);
        }

        if (int r = (cur / 10 + (cur % 10 * 1000)) % 10000; dist[r].empty()) {
            dist[r] = dist[cur] + 'R';
            q.push(r);
        }
    }

    return dist[b].substr(1);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++i) {
        int a, b;
        std::cin >> a >> b;

        std::cout << bfs(a, b) << '\n';
    }

    return 0;
}