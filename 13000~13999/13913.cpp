#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, K;
    std::cin >> N >> K;

    std::queue<int> Q;
    std::vector<int> P(2 * std::max(N, K) + 1);
    std::vector<int> dist(2 * std::max(N, K) + 1);

    Q.push(N);
    P[N] = -1;
    dist[N] = 1;

    bool isFound = false;
    while (!Q.empty() && !isFound) {
        int cur = Q.front();
        Q.pop();

        int dx[2] = {1, -1};
        for (int i = 0; i < 2; ++i) {
            int next = cur + dx[i];
            if (0 <= next && next <= 2 * std::max(N, K) && !dist[next]) {
                Q.push(next);
                P[next] = cur;
                dist[next] = dist[cur] + 1;
                if (next == K) isFound = true;
            }
        }

        int tp = cur * 2;
        if (0 <= tp && tp <= 2 * std::max(N, K) && !dist[tp]) {
            Q.push(tp);
            P[tp] = cur;
            dist[tp] = dist[cur] + 1;
            if (tp == K) isFound = true;
        }
    }

    std::cout << dist[K] - 1 << '\n';

    std::vector<int> path;
    while (K != -1) {
        path.push_back(K);
        K = P[K];
    }
    for (auto it = path.rbegin(); it != path.rend(); ++it) 
        std::cout << *it << ' ';
    

    return 0;
}