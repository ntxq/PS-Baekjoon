#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <vector>

int bfs(int s) {
    const int t = 123456780;

    if (s == t) return 0;

    std::queue<int> q;
    std::set<int> visited;

    q.push(s);
    int dist = 0;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    int board[3][3]{};
    while (!q.empty()) {
        auto size = q.size();

        while (size--) {
            int u = q.front();
            q.pop();

            int x, y;

            for (int i = 2; i >= 0; --i)
                for (int j = 2; j >= 0; --j) {
                    board[i][j] = u % 10;
                    u /= 10;

                    if (board[i][j] == 0) {
                        x = i;
                        y = j;
                    }
                }

            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (0 <= nx && nx < 3 && 0 <= ny && ny < 3) {
                    std::swap(board[x][y], board[nx][ny]);

                    int v = 0;
                    for (int i = 0; i < 3; ++i)
                        for (int j = 0; j < 3; ++j) v = v * 10 + board[i][j];

                    if (v == t) {
                        return dist + 1;
                    } else if (!visited.contains(v)) {
                        visited.insert(v);
                        q.push(v);
                    }

                    std::swap(board[x][y], board[nx][ny]);
                }
            }
        }

        ++dist;
    }

    return -1;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int s = 0;
    for (int i = 0; i < 9; ++i) {
        int x;
        std::cin >> x;
        s = s * 10 + x;
    }

    std::cout << bfs(s) << '\n';

    return 0;
}
