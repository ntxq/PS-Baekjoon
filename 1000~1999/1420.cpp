#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <vector>

int N;
std::map<std::pair<int, int>, int> capacity;
std::vector<std::vector<int>> adj;

int bfs(int s, int t, std::vector<int>& parent) {
    std::fill(parent.begin(), parent.end(), -1);

    parent[s] = -2;
    std::queue<std::pair<int, int>> q;
    q.push({s, std::numeric_limits<int>::max()});

    while (!q.empty()) {
        auto [cur, flow] = q.front();
        q.pop();

        for (int next : adj[cur])
            if (parent[next] == -1 && capacity[{cur, next}]) {
                parent[next] = cur;
                int new_flow = std::min(flow, capacity[{cur, next}]);
                if (next == t) return new_flow;
                q.push({next, new_flow});
            }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    std::vector<int> parent(N);
    int new_flow;

    while ((new_flow = bfs(s, t, parent))) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[{prev, cur}] -= new_flow;
            capacity[{cur, prev}] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<char>> board(n, std::vector<char>(m));
    for (auto& row : board)
        for (auto& cell : row) std::cin >> cell;

    N = n * m;
    adj.resize(N * 2);

    int s, t;
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    for (int x = 0; x < n; ++x)
        for (int y = 0; y < m; ++y) {
            if (board[x][y] == '#') continue;
            if (board[x][y] == 'K') s = x * m + y + N;
            if (board[x][y] == 'H') t = x * m + y;

            int uIn = x * m + y;
            int uOut = N + x * m + y;

            adj[uIn].push_back(uOut);
            adj[uOut].push_back(uIn);
            capacity[{uIn, uOut}] = 1;

            for (int k = 0; k < 4; ++k) {
                int nx = x + dx[k];
                int ny = y + dy[k];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                if (board[nx][ny] == '#') continue;

                int vIn = nx * m + ny;
                // int vOut = N + nx * m + ny;

                adj[uOut].push_back(vIn);
                adj[vIn].push_back(uOut);
                capacity[{uOut, vIn}] = 1;

                if (board[nx][ny] == 'H') capacity[{uOut, vIn}] = 100;
            }
        }

    N = N * 2;
    int ans = maxflow(s, t);
    std::cout << (ans >= 100 ? -1 : ans) << '\n';

    return 0;
}
