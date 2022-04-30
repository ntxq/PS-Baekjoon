#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int find(int x, std::vector<int>& parents) {
    int root = parents[x];
    while (root != parents[root]) root = parents[root];

    while (x != parents[x]) {
        int next = parents[x];
        parents[x] = root;
        x = next;
    }

    return root;
}

void unite(int x, int y, std::vector<int>& parents, std::vector<int>& ranks) {
    int xroot = find(x, parents);
    int yroot = find(y, parents);

    if (xroot != yroot) {
        if (ranks[xroot] < ranks[yroot])
            parents[xroot] = yroot;
        else if (ranks[xroot] > ranks[yroot])
            parents[yroot] = xroot;
        else {
            parents[yroot] = xroot;
            ++ranks[xroot];
        }
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::vector<int> parents(N + 1);
    std::vector<int> ranks(N + 1);
    std::iota(parents.begin(), parents.end(), 0);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            bool isConnected;
            std::cin >> isConnected;

            if (isConnected) unite(i + 1, j + 1, parents, ranks);
        }

    bool isPossible = true;

    int u, v;
    std::cin >> u;
    for (int i = 0; i < M - 1 && isPossible; ++i) {
        std::cin >> v;
        isPossible &= find(u, parents) == find(v, parents);
        u = v;
    }

    std::cout << (isPossible ? "YES" : "NO") << '\n';

    return 0;
}