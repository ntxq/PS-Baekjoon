#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

typedef std::pair<int, int> Point;
typedef std::tuple<int, int, int> Edge;
typedef std::vector<int> Row;
typedef std::vector<std::vector<int>> Matrix;

int Find(int x, Row& parents) {
    int root = parents[x];
    while (root != parents[root]) root = parents[root];
    while (root != parents[x]) {
        int next = parents[x];
        parents[x] = root;
        x = next;
    }
    return root;
}

void Union(int x, int y, Row& parents, Row& ranks) {
    int xroot = Find(x, parents);
    int yroot = Find(y, parents);

    if (xroot != yroot) {
        if (ranks[xroot] < ranks[yroot]) {
            parents[xroot] = yroot;
        } else if (ranks[xroot] > ranks[yroot]) {
            parents[yroot] = xroot;
        } else {
            parents[yroot] = xroot;
            ranks[xroot]++;
        }
    }
}

void bfs(Point s, int group, Matrix& map, int N, int M) {
    std::queue<Point> q;

    map[s.first][s.second] = group;
    q.push(s);

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (0 <= nx && nx < N && 0 <= ny && ny < M && map[nx][ny] == 1) {
                map[nx][ny] = group;
                q.push({nx, ny});
            }
        }
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    Matrix map(N, Row(M));
    for (auto& row : map)
        for (auto& cell : row) std::cin >> cell;

    int group = 2;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (map[i][j] == 1) {
                bfs({i, j}, group, map, N, M);
                ++group;
            }

    Matrix adj(group, Row(group));
    for (int i = 0; i < N; ++i) {
        int prev = 0;
        int dist = 0;
        for (int j = 0; j < M; ++j) {
            if (!prev && map[i][j]) {
                prev = map[i][j];
            } else if (map[i][j] == prev) {
                dist = 0;
            } else if (prev && !map[i][j]) {
                ++dist;
            } else if (prev && map[i][j]) {
                if (dist > 1 &&
                    (dist < adj[prev][map[i][j]] || !adj[prev][map[i][j]])) {
                    adj[prev][map[i][j]] = dist;
                    adj[map[i][j]][prev] = dist;
                }

                prev = map[i][j];
                dist = 0;
            }
        }
    }

    for (int i = 0; i < M; ++i) {
        int prev = 0;
        int dist = 0;
        for (int j = 0; j < N; ++j) {
            if (!prev && map[j][i]) {
                prev = map[j][i];
            } else if (prev == map[j][i]) {
                dist = 0;
            } else if (prev && !map[j][i]) {
                ++dist;
            } else if (prev && map[j][i]) {
                if (dist > 1 &&
                    (dist < adj[prev][map[j][i]] || !adj[prev][map[j][i]])) {
                    adj[prev][map[j][i]] = dist;
                    adj[map[j][i]][prev] = dist;
                }

                prev = map[j][i];
                dist = 0;
            }
        }
    }

    std::vector<Edge> edges;
    for (int i = 2; i < group; ++i)
        for (int j = i + 1; j < group; ++j)
            if (adj[i][j]) edges.push_back({adj[i][j], i, j});
    std::sort(edges.begin(), edges.end(), std::greater<Edge>());

    Row parents(group);
    Row ranks(group);
    std::iota(parents.begin(), parents.end(), 0);

    int sumDist = 0;
    int count = 0;
    while (count != group - 3 && !edges.empty()) {
        auto [dist, x, y] = edges.back();
        edges.pop_back();

        if (Find(x, parents) != Find(y, parents)) {
            Union(x, y, parents, ranks);
            sumDist += dist;
            ++count;
        }
    }

    std::cout << (count == group - 3 ? sumDist : -1) << std::endl;

    return 0;
}