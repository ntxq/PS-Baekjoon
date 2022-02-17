#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

bool visit(char& c, std::vector<bool>& keys, int& count) {
    if (std::isupper(c) && !keys[c - 'A']) return false;

    if (c == '$') ++count;
    if (std::islower(c)) keys[c - 'a'] = true;

    c = '.';

    return true;
}

int bfs(std::vector<std::vector<char>>& grid, std::vector<bool>& keys, int h,
        int w) {
    std::vector<std::vector<bool>> visited(h, std::vector<bool>(w));
    std::vector<std::vector<std::pair<int, int>>> trapped(26);
    std::queue<std::pair<int, int>> q;

    int count = 0;
    for (int i = 0; i < h; ++i) {
        if (grid[i][0] != '*') {
            if (visit(grid[i][0], keys, count))
                q.push({i, 0});
            else
                trapped[grid[i][0] - 'A'].push_back({i, 0});
        }

        visited[i][0] = true;

        if (grid[i][w - 1] != '*') {
            if (visit(grid[i][w - 1], keys, count))
                q.push({i, w - 1});
            else
                trapped[grid[i][w - 1] - 'A'].push_back({i, w - 1});
        }

        visited[i][w - 1] = true;
    }

    for (int i = 0; i < w; ++i) {
        if (grid[0][i] != '*') {
            if (visit(grid[0][i], keys, count))
                q.push({0, i});
            else
                trapped[grid[0][i] - 'A'].push_back({0, i});
        }

        visited[0][i] = true;

        if (grid[h - 1][i] != '*') {
            if (visit(grid[h - 1][i], keys, count))
                q.push({h - 1, i});
            else
                trapped[grid[h - 1][i] - 'A'].push_back({h - 1, i});
        }

        visited[h - 1][i] = true;
    }

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (0 <= nx && nx < h && 0 <= ny && ny < w && !visited[nx][ny]) {
                if (grid[nx][ny] != '*') {
                    if (visit(grid[nx][ny], keys, count))
                        q.push({nx, ny});
                    else
                        trapped[grid[nx][ny] - 'A'].push_back({nx, ny});
                }

                visited[nx][ny] = true;
            }
        }

        if (q.empty())
            for (int i = 0; i < 26; ++i)
                if (keys[i]) {
                    for (auto p : trapped[i]) q.push(p);
                    trapped[i].clear();
                }
    }

    return count;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    for (int t = 0; t < T; ++t) {
        int h, w;
        std::cin >> h >> w;

        std::vector<std::vector<char>> grid(h, std::vector<char>(w));
        std::vector<bool> keys(26);

        for (int i = 0; i < h; ++i)
            for (int j = 0; j < w; ++j) std::cin >> grid[i][j];

        std::string line;
        std::cin >> std::ws;
        std::getline(std::cin, line);

        for (const char& c : line)
            if (c != '0') keys[c - 'a'] = true;

        std::cout << bfs(grid, keys, h, w) << '\n';
    }

    return 0;
}