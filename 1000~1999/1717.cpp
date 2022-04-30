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

    for (int i = 0; i < M; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;

        if (a)
            std::cout << (find(b, parents) == find(c, parents) ? "yes\n"
                                                               : "no\n");
        else
            unite(b, c, parents, ranks);
    }

    return 0;
}