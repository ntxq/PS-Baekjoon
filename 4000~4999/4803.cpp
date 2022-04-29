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
    int caseNo = 1;
    while (std::cin >> N >> M && (N || M)) {
        std::vector<int> parents(N + 1);
        std::vector<int> ranks(N + 1);
        std::vector<bool> isTree(N + 1, true);
        std::iota(parents.begin(), parents.end(), 0);

        int count = N;
        for (int i = 0; i < M; ++i) {
            int u, v;
            std::cin >> u >> v;

            int xroot = find(u, parents);
            int yroot = find(v, parents);

            if (xroot != yroot) {
                if (isTree[xroot] || isTree[yroot]) {
                    isTree[xroot] = isTree[yroot] =
                        isTree[xroot] & isTree[yroot];
                    --count;
                }
                unite(u, v, parents, ranks);
            } else if (isTree[xroot]) {
                isTree[xroot] = false;
                --count;
            }
        }

        if (!count)
            std::cout << "Case " << caseNo++ << ": No trees.\n";
        else if (count == 1)
            std::cout << "Case " << caseNo++ << ": There is one tree.\n";
        else
            std::cout << "Case " << caseNo++ << ": A forest of " << count
                      << " trees.\n";
    }

    return 0;
}