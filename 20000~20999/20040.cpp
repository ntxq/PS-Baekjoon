#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int find(std::vector<int>& parents, int x) {
    int root = x;
    while (root != parents[root]) root = parents[root];

    while (x != parents[x]) {
        int next = parents[x];
        parents[x] = root;
        x = next;
    }

    return root;
}

void unite(std::vector<int>& parents, std::vector<int>& ranks, int x, int y) {
    int xroot = find(parents, x);
    int yroot = find(parents, y);

    if (xroot != yroot) {
        if (ranks[xroot] == ranks[yroot]) {
            parents[xroot] = yroot;
            ranks[yroot]++;
        } else if (ranks[xroot] < ranks[yroot]) {
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

    std::vector<int> parents(n);
    std::iota(parents.begin(), parents.end(), 0);

    std::vector<int> ranks(n);

    int isCycle = 0;
    for (int i = 0; i < m && !isCycle; ++i) {
        int u, v;
        std::cin >> u >> v;

        if (find(parents, u) == find(parents, v))
            isCycle = i + 1;
        else
            unite(parents, ranks, u, v);
    }

    std::cout << isCycle << '\n';

    return 0;
}
