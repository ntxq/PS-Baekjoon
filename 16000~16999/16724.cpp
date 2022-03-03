#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int find(int x, std::vector<int>& parents) {
    int root = x;
    while (parents[root] != root) root = parents[root];

    while (parents[x] != root) {
        int next = parents[x];
        parents[x] = root;
        x = next;
    }

    return root;
}

void unite(int x, int y, std::vector<int>& parents) {
    static std::vector<int> ranks(parents.size());

    int xroot = find(x, parents);
    int yroot = find(y, parents);

    if (xroot != yroot) {
        if (ranks[x] == ranks[y]) {
            parents[xroot] = yroot;
            ranks[yroot]++;
        } else if (ranks[x] < ranks[y]) {
            parents[xroot] = yroot;
        } else {
            parents[yroot] = xroot;
        }
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<char>> grid(n, std::vector<char>(m));
    for (auto& row : grid)
        for (auto& c : row) std::cin >> c;

    std::vector<int> parents(n * m);
    std::iota(parents.begin(), parents.end(), 0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int curIdx = i * m + j;
            int moveIdx;

            switch (grid[i][j]) {
                case 'U':
                    moveIdx = curIdx - m;
                    break;
                case 'D':
                    moveIdx = curIdx + m;
                    break;
                case 'L':
                    moveIdx = curIdx - 1;
                    break;
                case 'R':
                    moveIdx = curIdx + 1;
                    break;
                default:
                    break;
            }

            if (find(curIdx, parents) != find(moveIdx, parents))
                unite(curIdx, moveIdx, parents);
        }
    }

    int count = 0;
    for (int i = 0; i < n * m; ++i)
        if (parents[i] == i) ++count;

    std::cout << count << '\n';

    return 0;
}
